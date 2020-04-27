// Copyright 2007 Peter Stegemann

#include "EEPROM.h"

#include <string.h>
#include <util/twi.h>

#define TWI_PINS			( UTILITY_BitValue( EEPROM_SCL) | UTILITY_BitValue( EEPROM_SDA))

#define TWI_Start()			TWCR = ( 1 << TWINT) | ( 1 << TWSTA) | ( 1 << TWEN);
#define TWI_Stop()			TWCR = ( 1 << TWINT) | ( 1 << TWSTO) | ( 1 << TWEN);
#define TWI_Wait()			while( !( TWCR & ( 1 << TWINT)));
#define TWI_Send( Value)	TWDR = ( Value); TWCR = ( 1 << TWINT) |  ( 1 << TWEN);

// TWI address for 24Cxx EEPROM:
//
// 1 0 1 0  E2  E1  E0 R/~W 24C01/24C02
// 1 0 1 0  E2  E1  A8 R/~W 24C04
// 1 0 1 0  E2  A9  A8 R/~W 24C08
// 1 0 1 0 A10  A9  A8 R/~W 24C16
// 1 0 1 0 A18 A17 A16 R/~W 24C256
// 1 0 1 0 A18 A17 A16 R/~W 24C512
// 1 0 1 0 A18 A17 A16 R/~W 24C1024
// 1 0 1 0 A17 A16 A15 R/~W FM24C512
#define TWI_SLA_24CXX		0b10100000

#define MAXIMUM_RETRIES		10000

