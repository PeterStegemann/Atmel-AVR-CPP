// Copyright 2015 Peter Stegemann

#pragma once

#include "AVR/Components/Types.h"

#include <stdlib.h>
#include <string.h>

class STRING
{
  public:
	static int8_t Compare( const char* String1, const char* String2, bool CaseSensitive = false);
	static int8_t Compare( const char* String1, const char* String2, uint8_t Length,
						   bool CaseSensitive = false);

	static int8_t CompareBegin( const char* String1, const char* String2,
							    bool CaseSensitive = false);

	// Remove leading and trailing whitespace.
	//	static void Trim( char* String);

	static char* SplitStart( char* String, char** Rest);
	static char* Split( char** Rest);

	// Convert a string to boolean.
	static bool String2Boolean( const char* String);
	// Convert a string to uint_8.
	template< class T> static T String2UInt( const char* String)
	{
		T Number = 0;

		String2UInt( String, &Number);

		return Number;
	}

	template< class T> static bool String2UInt( const char* String, T* Number)
	{
		if( String == NULL)
		{
			return false;
		}

		// Assume decimal as default
		bool Decimal = true;
		bool Hex = false;

		char* Temp;

	// Assume octal if we find a leading zero.
	/*	if( *String == '0')
	 {
		*Number = strtoul( String, &Temp, 8);

		if( Temp)
		{
	 switch( *Temp)
	 {
	 // Hmm, is decimal...
	 case '8' :
	 case '9' :
	 {
	 Decimal = true;
	 }
	 break;

	 // Is hex!
	 case 'x' :
	 {
	 Hex = true;
	 Decimal = false;
	 }
	 break;

	 case 0x0 :
	 {
	 return( true);
	 }
	 break;

	 default: break;
	 }
		}
	 }
	 */
		if( Decimal == true)
		{
			*Number = strtoul( String, &Temp, 10);

			if( Temp != NULL)
			{
				switch( *Temp)
				{
					case 'a' :
					case 'A' :
					case 'b' :
					case 'B' :
					case 'c' :
					case 'C' :
					case 'd' :
					case 'D' :
					case 'e' :
					case 'E' :
					case 'f' :
					case 'F' :
					{
						Decimal = false;
						Hex = true;
					}
					break;

					case 0x0 :
					{
						return true;
					}
					break;
				}
			}
		}

		if( Hex == true)
		{
			*Number = strtoul( String, &Temp, 16);

			if( Temp && ( *Temp == 0))
			{
				return true;
			}
		}

		return false;
	}
};
