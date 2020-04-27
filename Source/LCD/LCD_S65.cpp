// Copyright 2007 Peter Stegemann

#include "LCD_S65.h"

#include "Ports.h"

#include "AVR/Components/SPI.h"
#include "AVR/Components/Utility.h"

#define LCD_S65_USED_BITS			/* UTILITY_BitValue( LCD_S65_SELECT) | */ UTILITY_BitValue( LCD_S65_LIGHT)

#define LCD_S65_SetBit( Bit)		SetBit( LCD_S65_PORT, Bit)
#define LCD_S65_ClearBit( Bit)		UTILITY_ClearBit( LCD_S65_PORT, Bit)

#define LCD_S65_WIDTH		132
#define LCD_S65_HEIGHT		176

const flash_uint16_t InitData[] PROGMEM =
{ 
	0xFDFD, 0xFDFD, 
	// pause 
	0xEF00, 0xEE04, 0x1B04, 0xFEFE, 0xFEFE, 
	0xEF90, 0x4A04, 0x7F3F, 0xEE04, 0x4306, 
	// pause 
	0xEF90, 0x0983, 0x0800, 0x0BAF, 0x0A00, 
	0x0500, 0x0600, 0x0700, 0xEF00, 0xEE0C, 
	0xEF90, 0x0080, 0xEFB0, 0x4902, 0xEF00, 
	0x7F01, 0xE181, 0xE202, 0xE276, 0xE183, 
	0x8001, 0xEF90, 0x0000 
};

LCD_S65::~LCD_S65( void)
{
}

void LCD_S65::select( void)
{
	// Select.
	SPI::Select( LCD_S65_SPI_ID);
}

void LCD_S65::deselect( void)
{
	// Deselect.
	SPI::Deselect( LCD_S65_SPI_ID);
}

void LCD_S65::windowStart( uint16_t Left, uint16_t Top, int16_t Width, int16_t Height)
{
	if(( Width == 0) || ( Height == 0))
	{
		return;
	}

	uint16_t Right = Left + Width - 1;
	uint16_t Bottom = Top + Height - 1;

	uint8_t data[] =
	{
		0xEF, 0x08,
		0x18, 0x00,
		0x12, Left,
		0x15, Right,
		0x13, Top,
		0x16, Bottom 
	};

	Orientation CurrentOrientation = GetOrientation();

	// This is not completely finished, only landscape is complete.
	if( CurrentOrientation & O_Portrait)
	{
		if( CurrentOrientation & O_HorizontalFlip)
		{
			data[ 3] = 0x03;		// Mode
			data[ 5] = LCD_S65_WIDTH - 1 - Left;
			data[ 7] = LCD_S65_WIDTH - 1 - Right;
			data[ 9] = LCD_S65_HEIGHT - 1 - Top;
			data[ 11] = LCD_S65_HEIGHT - 1 - Bottom;
		}
		else
		{
			data[ 3] = 0x00;		// Mode
			data[ 5] = Left;
			data[ 7] = Right;
			data[ 9] = Top;
			data[ 11] = Bottom;
		}
	}
	else
	{
		if( CurrentOrientation & O_HorizontalFlip)
		{
			// Information on mode Landscape180: At this mode the display seems to have a bug.
			// Please read the programmers manual for more information or just do not use this mode
			// with  large pictures or large boxes >125 lines in Y-direction
			data[ 3] = 0x06;		// Mode
			data[ 5] = Top;
			data[ 7] = Bottom;
			data[ 9] = LCD_S65_HEIGHT - 1 - Left;
			data[ 11] = LCD_S65_HEIGHT - 1 - Right;
		}
		else
		{
			data[ 3] = 0x05;		// Mode
			data[ 5] = LCD_S65_WIDTH - 1 - Top;
			data[ 7] = LCD_S65_WIDTH - 1 - Bottom;
			data[ 9] = Left;
			data[ 11] = Right;			
		}
	}
/*
	switch( GetOrientation())
	{
		default :
			// Invalid! Fall through to portrait mode
		case O_Portrait :
			// do nothing, data is intitialized for Portrait mode
		break;

		case O_PortraitFlip :
		{
			data[ 3] = 0x03;		// Mode
			data[ 5] = LCD_S65_WIDTH - 1 - Left;
			data[ 7] = LCD_S65_WIDTH - 1 - Right;
			data[ 9] = LCD_S65_HEIGHT - 1 - Top;
			data[ 11] = LCD_S65_HEIGHT - 1 - Bottom;
		}
		break;

		case O_Landscape :
		{
			data[ 3] = 0x05;		// Mode
			data[ 5] = LCD_S65_WIDTH - 1 - Top;
			data[ 7] = LCD_S65_WIDTH - 1 - Bottom;
			data[ 9] = Left;
			data[ 11] = Right;
		}
		break;

		case O_LandscapeFlip :
		{
			// Information on mode Landscape180: At this mode the display seems to have a bug.
			// Please read the programmers manual for more information or just do not use this mode
			// with  large pictures or large boxes >125 lines in Y-direction
			data[ 3] = 0x06;		// Mode
			data[ 5] = Top;
			data[ 7] = Bottom;
			data[ 9] = LCD_S65_HEIGHT - 1 - Left;
			data[ 11] = LCD_S65_HEIGHT - 1 - Right;
		}
		break;
	}
*/
	select();

	SPI::SendDataBytes( data, 12); 
}