bool EEPROM::readByteStart( uint32_t Address)
{
	uint32_t AddressCopy = Address;

	uint8_t AddressLow = AddressCopy & 0xff;
	AddressCopy = AddressCopy >> 8;

	#if( SYSTEM_EEPROM_TYPE == SYSTEM_EEPROM_TYPE_FM24C512)
		uint8_t AddressHigh = AddressCopy & 0x7f;
		AddressCopy = AddressCopy >> 7;
	#elif(( SYSTEM_EEPROM_TYPE == SYSTEM_EEPROM_TYPE_AT24C512) || ( SYSTEM_EEPROM_TYPE == SYSTEM_EEPROM_TYPE_AT24C1024))
		uint8_t AddressHigh = ( AddressCopy & 0xff);
		AddressCopy = AddressCopy >> 8;
	#endif
	
	uint8_t DeviceAddress = ( AddressCopy & 0x07) << 1;

	bool Result = false;
	uint8_t Status;

	uint16_t RetryCount = MAXIMUM_RETRIES;

	while( RetryCount--)
	{
		TWI_Start();
		TWI_Wait();

		Status = TW_STATUS;

		if( Status == TW_MT_ARB_LOST) continue;
		
		if(( Status != TW_REP_START) && ( Status != TW_START))
		{
			return( false);
		}

		TWI_Send( TWI_SLA_24CXX | DeviceAddress | TW_WRITE);
		TWI_Wait();

		Status = TW_STATUS;

		if( Status == TW_MT_SLA_NACK) continue;
		if( Status == TW_MT_ARB_LOST) continue;
		if( Status != TW_MT_SLA_ACK) break;

		// Send high 8 bits of address.
		TWI_Send( AddressHigh);
		TWI_Wait();

		Status = TW_STATUS;

		if( Status == TW_MT_DATA_NACK) continue;
		if( Status == TW_MT_ARB_LOST) continue;
		if( Status != TW_MT_DATA_ACK) break;

		// Send low 8 bits of address. 
		TWI_Send( AddressLow);
		TWI_Wait();

		Status = TW_STATUS;

		if( Status == TW_MT_DATA_NACK) continue;
		if( Status == TW_MT_ARB_LOST) continue;
		if( Status != TW_MT_DATA_ACK) break;

		TWI_Start();
		TWI_Wait();

		Status = TW_STATUS;

		if( Status == TW_MT_ARB_LOST) continue;

		if(( Status != TW_REP_START) && ( Status != TW_START))
		{
			return( false);
		}

		TWI_Send( TWI_SLA_24CXX | DeviceAddress | TW_READ);
		TWI_Wait();

		Status = TW_STATUS;

		if( Status == TW_MR_SLA_NACK) continue;
		if( Status == TW_MR_ARB_LOST) continue;
		if( Status != TW_MR_SLA_ACK) break;

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
	
bool EEPROM::ReadByte( uint32_t Address, uint8_t* Value)
{
	bool Result = false;

	if( readByteStart( Address))
	{
		// Do read transmission.
		TWCR = ( 1 << TWINT) | ( 1 << TWEN);
		TWI_Wait();

		uint8_t Status = TW_STATUS;

		if(( Status == TW_MR_DATA_ACK) || ( Status == TW_MR_DATA_NACK))
		{
			*Value = TWDR;

			Result = true;
		}
	}

	TWI_Stop();

	return( Result);
}

bool EEPROM::ReadBytes( uint32_t Address, uint16_t Length, void* Value)
{
	uint8_t* ValueCopy = ( uint8_t*) Value;

	bool Result;

//	do
//	{
	Result = readByteStart( Address);

	while( Result && ( Length > 0))
	{
		// Start read transmission.
		if( Length == 1)
		{
			// Last byte to get.
			TWCR = ( 1 << TWINT) | ( 1 << TWEN);
		}
		else
		{
			// Get more bytes after this one.
			TWCR = ( 1 << TWINT) | ( 1 << TWEN) | ( 1 << TWEA);
		}

		TWI_Wait();

		if(( TW_STATUS == TW_MR_DATA_ACK) || (( Length == 1) && ( TW_STATUS == TW_MR_DATA_NACK)))
		{
			*ValueCopy = TWDR;

//			AddressCopy++;
			ValueCopy++;
			Length--;
		}

		if(( Length == 0) && ( TW_STATUS == TW_MR_DATA_NACK))
		{
			// This was the last one we get.
			break;
		}

		if( TW_STATUS != TW_MR_DATA_ACK)
		{
			Result = false;

			break;
		}
	}

	TWI_Stop();
//	}
//	while( Result && ( Length > 0));

	return( Result);
}

bool EEPROM::WriteByte( uint32_t Address, uint8_t Value)
{
	uint32_t AddressCopy = Address;

	uint8_t AddressLow = AddressCopy & 0xff;
	AddressCopy = AddressCopy >> 8;

	#if( SYSTEM_EEPROM_TYPE == SYSTEM_EEPROM_TYPE_FM24C512)
		uint8_t AddressHigh = AddressCopy & 0x7f;
		AddressCopy = AddressCopy >> 7;
	#elif(( SYSTEM_EEPROM_TYPE == SYSTEM_EEPROM_TYPE_AT24C512) || ( SYSTEM_EEPROM_TYPE == SYSTEM_EEPROM_TYPE_AT24C1024))
		uint8_t AddressHigh = ( AddressCopy & 0xff);
		AddressCopy = AddressCopy >> 8;
	#endif
	
	uint8_t DeviceAddress = ( AddressCopy & 0x07) << 1;

	bool Result = false;

	uint16_t RetryCount = MAXIMUM_RETRIES;

	while( RetryCount--)
	{
		TWI_Start();
		TWI_Wait();

		if( TW_STATUS == TW_MT_ARB_LOST) continue;

		if(( TW_STATUS != TW_REP_START) && ( TW_STATUS != TW_START))
		{
			return( false);
		}

		TWI_Send( TWI_SLA_24CXX | DeviceAddress | TW_WRITE);
		TWI_Wait();

		if( TW_STATUS == TW_MT_SLA_NACK) continue;
		if( TW_STATUS == TW_MT_ARB_LOST) continue;
		if( TW_STATUS != TW_MT_SLA_ACK) break;

		// Send high 8 bits of address. 
		TWI_Send( AddressHigh);
		TWI_Wait();

		if( TW_STATUS == TW_MT_DATA_NACK) continue;
		if( TW_STATUS == TW_MT_ARB_LOST) continue;
		if( TW_STATUS != TW_MT_DATA_ACK) break;

		// Send low 8 bits of address. 
		TWI_Send( AddressLow);
		TWI_Wait();
		
		if( TW_STATUS == TW_MT_DATA_NACK) continue;
		if( TW_STATUS == TW_MT_ARB_LOST) continue;
		if( TW_STATUS != TW_MT_DATA_ACK) break;

		// Send value.
		TWI_Send( Value);
		TWI_Wait();

		if( TW_STATUS != TW_MT_DATA_ACK) break;

		Result = true;
		break;
	}

	TWI_Stop();

	return( Result);
}

bool EEPROM::WriteBytes( uint32_t Address, uint16_t Length, const void* Value)
{
	uint32_t AddressCopy = Address;
	uint8_t* ValueCopy = ( uint8_t*) Value;
	
	while( Length > 0)
	{
		if( WriteByte( AddressCopy, *ValueCopy) == false)
		{
			return( false);
		}
		
		AddressCopy++;
		ValueCopy++;
		Length--;
	}
	
	return( true);
}

bool EEPROM::ReadString( uint32_t Address, uint8_t EepromSize, char* String, uint8_t Length)
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
	bool Result = ReadBytes( Address, Length, String);

	// Add safety termination.
	String[ Length] = 0;

	return( Result);
}

bool EEPROM::WriteString( uint32_t Address, uint8_t EepromSize, const char* String)
{
	// Measure size of string including termination.
	uint8_t Length = strlen( String) + 1;
	
	// Check the size.
	if( Length > EepromSize)
	{
		Length = EepromSize;
	}
	
	// So for the maximum string length, no termination will be written.
	return( WriteBytes( Address, Length, String));
}
