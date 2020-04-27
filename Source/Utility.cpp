// Copyright 2007 Peter Stegemann

#include "AVR/Components/Utility.h"
#include "AVR/Components/Types.h"

#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <string.h>
#include <util/delay.h>

void UTILITY::Pause( uint16_t Milliseconds)
{
	while( Milliseconds > 0)
	{
		_delay_ms( 1);

		Milliseconds--;
	}
}
/*
#if( SYSTEM_MODE == SYSTEM_MODE_SETUP)
void UTILITY::PrintByteBits( LCD_65K_RGB* UseLCD, uint16_t Left, uint16_t Bottom, const char* Text,
	                         uint8_t Value)
{
	char BitString[] = "00000000";

	uint8_t ValueCopy = Value;

	for( uint8_t Count = 0; Count < 8; Count++)
	{
		if( ValueCopy & 0x01)
		{
			BitString[ 7 - Count] = '1';
		}
		else
		{
			BitString[ 7 - Count] = '0';
		}

		ValueCopy = ValueCopy >> 1;		
	}

 	UseLCD->PrintFormat( Left, Bottom, FONT::FI_Mini, LCD_65K_RGB::C_WarmYellow,
						 LCD_65K_RGB::C_Black, LCD_65K_RGB::PO_Proportional, "%s%s", Text,
						 BitString);
}
#endif
*/

int8_t UTILITY::Invert( int8_t Value)
{
	if( Value != 0)
	{
		return( false);
	}
	else
	{
		return( true);
	}
}

void UTILITY::SoftReset( void)
{
	// Jump into reset vector.
	goto *(( void**) NULL);
}

void UTILITY::HardReset( void)
{
	// Stop all interrupt activity.
	cli();

	// Enable watchdog.
	wdt_enable( WDTO_1S);

	while( true);
}

void* operator new( size_t Size)
{
	return( NULL);
} 

void operator delete( void* Buffer)
{
}

void operator delete( void* Buffer, unsigned int Size)
{
}

extern "C" void __cxa_pure_virtual( void)
{
}
