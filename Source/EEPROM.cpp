// Copyright 2007 Peter Stegemann

#include "EEPROM.h"

#include <string.h>

using namespace avr;

//#define TWI_PINS			( UTILITY_BitValue( EEPROM_SCL) | UTILITY_BitValue( EEPROM_SDA))

// TWI address for 24Cxx EEPROM:
//
// 1 0 1 0  E2  E1  E0 R/~W 24C01/24C02
// 1 0 1 0  E2  E1  A8 R/~W 24C04
// 1 0 1 0  E2  A9  A8 R/~W 24C08
// 1 0 1 0 A10  A9  A8 R/~W 24C16
// 1 0 1 0 A18 A17 A16 R/~W 24C256
// 1 0 1 0 A17 A16 A15 R/~W FM24x256
// 1 0 1 0 A18 A17 A16 R/~W 24C512
// 1 0 1 0 A18 A17 A16 R/~W 24C1024
// 1 0 1 0 A17 A16 A15 R/~W FM24x512
#define TWI_SLA_24CXX		0b10100000

#define MAXIMUM_RETRIES		10000

struct EEPROM_Address
{
    uint8_t Low;
    uint8_t High;
    uint8_t Device;
};

void mapAddress( uint32_t MemoryAddress, EEPROM_Address* EepromAddress)
{
	EepromAddress->Low = MemoryAddress & 0xff;
	MemoryAddress = MemoryAddress >> 8;

	#if(( SYSTEM_EEPROM_TYPE == SYSTEM_EEPROM_TYPE_FM24C256 || SYSTEM_EEPROM_TYPE == SYSTEM_EEPROM_TYPE_FM24C512))
		EepromAddress->High = MemoryAddress & 0x7f;
		MemoryAddress = MemoryAddress >> 7;
	#elif(( SYSTEM_EEPROM_TYPE == SYSTEM_EEPROM_TYPE_AT24C512) || ( SYSTEM_EEPROM_TYPE == SYSTEM_EEPROM_TYPE_AT24C1024))
		EepromAddress->High = ( MemoryAddress & 0xff);
		MemoryAddress = MemoryAddress >> 8;
    #else
	    #error "Unknown system eeprom." SYSTEM_EEPROM_TYPE
    #endif

	EepromAddress->Device = TWI_SLA_24CXX | (( MemoryAddress & 0x07) << 1);
}

TWI::Result sendEepromAddress( EEPROM_Address* EepromAddress)
{
    TWI::Result TwiResult = TWI::OpenForWrite( EepromAddress->Device);

    if( TwiResult != TWI::R_Ok) return( TwiResult);

    // Send high 8 bits of address.
    TwiResult = TWI::WriteValue( EepromAddress->High);

    if( TwiResult != TWI::R_Ok) return( TwiResult);

    // Send low 8 bits of address.
    TwiResult = TWI::WriteValue( EepromAddress->Low);

    return( TwiResult);
}

bool EEPROM::readByteStart( uint32_t MemoryAddress)
{
    EEPROM_Address EepromAddress;

    mapAddress( MemoryAddress, &EepromAddress);

	bool Result = false;

	uint16_t RetryCount = MAXIMUM_RETRIES;

	while( RetryCount--)
	{
		TWI::Result TwiResult = sendEepromAddress( &EepromAddress);

		if( TwiResult == TWI::R_Repeat) continue;
		if( TwiResult == TWI::R_Failed) break;

		TwiResult = TWI::OpenForRead( EepromAddress.Device);

		if( TwiResult == TWI::R_Repeat) continue;
		if( TwiResult == TWI::R_Failed) break;

		Result = true;

		break;
	}

	return( Result);
}

void EEPROM::Initialize( void)
{
	// SCL frequency = Clock / 16 + 2 * TWBR * 4 ^ TWPS
	// 16 + 2 * TWBR * 4 ^ TWPS = Clock / SCL frequency
	// 16 + 2 * TWBR * 4 ^ TWPS = 14745600Hz / 400kHz = 36.864
	//
	// 388042Hz = 14745600Hz / 16 + 2 * 11 * 4 ^ 0
	// 409600Hz = 14745600Hz / 16 + 2 * 10 * 4 ^ 0
	TWSR = 0;
	TWBR = 10;
}

bool EEPROM::ReadByte( uint32_t MemoryAddress, uint8_t* Value)
{
    return( ReadBytes( MemoryAddress, 1, Value));
}

bool EEPROM::ReadBytes( uint32_t MemoryAddress, uint16_t Length, void* Value)
{
	uint8_t* Bytes = ( uint8_t*) Value;

	bool Result = readByteStart( MemoryAddress);

	while(( Result == true) && ( Length > 0))
	{
	    Result = TWI::ReadValue( Bytes, Length != 1);

		if( Result == true)
		{
			Bytes++;
			Length--;
		}
	}

	TWI::Stop();

	return( Result);
}

bool EEPROM::WriteByte( uint32_t MemoryAddress, uint8_t Value)
{
    EEPROM_Address EepromAddress;

    mapAddress( MemoryAddress, &EepromAddress);

	bool Result = false;

	uint16_t RetryCount = MAXIMUM_RETRIES;

	while( RetryCount--)
	{
        TWI::Result TwiResult = sendEepromAddress( &EepromAddress);

        if( TwiResult == TWI::R_Repeat) continue;
        if( TwiResult == TWI::R_Failed) break;

		// Send value.
		TwiResult = TWI::WriteValue( Value);

		if( TwiResult == TWI::R_Ok)
		{
    		Result = true;
    	}

		break;
	}

	TWI::Stop();

	return( Result);
}

bool EEPROM::WriteBytes( uint32_t MemoryAddress, uint16_t Length, const void* Value)
{
	uint8_t* Bytes = ( uint8_t*) Value;

	while( Length > 0)
	{
		if( WriteByte( MemoryAddress, *Bytes) == false)
		{
			return( false);
		}

		MemoryAddress++;
		Bytes++;
		Length--;
	}
	
	return( true);
}

bool EEPROM::ReadString( uint32_t MemoryAddress, uint8_t EepromSize, char* String, uint8_t Length)
{
	if( Length == 0)
	{
		return( false);
	}

	// Make room for termination in buffer.
	Length--;
	
	// Check the size.
	if( Length > EepromSize)
	{
		Length = EepromSize;
	}
	
	// If the string is shorter than what we read, it will come with a short termination.
	bool Result = ReadBytes( MemoryAddress, Length, String);

	// Add safety termination.
	String[ Length] = 0;

	return( Result);
}

bool EEPROM::WriteString( uint32_t MemoryAddress, uint8_t EepromSize, const char* String)
{
	// Measure size of string including termination.
	uint8_t Length = strlen( String) + 1;
	
	// Check the size.
	if( Length > EepromSize)
	{
		Length = EepromSize;
	}
	
	// So for the maximum string length, no termination will be written.
	return( WriteBytes( MemoryAddress, Length, String));
}
