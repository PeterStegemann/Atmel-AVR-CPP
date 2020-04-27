// Copyright 2015 Peter Stegemann

#include "AVR/Source/String.h"

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

int8_t STRING::Compare( const char* String1, const char* String2, bool CaseSensitive)
{
	if(( String1 == NULL) && ( String2 == NULL))
	{
		return( 0);
	}

	if(( String1 != NULL) && ( String2 != NULL))
	{
		if( CaseSensitive == true)
		{
			return( strcmp( String1, String2));
		}
		else
		{
			return( strcasecmp( String1, String2));
		}
	}

	return( String2 - String1);
}

int8_t STRING::Compare( const char* String1, const char* String2, uint8_t Length,
					    bool CaseSensitive)
{
	if(( String1 == NULL) && ( String2 == NULL))
	{
		return( 0);
	}

	if(( String1 != NULL) && ( String2 != NULL))
	{
		if( CaseSensitive == true)
		{
			return( strncmp( String1, String2, Length));
		}
		else
		{
			return( strncasecmp( String1, String2, Length));
		}
	}

	return( String2 - String1);
}

int8_t STRING::CompareBegin( const char* String1, const char* String2, bool CaseSensitive)
{
	if(( String1 == NULL) && ( String2 == NULL))
	{
		return( 0);
	}

	if(( String1 != NULL) && ( String2 != NULL))
	{
		return Compare( String1, String2, strlen( String2), CaseSensitive);
	}

	return( String2 - String1);
}
/*
void STRING::Trim( char* String)
{
	uint8_t SourceIndex = 0;
	uint8_t TargetIndex = 0;

	while( String[ SourceIndex] != 0)
	{
		if( isspace( String[ SourceIndex]) != 0)
		{
			SourceIndex++;
		}
		else
		{
			String[ TargetIndex++] = String[ SourceIndex++];
		}
	}

	String[ TargetIndex] = 0;
}
*/
char* STRING::SplitStart( char* String, char** Rest)
{
	return strtok_r( String, " \t\v\f\r\n", Rest);
}

char* STRING::Split( char** Rest)
{
	return SplitStart( NULL, Rest);
}

bool STRING::String2Boolean( const char* String)
{
	if(( Compare( String, "On") == 0) ||
	   ( Compare( String, "True") == 0) ||
	   ( Compare( String, "1") == 0))
	{
		return true;
	}

	return false;
}
