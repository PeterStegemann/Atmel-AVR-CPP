// Copyright 2015 Peter Stegemann

#pragma once

#include "AVR/Source/Types.h"

#include <stdlib.h>
#include <string.h>

namespace avr
{
  class String
  {
    public:
      static int8_t Compare( const char* String1, const char* String2, bool CaseSensitive = false)
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

	  static int8_t Compare( const char* String1, const char* String2, uint8_t Length, bool CaseSensitive = false)
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

      static int8_t CompareBegin( const char* String1, const char* String2, bool CaseSensitive = false)
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

      // Remove leading and trailing whitespace.
	  // static void Trim( char* String);

      static char* SplitStart( char* String, char** Rest)
      {
          return( strtok_r( String, " \t\v\f\r\n", Rest));
      }

      static char* Split( char** Rest)
      {
      	  return( SplitStart( NULL, Rest));
      }

      // Convert a string to boolean.
      static bool String2Boolean( const char* String)
      {
      	  if(( Compare( String, "On") == 0) || ( Compare( String, "True") == 0) || ( Compare( String, "1") == 0))
      	  {
      		  return( true);
      	  }

      	  return( false);
      }

/*
    void Trim( char* String)
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
	  // Convert a string to uint_8.
	  template< class T> static T String2UInt( const char* String)
	  {
		  T Number = 0;

		  String2UInt( String, &Number);

		  return( Number);
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
						  return( true);
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
				  return( true);
			  }
		  }

		  return( false);
	  }
  };
};
