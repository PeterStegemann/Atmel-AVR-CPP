// Copyright 2009 Peter Stegemann

#include "LCD_DOG_S102.h"

#include "AVR/Source/Utility.h"

#define LCD_DOG_S102_USED_BITS			/*UTILITY_BitValue( LCD_DOG_SELECT) |*/ UTILITY_BitValue( LCD_DOG_LIGHT)

#define LCD_DOG_S102_SetBit( Bit)			UTILITY_SetBit( LCD_DOG_PORT, Bit)
#define LCD_DOG_S102_ClearBit( Bit)		UTILITY_ClearBit( LCD_DOG_PORT, Bit)

#define LCD_DOG_S102_COLUMNS				102
#define LCD_DOG_S102_PAGES					8

#define LCD_DOG_S102_COLUMN_OFFSET			30

#define LCD_DOG_S102_ADDRESS_UPPER					0b00010000
#define LCD_DOG_S102_ADDRESS_LOWER					0b00000000

#define LCD_DOG_S102_DISPLAY_OFF					0b10101110
#define LCD_DOG_S102_DISPLAY_ON						0b10101111

#define LCD_DOG_S102_POWER_CONTROL					0b00101111

#define LCD_DOG_S102_START_LINE						0b01000000
#define LCD_DOG_S102_PAGE_ADDRESS					0b10110000

#define LCD_DOG_S102_RESISTOR_RATIO					0b00100111

#define LCD_DOG_S102_ELECTRONIC_VOLUME_MODE_0		0b10000001
#define LCD_DOG_S102_ELECTRONIC_VOLUME_MODE_1		0b00000000

#define LCD_DOG_S102_ALL_PIXEL_NORMAL				0b10100100
#define LCD_DOG_S102_ALL_PIXEL_ON					0b10100101

#define LCD_DOG_S102_DISPLAY_NORMAL					0b10100110
#define LCD_DOG_S102_DISPLAY_REVERSE				0b10100111

#define LCD_DOG_S102_SEG_DIRECTION_NORMAL			0b10100000
#define LCD_DOG_S102_SEG_DIRECTION_MIRROR			0b10100001

#define LCD_DOG_S102_COM_DIRECTION_NORMAL			0b11000000
#define LCD_DOG_S102_COM_DIRECTION_MIRROR			0b11001000

#define LCD_DOG_S102_INTERNAL_RESET					0b11100010

#define LCD_DOG_S102_BIAS_1_7						0b10100011
#define LCD_DOG_S102_BIAS_1_9						0b10100010

#define LCD_DOG_S102_ADVANCED_PROGRAM_CONTROL_0		0b11111010
#define LCD_DOG_S102_ADVANCED_PROGRAM_CONTROL_1		0b10010000

LCD_DOG_S102::LCD_DOG_S102( void)
            : LCD_DOG( LCD_DOG_S102_COLUMNS, LCD_DOG_S102_PAGES)
{
}

void LCD_DOG_S102::initialize( void)
{
	// All Ports to output
	LCD_DOG_DDR |= LCD_DOG_S102_USED_BITS;

	// Select.
	select();

	SPI::SendCommandByte( LCD_DOG_S102_START_LINE | 0b00000);
	SPI::SendCommandByte( LCD_DOG_S102_SEG_DIRECTION_NORMAL);
//	SPI::SendCommandByte( LCD_DOG_S102_SEG_DIRECTION_MIRROR);
//	SPI::SendCommandByte( LCD_DOG_S102_COM_DIRECTION_NORMAL);
	SPI::SendCommandByte( LCD_DOG_S102_COM_DIRECTION_MIRROR);
	SPI::SendCommandByte( LCD_DOG_S102_ALL_PIXEL_NORMAL);
//	SPI::SendCommandByte( LCD_DOG_S102_ALL_PIXEL_ON);
	SPI::SendCommandByte( LCD_DOG_S102_DISPLAY_NORMAL);
//	SPI::SendCommandByte( LCD_DOG_S102_DISPLAY_REVERSE);
	SPI::SendCommandByte( LCD_DOG_S102_BIAS_1_9);
	SPI::SendCommandByte( LCD_DOG_S102_POWER_CONTROL);
	SPI::SendCommandByte( LCD_DOG_S102_RESISTOR_RATIO | 0b011);
	SPI::SendCommandByte( LCD_DOG_S102_ELECTRONIC_VOLUME_MODE_0);
	SPI::SendCommandByte( LCD_DOG_S102_ELECTRONIC_VOLUME_MODE_1 | 0b010000);
	SPI::SendCommandByte( LCD_DOG_S102_ADVANCED_PROGRAM_CONTROL_0);
	SPI::SendCommandByte( LCD_DOG_S102_ADVANCED_PROGRAM_CONTROL_1);
	SPI::SendCommandByte( LCD_DOG_S102_DISPLAY_ON);

	deselect();
}

