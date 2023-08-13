// Copyright 2008 Peter Stegemann

#pragma once

#include "Serial.h"
#include "System.h"

#include "AVR/Source/Types.h"
#include "AVR/Source/Utility.h"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#include <avr/io.h>

template <uint8_t DeviceId, size_t BufferSize>
class SERIAL_Device
{
  private:
    uint8_t id;

    uint8_t buffer[ BufferSize];
    uint8_t bufferStart;
    uint8_t bufferFill;

    bool had0d;

    void fillBuffer( void)
    {
        while( true)
        {
            if( bufferFill == BufferSize)
            {
                // Buffer full.
                return;
            }

            if( readyToReceive() == false)
            {
                // No data available.
                return;
            }

            uint8_t Byte;

            if( DeviceId == 0)
            {
                #if defined( SERIAL_0_UBBR)
                Byte = SERIAL_0_UDR;
                #endif
            }
            else
            {
                #if defined( SERIAL_1_UBBR)
                Byte = SERIAL_1_UDR;
                #endif
            }

            buffer[( bufferStart + bufferFill) % BufferSize] = Byte;
            bufferFill++;
        }
    }

    bool getByteFromBuffer( uint8_t* Byte)
    {
        if( bufferFill == 0)
        {
            // Buffer empty.
            return( false);
        }

        *Byte = buffer[ bufferStart];

        bufferFill--;
        bufferStart = ( bufferStart + 1) % BufferSize;

        return( true);
    }

    bool readyToReceive( void)
    {
        bool Result = false;

        if( DeviceId == 0)
        {
            #if defined( SERIAL_0_UBBR)
            Result = SERIAL_0_UCSRA & ( 1 << SERIAL_0_RXC);
            #endif
        }
        else
        {
            #if defined( SERIAL_1_UBBR)
            Result = SERIAL_1_UCSRA & ( 1 << SERIAL_1_RXC);
            #endif
        }

        return( Result);
    }

    bool readyToSend( void)
    {
        bool Result = false;

        if( DeviceId == 0)
        {
            #if defined( SERIAL_0_UBBR)
            Result = SERIAL_0_UCSRA & ( 1 << SERIAL_0_UDRE);
            #endif
        }
        else
        {
            #if defined( SERIAL_1_UBBR)
            Result = SERIAL_1_UCSRA & ( 1 << SERIAL_1_UDRE);
            #endif
        }

        return( Result);
    }

  public:
    SERIAL_Device( void)
        : bufferStart( 0)
        , bufferFill( 0)
        , had0d( false)
    {
    }

    void Initialize()
    {
        if( DeviceId == 0)
        {
            #if defined( SERIAL_0_UBBR)
            SERIAL_0_UBBR = SERIAL_0_UBBR_VALUE;

            SERIAL_0_UCSRA = SERIAL_0_UCSRA_VALUE;
            SERIAL_0_UCSRB = SERIAL_0_UCSRB_VALUE;
            SERIAL_0_UCSRC = SERIAL_0_UCSRC_VALUE;
            #endif
        }
        else
        {
            #if defined( SERIAL_1_UBBR)
            SERIAL_1_UBBR = SERIAL_1_UBBR_VALUE;

            SERIAL_1_UCSRA = SERIAL_1_UCSRA_VALUE;
            SERIAL_1_UCSRB = SERIAL_1_UCSRB_VALUE;
            SERIAL_1_UCSRC = SERIAL_1_UCSRC_VALUE;
            #endif
        }
    }

    bool ReadyToSend( void)
    {
        return( readyToSend());
    }

    bool ReadyToReceive( void)
    {
        fillBuffer();

        return( bufferFill > 0);
    }

