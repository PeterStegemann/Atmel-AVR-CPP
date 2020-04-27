// Copyright 2008 Peter Stegemann

#ifndef SERIAL_TYPEDCONNECTION_H
#define SERIAL_TYPEDCONNECTION_H

#include "Serial.h"
#include "Serial_Protocol.h"

#include "AVR/Source/Types.h"
#include "AVR/Source/Utility.h"

#include <stdio.h>

#define SERIAL_STRING_SIZE	25

template <uint8_t DeviceId>
class SERIAL_TypedConnection
{
  private:
	SERIAL_Device< DeviceId, 10> serial;

	uint16_t byteCount;

  public:
	char stringBuffer[ SERIAL_STRING_SIZE];

	SERIAL_TypedConnection( void)
	{
		byteCount = 0;
	}
	void Initialize()
	{
		serial.Initialize();
	}

	bool ReadyToReceive( void)
	{
		return serial.ReadyToReceive();
	}

	bool ReadyToSend( void)
	{
		return serial.ReadyToSend();
	}

	void SendState( uint8_t Id)
	{
		SendByte( SERIAL_Protocol::T_State);
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

	void SendInteger( uint8_t Id, int32_t Value)
	{
		char String[ 20];

		snprintf( String, sizeof( String), "%ld", Value);

		SendString( Id, String);
	}

	void SendString( uint8_t Id, const char* Value)
	{
		SendByte( SERIAL_Protocol::T_Value);
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
		SendByte( SERIAL_Protocol::T_Complex);
		SendByte( Id);
	}

	void SendComplexClose( void)
	{
		SendByte( SERIAL_Protocol::T_ComplexEnd);
	}

	void ConsumeItem( uint8_t Type)
	{
		// Eat Id.
		ReceiveByte();

		switch( Type)
		{
			case SERIAL_Protocol::T_State : break;

			case SERIAL_Protocol::T_Value :
			{
				ConsumeValue();
			}
			break;

			case SERIAL_Protocol::T_Complex :
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
				case SERIAL_Protocol::T_ComplexEnd :
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
		uint8_t Byte;

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

#endif
