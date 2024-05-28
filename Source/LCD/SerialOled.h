// Copyright 2010 Peter Stegemann

#pragma once

#include "65K_RGB.h"
#include "SerialOledProtocol.h"
#include "System.h"

#include "AVR/Source/Types.h"
#include "AVR/Source/Serial/Connection.h"

#define LCD_SERIALOLED_WIDTH		240
#define LCD_SERIALOLED_HEIGHT		320

template< uint8_t DeviceId>
class LCD_SerialOled : public LCD_65K_RGB
{
  private:
	avr::serial::Connection< DeviceId> oledConnection;

	virtual void drawPixel( uint16_t Left, uint16_t Top, LCD_65K_RGB::Color Color)
	{
		oledConnection.SendByte( LCD_SerialOledProtocol::I_DrawPixel);

		oledConnection.SendWord( Left);
		oledConnection.SendWord( Top);
		oledConnection.SendWord( Color);
	}

	virtual void fillRect
	(
	    uint16_t Left, uint16_t Top, int16_t Width, int16_t Height,
	    LCD_65K_RGB::Color Color, RectOptions UseRectOptions
    )
	{
		oledConnection.SendByte( LCD_SerialOledProtocol::I_FillRect);

		oledConnection.SendWord( Left);
		oledConnection.SendWord( Top);
		oledConnection.SendWord( Width);
		oledConnection.SendWord( Height);
		oledConnection.SendWord( Color);
	}

	virtual uint16_t print
	(
	    uint16_t Left, uint16_t Top, avr::font::FontId UseFontId,
		LCD_65K_RGB::Color ForegroundColor, LCD_65K_RGB::Color BackgroundColor,
		PrintOptions UsePrintOptions, const char* String
    )
	{
		oledConnection.SendByte( LCD_SerialOledProtocol::I_Print);

		oledConnection.SendWord( Left);
		oledConnection.SendWord( Top);
		oledConnection.SendByte( UseFontId);
		oledConnection.SendWord( ForegroundColor);
		oledConnection.SendWord( BackgroundColor);
		oledConnection.SendByte( UsePrintOptions);
		oledConnection.SendString( String);

		return 0;
	}

	virtual void drawLine
	(
	    uint16_t StartX, uint16_t StartY, uint16_t StopX, uint16_t StopY, LCD_65K_RGB::Color Color
    )
	{
		oledConnection.SendByte( LCD_SerialOledProtocol::I_DrawLine);

		oledConnection.SendWord( StartX);
		oledConnection.SendWord( StartY);
		oledConnection.SendWord( StopX);
		oledConnection.SendWord( StopY);
		oledConnection.SendWord( Color);
	}

  public:
	virtual ~LCD_SerialOled( void)
	{
	}

	virtual bool Initialize( uint16_t Retries)
	{
		setDimensions( LCD_SERIALOLED_WIDTH, LCD_SERIALOLED_HEIGHT);

		// Initialize serial connection.
		oledConnection.Initialize();

		// Ping display several times to probe whether it is available.
		while( true)
	    {
            bool Result = oledConnection.SendByte( LCD_SerialOledProtocol::I_Ping, avr::serial::TO_ShortBlock);

			if( Result == true)
			{
			    break;
			}

			if( Retries == 0)
			{
			    return( false);
			}

            Retries--;
		}

        // Pull serial line empty to make sure no unexpected ping responses are still around.
        oledConnection.Clear();

		oledConnection.SendByte( LCD_SerialOledProtocol::I_Clear);
		oledConnection.SendWord( LCD_65K_RGB::C_Black);

		return( true);
	}

	virtual void SetBacklight( uint8_t Backlight)
	{
		setBacklight( Backlight);

		oledConnection.SendByte( LCD_SerialOledProtocol::I_Backlight);

		oledConnection.SendByte( Backlight);
	}

	virtual void SetBlanked( bool Blanked)
	{
		setBlanked( Blanked);

		oledConnection.SendByte( LCD_SerialOledProtocol::I_Blank);

		oledConnection.SendBoolean( Blanked);
	}

	virtual void SetOrientation( Orientation UseOrientation)
	{
		setOrientation( UseOrientation);
	}
};