    bool SendByte( uint8_t Byte, SERIAL::TransferOptions UseOptions = SERIAL::TO_Block)
    {
        if( UseOptions & SERIAL::TO_NonBlock)
        {
            if( ReadyToSend() == false)
            {
                return( false);
            }
        }
        else if( UseOptions & SERIAL::TO_ShortBlock)
        {
            uint16_t RetryCount = 500;

            while( true)
            {
                if( ReadyToSend() == true)
                {
                    break;
                }

                if( RetryCount == 0)
                {
                    return( false);
                }

                RetryCount--;

                UTILITY::Pause( 1);
            }
        }
        else
        {
            // In blocking mode, wait until ready to send.
            while( ReadyToSend() == false);
        }

        if( DeviceId == 0)
        {
            #if defined( SERIAL_0_UBBR)
            SERIAL_0_UDR = Byte;
            #endif
        }
        else
        {
            #if defined( SERIAL_1_UBBR)
            SERIAL_1_UDR = Byte;
            #endif
        }

        return( true);
    }

    bool ReceiveByte( uint8_t* Byte, SERIAL::TransferOptions UseOptions = SERIAL::TO_Block)
    {
        if( UseOptions & SERIAL::TO_NonBlock)
        {
            if( ReadyToReceive() == false)
            {
                return( false);
            }
        }
        else if( UseOptions & SERIAL::TO_ShortBlock)
        {
            uint16_t RetryCount = 500;

            while( true)
            {
                if( ReadyToReceive() == true)
                {
                    break;
                }

                if( RetryCount == 0)
                {
                    return( false);
                }

                RetryCount--;

                UTILITY::Pause( 1);
            }
        }
        else
        {
            // In blocking mode, wait until ready to receive.
            while( ReadyToReceive() == false);
        }

        return( getByteFromBuffer( Byte));
    }

    bool SendString( const char* String, SERIAL::TransferOptions UseOptions = SERIAL::TO_Block)
    {
        while( true)
        {
            fillBuffer();

            if( *String == 0)
            {
                return( true);
            }

            if( SendByte( *String, UseOptions) == false)
            {
                return( false);
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

            String[ Count] = Byte;

            // Too short?
            if( Byte == 0)
            {
                return( false);
            }

            Count++;

            if( Count == ( BufferLength - 1))
            {
                String[ Count] = 0;

                return( true);
            }
        }
    }

    bool SendStringFormat( const char* Format, ...)
    {
        va_list Arguments;
        va_start( Arguments, Format);

        bool Result = SendStringFormatVAList( Format, &Arguments);

        va_end( Arguments);

        return( Result);
    }

    bool SendStringFormatVAList( const char* Format, va_list* Arguments)
    {
        // Sorry, no more than 60 characters.
        char String[ 60];

        vsnprintf( String, sizeof( String), Format, *Arguments);

        bool Result = SendString( String);

        return( Result);
    }

    bool SendLine( const char* String, SERIAL::TransferOptions UseOptions = SERIAL::TO_Block)
    {
        return( SendString( String, UseOptions) && SendByte( 0x0a, UseOptions));
    }

    /**
     * @return If a complete line was received.
     */
    bool ReceiveLine( char* String, uint8_t BufferLength, uint8_t* Offset,
                      SERIAL::TransferOptions UseOptions = SERIAL::TO_Block)
    {
        uint8_t Index = *Offset;

        if( Index >= ( BufferLength - 1))
        {
            return( true);
        }

        bool Result = true;

        while( true)
        {
            uint8_t Byte;

            if( ReceiveByte( &Byte, UseOptions) == false)
            {
                Result = false;

                break;
            }

            // Too short?
            if( Byte == 0)
            {
                had0d = false;
                Result = false;

                break;
            }

            // Line end?
            if( Byte == 0x0a)
            {
                if( had0d == true)
                {
                    // Skip this.
                    had0d = false;

                    continue;
                }

                break;
            }

            if( Byte == 0x0d)
            {
                had0d = true;

                break;
            }

            had0d = false;

            String[ Index] = Byte;

            Index++;

            if( Index == ( BufferLength - 1))
            {
                break;
            }
        }

        String[ Index] = 0;
        *Offset = Index;

        return( Result);
    }
};
