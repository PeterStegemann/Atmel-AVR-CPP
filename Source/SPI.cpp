// Copyright 2009 Peter Stegemann

#include "SPI.h"

#include "Ports.h"

#include "AVR/Source/Utility.h"

#if defined( SPI_DC)
	#define SPI_USED_BITS		UTILITY_BitValue( SPI_CLOCK) | \
								UTILITY_BitValue( SPI_DATA_OUTPUT) | \
								UTILITY_BitValue( SPI_RESET) | UTILITY_BitValue( SPI_DC) | \
								UTILITY_BitValue( SPI_SS)
#else
	#define SPI_USED_BITS		UTILITY_BitValue( SPI_CLOCK) | \
								UTILITY_BitValue( SPI_DATA_OUTPUT) | \
								UTILITY_BitValue( SPI_RESET) | UTILITY_BitValue( SPI_SS)
#endif

#define SPI_SetBit( Bit)		UTILITY_SetBit( SPI_PORT, Bit)
#define SPI_ClearBit( Bit)		UTILITY_ClearBit( SPI_PORT, Bit)

SPI::SPI( void)
{
}

void SPI::data( void)
{
	#if defined( SPI_DC)
		SPI_SetBit( SPI_DC);
	#endif
}

void SPI::command( void)
{
	#if defined( SPI_DC)
		SPI_ClearBit( SPI_DC); 
	#endif
}

void SPI::Initialize( void)
{
	SPI_DDR |= SPI_USED_BITS;

	#if defined( SPI_0_SELECT)
		UTILITY_SetBit( SPI_DDR, SPI_0_SELECT);
		SPI_SetBit( SPI_0_SELECT);
	#endif
	#if defined( SPI_1_SELECT)
		UTILITY_SetBit( SPI_DDR, SPI_1_SELECT);
		SPI_SetBit( SPI_1_SELECT);
	#endif

	// Reset devices.
	#if defined( SPI_0_SELECT)
		SPI_ClearBit( SPI_0_SELECT);
	#endif
	#if defined( SPI_1_SELECT)
		SPI_ClearBit( SPI_1_SELECT);
	#endif

	SPI_ClearBit( SPI_RESET);
	UTILITY::Pause( 75);
	
	// Return from reset.
	SPI_SetBit( SPI_RESET);
	UTILITY::Pause( 75);

	#if defined( SPI_0_SELECT)
		SPI_SetBit( SPI_0_SELECT);
	#endif
	#if defined( SPI_1_SELECT)
		SPI_SetBit( SPI_1_SELECT);
	#endif
	
	// Fast SPI
	SPSR = UTILITY_BitValue( SPI2X);
	// Slow SPI.
	// SPSR = 0;
	SPCR = UTILITY_BitValue( SPE) | UTILITY_BitValue( MSTR) | UTILITY_BitValue( CPHA) |
		   UTILITY_BitValue( CPOL); // | UTILITY_BitValue( SPR0) | UTILITY_BitValue( SPR1);

	// Pull up SPI_RESET as it shares a pin with MISO which is going to input when SPI is activated.
	SPI_PORT |= UTILITY_BitValue( SPI_RESET);
}

void SPI::Select( uint8_t Id)
{
	switch( Id)
	{
		#if defined( SPI_0_SELECT)
			case 0 : SPI_ClearBit( SPI_0_SELECT); break;
		#endif
		#if defined( SPI_1_SELECT)
			case 1 : SPI_ClearBit( SPI_1_SELECT); break;
		#endif
	}
}

void SPI::Deselect( uint8_t Id)
{
	switch( Id)
	{
		#if defined( SPI_0_SELECT)
			case 0 : SPI_SetBit( SPI_0_SELECT); break;
		#endif
		#if defined( SPI_1_SELECT)
			case 1 : SPI_SetBit( SPI_1_SELECT); break;
		#endif
	}
}

void SPI::Wait( void)
{
//	while( SPCR & UTILITY_BitValue( SPE))
	{
		while( !( SPSR & UTILITY_BitValue( SPIF)));

//		SPCR &= ~( UTILITY_BitValue( SPE));
	}
}

void SPI::SendCommandByte( uint8_t Value) 
{
	// Set to command.
	command(); 

	SPCR |= UTILITY_BitValue( SPE);
	SPDR = Value;
	Wait();
}

void SPI::SendCommandWord( uint16_t Value) 
{
	// Set to command.
	command(); 

	SPCR |= UTILITY_BitValue( SPE);
	SPDR = ( Value >> 8) & 0xff;
	Wait();

	SPCR |= UTILITY_BitValue( SPE);
	SPDR = Value & 0xff;
	Wait();
}

void SPI::SendDataByte( uint8_t Value) 
{
	// Set to data.
	data(); 
	
	SPCR |= UTILITY_BitValue( SPE);
	SPDR = Value;
	Wait();
}

void SPI::SendDataWord( uint16_t Value) 
{
	// Set to data.
	data(); 
	
	SPCR |= UTILITY_BitValue( SPE);
	SPDR = ( Value >> 8) & 0xff;
	Wait();

	SPCR |= UTILITY_BitValue( SPE);
	SPDR = Value & 0xff;
	Wait();
}

void SPI::SendDataBytes( const uint8_t Data[], uint16_t DataSize) 
{
	// Set to data.
	data(); 

	while( DataSize > 0)
	{
		SPCR |= UTILITY_BitValue( SPE);
		SPDR = *Data;
		Wait();

		Data++;
		DataSize--;
	}
}

void SPI::SendDataWords_P( const flash_uint16_t Data[], uint16_t DataSize)
{
	// Set to data.
	data();

	while( DataSize > 0)
	{
		uint16_t Value = pgm_read_word( Data);

		SPCR |= UTILITY_BitValue( SPE);
		SPDR = ( Value >> 8) & 0xff;
		Wait();

		SPCR |= UTILITY_BitValue( SPE);
		SPDR = Value & 0xff;
		Wait();

		Data++;
		DataSize--;
	}
}
