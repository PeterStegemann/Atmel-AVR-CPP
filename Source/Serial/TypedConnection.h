// Copyright 2008 Peter Stegemann

#pragma once

#include "Device.h"
#include "Protocol.h"
#include "TransferOptions.h"

#include "AVR/Source/Types.h"
#include "AVR/Source/Utility.h"

#include <stdio.h>

namespace avr::serial
{
  #define SERIAL_STRING_SIZE	25

  template <uint8_t DeviceId>
  class TypedConnection
  {
    private:
      Device< DeviceId, 10> serial;

      uint16_t byteCount;
      char stringBuffer[ SERIAL_STRING_SIZE];

    public:
      TypedConnection( void)
      {
          byteCount = 0;
      }

      void Initialize()
      {
          serial.Initialize();
      }

      char* GetStringBuffer( void)
      {
          return( stringBuffer);
      }

      bool ReadyToReceive( void)
      {
          return( serial.ReadyToReceive());
      }

      bool ReadyToSend( void)
      {
          return( serial.ReadyToSend());
      }

      void SendState( uint8_t Id)
      {
          SendByte( Protocol::T_State);
          SendByte( Id);
      }

      void SendBoolean( uint8_t Id, bool Value)
      {
          if( Value == true)
          {
              SendString( Id, "true");
          }
          else
          {
              SendString( Id, "false");
          }
      }

      void SendLong( uint8_t Id, int32_t Value)
      {
          char String[ 20];

          snprintf( String, sizeof( String), "%ld", Value);

          SendString( Id, String);
      }

      void SendString( uint8_t Id, const char* Value)
      {
          SendByte( Protocol::T_Value);
          SendByte( Id);

          while( *Value)
          {
              SendByte( *Value);

              Value++;
          }

          SendByte( 0x00);
      }

      void SendComplexOpen( uint8_t Id)
      {
          SendByte( Protocol::T_Complex);
          SendByte( Id);
      }

      void SendComplexClose( void)
      {
          SendByte( Protocol::T_ComplexEnd);
      }

      void ConsumeItem( uint8_t Type)
      {
          // Eat id.
          ReceiveByte();

          switch( Type)
          {
              case Protocol::T_State : break;

              case Protocol::T_Value :
              {
                  ConsumeValue();
              }
              break;

              case Protocol::T_Complex :
              {
                  ConsumeComplex();
              }
              break;
          }
      }

      void ConsumeComplex( void)
      {
          bool Loop = true;

          while( Loop)
          {
              uint8_t Type = ReceiveByte();

              switch( Type)
              {
                  case Protocol::T_ComplexEnd :
                  {
                      Loop = false;
                  }
                  break;

                  default :
                  {
                      ConsumeItem( Type);
                  }
                  break;
              }
          }
      }

      void ConsumeValue( void)
      {
          ReceiveValue( stringBuffer, SERIAL_STRING_SIZE);

//	GLOBAL.Lcd.PrintFormat( 0, 10, FONT::FI_Mini, LCD::White, LCD::Black,
//						  LCD::PO_Proportional, "%s", Value);
      }

      void ReceiveValue( char* Value, uint8_t Length)
      {
          uint8_t Count = 0;

          while( true)
          {
              Value[ Count] = ReceiveByte();

              if( Value[ Count] == 0)
              {
                  break;
              }

              if( Count < ( Length - 1))
              {
                  Count++;
              }
          }
      }

      void SendByte( uint8_t Byte)
      {
          serial.SendByte( Byte);

          byteCount++;

          // Wait for echo to come back.
          serial.ReceiveByte( &Byte);
      }

      uint8_t ReceiveByte( void)
      {
          uint8_t Byte = 0;

          serial.ReceiveByte( &Byte);

          byteCount++;

          // Echo byte.
          serial.SendByte( Byte);

          return( Byte);
      }

      uint16_t ReceiveWord( void)
      {
          uint16_t Word = ReceiveByte();

          Word = Word << 8;
          Word = Word | ReceiveByte();

          return( Word);
      }
  };
};
