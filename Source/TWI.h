// Copyright 2024 Peter Stegemann

#include "AVR/Source/Types.h"

#include <util/twi.h>

#pragma once

namespace avr
{
  class TWI
  {
    public:
      enum Result
      {
          R_Ok,
          R_Repeat,
          R_Failed
      };

    private:
      static uint8_t write( uint8_t Value)
      {
          TWDR = ( Value);
          TWCR = ( 1 << TWINT) |  ( 1 << TWEN);

          TWI::Wait();

          return( TW_STATUS);
      }

    public:
      static void Wait( void)
      {
          while( !( TWCR & ( 1 << TWINT)));
      }

      static Result Start( void)
      {
          TWCR = ( 1 << TWINT) | ( 1 << TWSTA) | ( 1 << TWEN);

          Wait();

          uint8_t Status = TW_STATUS;

          if( Status == TW_MT_ARB_LOST)
          {
              return( R_Repeat);
          }

          if(( Status != TW_REP_START) && ( Status != TW_START))
          {
              return( R_Failed);
          }

          return( R_Ok);
      }

      static void Stop( void)
      {
          TWCR = ( 1 << TWINT) | ( 1 << TWSTO) | ( 1 << TWEN);
      }

      static Result OpenForRead( uint8_t Device)
      {
          Result TwiResult = Start();

          if( TwiResult != R_Ok)
          {
              return( TwiResult);
          }

          uint8_t Status = write( Device | TW_READ);

          if(( Status == TW_MR_SLA_NACK) || ( Status == TW_MR_ARB_LOST))
		  {
              return( R_Repeat);
          }

  		  if( Status != TW_MR_SLA_ACK)
  		  {
              return( R_Failed);
	      }

          return( R_Ok);
      }

      static Result OpenForWrite( uint8_t Device)
      {
          Result TwiResult = Start();

          if( TwiResult != R_Ok)
          {
              return( TwiResult);
          }

          uint8_t Status = write( Device | TW_WRITE);

          if(( Status == TW_MT_SLA_NACK) || ( Status == TW_MT_ARB_LOST))
		  {
              return( R_Repeat);
          }

  		  if( Status != TW_MT_SLA_ACK)
  		  {
              return( R_Failed);
	      }

          return( R_Ok);
      }

      static TWI::Result WriteValue( uint8_t Value)
      {
          uint8_t Status = write( Value);

          if(( Status == TW_MT_DATA_NACK) || ( Status == TW_MT_ARB_LOST))
          {
              return( TWI::R_Repeat);
          }

          if( Status != TW_MT_DATA_ACK)
          {
              return( TWI::R_Failed);
          }

          return( R_Ok);
      }

      static bool ReadValue( uint8_t* Value, bool Continue)
      {
          // Do read transmission.
          if( Continue == true)
          {
              // Get more bytes after this one.
              TWCR = ( 1 << TWINT) | ( 1 << TWEN) | ( 1 << TWEA);
          }
          else
          {
              // Only byte to get.
              TWCR = ( 1 << TWINT) | ( 1 << TWEN);
          }

          Wait();

          uint8_t Status = TW_STATUS;

          if(( Status == TW_MR_DATA_ACK) || (( Continue == false) && ( Status == TW_MR_DATA_NACK)))
          {
              *Value = TWDR;

              return( true);
          }
		  else
		  {
              return( false);
          }
      }
  };
}