void LCD_DOG_S102::select( void)
{
	// Select.
	SPI::Select( LCD_DOG_SPI_ID);
}

void LCD_DOG_S102::deselect( void)
{
	// Deselect.
	SPI::Deselect( LCD_DOG_SPI_ID);
}

void LCD_DOG_S102::setPage( uint8_t Page)
{
	SPI::SendCommandByte( LCD_DOG_S102_PAGE_ADDRESS | Page);
}

void LCD_DOG_S102::setColumn( uint8_t Column)
{
	Column += LCD_DOG_S102_COLUMN_OFFSET;

	SPI::SendCommandByte( LCD_DOG_S102_ADDRESS_UPPER | (( Column & 0xf0) >> 4));
	SPI::SendCommandByte( LCD_DOG_S102_ADDRESS_LOWER | ( Column & 0x0f));
}

void LCD_DOG_S102::sendDataByte( uint8_t Data)
{
	SPI::SendDataByte( Data);
}

void LCD_DOG_S102::setBacklight( void)
{
	static const uint16_t PWMValue [] = 
	{
		0x0000,
		0x0001,	// 01
		0x0002,	// 01
		0x0003,	// 01

		0x0004,	// 01
		0x0006,	// 02
		0x0008,	// 02
		0x000c,	// 04

		0x0010,	// 04
		0x0018,	// 08
		0x0020,	// 08
		0x0030,	// 10

		0x0040,	// 10
		0x0050,	// 10
		0x0060,	// 10
		0x0080,	// 20

		0x00a0,	// 20
		0x00c0,	// 20
		0x00e0,	// 20
		0x0120,	// 40

		0x0180	// 60
	};

	uint8_t Backlight = ( GetBlanked() == true) ? 0 : GetBacklight();

	uint16_t Normalized = Backlight * ( sizeof( PWMValue) / 2 - 1) / 100;
	OCR1A = PWMValue[ Normalized];
//	OCR1C = PWMValue[ Normalized];

	ICR1 = 0x0180;

	// PWM, phase correct.
	LCD_DOG_TIMERA = ( 1 << WGM11) | ( 1 << COM1A1) /*| ( 1 << COM1C1)*/;
	// Set clock/prescaler 1/256 -> enable counter.
	LCD_DOG_TIMERB = ( 1 << WGM13) | ( 1 << CS11) | ( 1 << CS11);
}

void LCD_DOG_S102::setContrast( void)
{
	uint16_t Normalized = GetContrast() * 25 / 100;

	select();

	SPI::SendCommandByte( LCD_DOG_S102_ELECTRONIC_VOLUME_MODE_0);
	SPI::SendCommandByte( LCD_DOG_S102_ELECTRONIC_VOLUME_MODE_1 | ( Normalized & 0b111111));

	deselect();
}

void LCD_DOG_S102::setInverted( void)
{
	select();

	if( GetInverted() == true)
	{
		SPI::SendCommandByte( LCD_DOG_S102_DISPLAY_REVERSE);
	}
	else
	{
		SPI::SendCommandByte( LCD_DOG_S102_DISPLAY_NORMAL);
	}

	deselect();
}
