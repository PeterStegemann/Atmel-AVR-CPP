// Copyright 2007 Peter Stegemann

#pragma once

#include "AVR/Components/Types.h"
/*
#if( SYSTEM_MODE == SYSTEM_MODE_SETUP)
#include "AVR/Components/LCD/LCD_65K_RGB.h"
#endif
*/
#include <stdlib.h> 

#define UTILITY_BitValue( Bit)				( 1 << ( Bit))
#define UTILITY_SetBit( Value, Bit)			( Value |= UTILITY_BitValue( Bit))
#define UTILITY_ClearBit( Value, Bit)		( Value &= ~UTILITY_BitValue( Bit))
#define UTILITY_GetBit( Value, Bit)			(( Value) & UTILITY_BitValue( Bit))

#define UTILITY_BitValue32( Bit)			( 1UL << ( Bit))
#define UTILITY_SetBit32( Value, Bit)		( Value |= UTILITY_BitValue32( Bit))
#define UTILITY_ClearBit32( Value, Bit)		( Value &= ~UTILITY_BitValue32( Bit))
#define UTILITY_GetBit32( Value, Bit)		(( Value) & UTILITY_BitValue32( Bit))

#define UTILITY_Maximum( A, B)				((( A) >= ( B)) ? ( A) : ( B))
#define UTILITY_Minimum( A, B)				((( A) <= ( B)) ? ( A) : ( B))

#define UTILITY_Absolute( Value)			((( Value) < 0) ? -( Value) : ( Value))

class LCD;

class UTILITY
{
  public:
	// Wait some milliseconds. Internal timer can't wait very long.
	static void Pause( uint16_t Milliseconds);

	// Quick soft reset.
	static void SoftReset( void);
	// Slow hard rest.
	static void HardReset( void);
/*
	#if( SYSTEM_MODE == SYSTEM_MODE_SETUP)
	static void PrintByteBits( LCD_65K_RGB* UseLCD, uint16_t Left, uint16_t Bottom,
							   const char* Text, uint8_t Value);
	#endif
*/
	static int8_t Invert( int8_t Value);
};

void* operator new( size_t Size); 
void operator delete( void* Buffer); 
void operator delete( void* Buffer, unsigned int Size);
