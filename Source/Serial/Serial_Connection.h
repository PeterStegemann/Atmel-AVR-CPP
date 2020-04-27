// Copyright 2008 Peter Stegemann

#ifndef SERIAL_CONNECTION_H
#define SERIAL_CONNECTION_H

#include "Serial_Device.h"
#include "Serial_Protocol.h"

#include "AVR/Components/Types.h"

template <uint8_t DeviceId>
class SERIAL_Connection
{
  protected:
	SERIAL_Device< DeviceId, 10> rawSerial;

  public:
	virtual ~SERIAL_Connection( void)
	{
	}

	void Initialize( void)
	{
		rawSerial.Initialize();
	}

	bool SendBoolean( bool Boolean, SERIAL::TransferOptions UseOptions = SERIAL::TO_Block)
	{
		return( SendByte( Boolean ? 1 : 0, UseOptions));
	}

	bool ReceiveBoolean( bool* Boolean, SERIAL::TransferOptions UseOptions = SERIAL::TO_Block)
	{
		uint8_t Byte;
		
		if( ReceiveByte( &Byte, UseOptions) == false)
		{
			return( false);
		}

		*Boolean = ( Byte == 1);

		return( true);
	}

	bool SendByte( uint8_t Byte, SERIAL::TransferOptions UseOptions = SERIAL::TO_Block)
	{
		if( rawSerial.SendByte( Byte, UseOptions) == false)
		{
			return( false);
		}

		// Wait for echo to come back.
		return( rawSerial.ReceiveByte( &Byte, UseOptions));
	}

	bool ReceiveByte( uint8_t* Byte, SERIAL::TransferOptions UseOptions = SERIAL::TO_Block)
	{
		if( rawSerial.ReceiveByte( Byte, UseOptions) == false)
		{
			return( false);
		}

		// Echo byte.
		return( rawSerial.SendByte( *Byte, UseOptions));
	}

	bool SendWord( uint16_t Word, SERIAL::TransferOptions UseOptions = SERIAL::TO_Block)
	{
		return( SendByte( Word >> 8, UseOptions) && SendByte( Word & 0xff, UseOptions));
	}

	bool ReceiveWord( uint16_t* Word, SERIAL::TransferOptions UseOptions = SERIAL::TO_Block)
	{
		uint8_t Byte;

		if( ReceiveByte( &Byte, UseOptions) == false)
		{
			return( false);
		}

		*Word = Byte;

		*Word = *Word << 8;

		if( ReceiveByte( &Byte, UseOptions) == false)
		{
			return( false);
		}

		*Word = *Word | Byte;

		return( true);
	}

	bool SendString( const char* String, SERIAL::TransferOptions UseOptions = SERIAL::TO_Block)
	{
		while( true)
		{
			if( SendByte( *String, UseOptions) == false)
			{
				return( false);
			}

			if( *String == 0)
			{
				return( true);
			}

			String++;
		}
	}

	bool ReceiveString( char* String, uint8_t BufferLength,
		SERIAL::TransferOptions UseOptions = SERIAL::TO_Block)
	{
		uint8_t Count = 0;

		while( true)
		{
			uint8_t Byte;

			if( ReceiveByte( &Byte, UseOptions) == false)
			{
				String[ Count] = 0;

				return( false);
			}

			// Too short?
			if( Byte == 0)
			{
				String[ Count] = 0;

				return( false);
			}

			String[ Count] = Byte;

			Count++;

			if( Count == ( BufferLength - 1))
			{
				String[ Count] = 0;

				return( true);
			}
		}
	}
};

#endif