void LCD_S65::pushPixel( LCD_65K_RGB::Color Color)
{
	// Send color information.
	SPI::SendCommandWord( Color);
}

void LCD_S65::windowEnd( void)
{
	deselect();
}

/*
void LCD_S65::fillRect( uint16_t Left, uint16_t Top, int16_t Width, int16_t Height,
						LCD_65K_RGB::Color Color, RectOptions UseRectOptions)
{
	if(( Width == 0) || ( Height == 0))
	{
		return;
	}

	if( Width < 0)
	{
		fillRect( Left + Width, Top, -Width, Height, Color);
	}

	if( Height < 0)
	{
		fillRect( Left, Top + Height, Width, -Height, Color);
	}

	// Set drawing window.
	windowStart( Left, Top, Width, Height);

	select();

	uint16_t PixelCount = Width * Height;

	// Feed all pixels.
	while( PixelCount > 0)
	{
		// Send color information.
		SPI::SendCommandWord( Color);

		PixelCount--;
	}

	deselect();
}
*/
void LCD_S65::Initialize( void)
{
	Initialize( LCD_S65_BACKLIGHT_FULL);
}

void LCD_S65::Initialize( uint8_t Backlight)
{
	setDimensions( LCD_S65_WIDTH, LCD_S65_HEIGHT);
	setOrientation( O_Landscape);

	// All Ports to output
	LCD_S65_DDR |= LCD_S65_USED_BITS;

	// Turn light on.
	SetBacklight( LCD_S65_BACKLIGHT_FULL);

	UTILITY::Pause( 300);

	// Select.
	select();

	SPI::SendDataWords_P( &InitData[ 0], 2);
	UTILITY::Pause( 75); 

	SPI::SendDataWords_P( &InitData[ 2], 10);
	UTILITY::Pause( 75);

	SPI::SendDataWords_P( &InitData[ 12], 23); 

	deselect();

	Clear( LCD_65K_RGB::C_Black);

	SetBacklight( Backlight);
}

void LCD_S65::SetBacklight( uint8_t Backlight)
{
	static const uint16_t PWMValue [] = 
	{
		0x0000, 0x001b, 0x001d, 0x0020, 0x0024,
		0x0028, 0x0030, 0x0038, 0x0040, 0x0050,
		0x0060, 0x0070, 0x0080, 0x0090, 0x00a8,
		0x00c0, 0x00f0, 0x0128, 0x0168, 0x0180
	};
	
	if( Backlight > LCD_S65_BACKLIGHT_FULL)
	{
		Backlight = LCD_S65_BACKLIGHT_FULL;
	}

	setBacklight( Backlight);

	uint16_t Normalized = Backlight * ( sizeof( PWMValue) / 2 - 1) / 100;
//	OCR1A = PWMValue[ Normalized];
	OCR1C = PWMValue[ Normalized];

	ICR1 = 0x0180;

	// PWM, phase correct.
	LCD_DOG_TIMERA = ( 1 << WGM11) /*| ( 1 << COM1A1)*/ | ( 1 << COM1C1);
	// Set clock/prescaler 1/256 -> enable counter.
	LCD_DOG_TIMERB = ( 1 << WGM13) | ( 1 << CS11) | ( 1 << CS11);

/*
	OCR1C = PWMValue[ Backlight];

	OCR1A = 0x180;

	// PWM, phase correct.
	LCD_S65_TIMERA = ( 1 << WGM11) | ( 1 << WGM10) | ( 1 << COM1C1);
	// Set clock/prescaler 1/64 -> enable counter.
	LCD_S65_TIMERB = ( 1 << WGM13) | ( 1 << CS11) | ( 1 << CS10);
*/
}

void LCD_S65::SetOrientation( Orientation UseOrientation)
{
	setOrientation( UseOrientation);
}
