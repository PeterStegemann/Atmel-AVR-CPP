// Copyright 2009 Peter Stegemann

#include "LCD_DOG_M132.h"

#include "AVR/Components/Utility.h"

#define LCD_DOG_M132_USED_BITS			/*UTILITY_BitValue( LCD_DOG_SELECT) |*/ UTILITY_BitValue( LCD_DOG_LIGHT)

#define LCD_DOG_M132_SetBit( Bit)		SetBit( LCD_DOG_PORT, Bit)
#define LCD_DOG_M132_ClearBit( Bit)	UTILITY_ClearBit( LCD_DOG_PORT, Bit)

#define LCD_DOG_M132_COLUMNS			132
#define LCD_DOG_M132_PAGES				4

#define LCD_DOG_M132_COLUMN_OFFSET		30

#define LCD_DOG_M132_DISPLAY_OFF					0b10101110
#define LCD_DOG_M132_DISPLAY_ON						0b10101111

#define LCD_DOG_M132_START_LINE						0b01000000

#define LCD_DOG_M132_PAGE_ADDRESS					0b10110000

#define LCD_DOG_M132_ADDRESS_UPPER					0b00010000
#define LCD_DOG_M132_ADDRESS_LOWER					0b00000000

#define LCD_DOG_M132_ADC_SELECT_NORMAL				0b10100000
#define LCD_DOG_M132_ADC_SELECT_REVERSE				0b10100001

#define LCD_DOG_M132_DISPLAY_NORMAL					0b10100110
#define LCD_DOG_M132_DISPLAY_REVERSE				0b10100111

#define LCD_DOG_M132_BIAS_1_9						0b10100010
#define LCD_DOG_M132_BIAS_1_7						0b10100011

#define LCD_DOG_M132_INTERNAL_RESET					0b11100010

#define LCD_DOG_M132_COMMON_OUTPUT_NORMAL			0b11000000
#define LCD_DOG_M132_COMMON_OUTPUT_REVERSE			0b11001000

#define LCD_DOG_M132_INTERNAL_POWER					0b00101000

#define LCD_DOG_M132_RESISTOR_RATIO					0b00100000

#define LCD_DOG_M132_ELECTRONIC_VOLUME_MODE			0b10000001
#define LCD_DOG_M132_ELECTRONIC_VOLUME_REGISTER		0b00000000

#define LCD_DOG_M132_STATIC_INDICATOR_OFF			0b10101100
#define LCD_DOG_M132_STATIC_INDICATOR_ON			0b10101101
#define LCD_DOG_M132_STATIC_INDICATOR_REGISTER		0b00000000

#define LCD_DOG_M132_BOOSTER_RATIO					0b11111000
#define LCD_DOG_M132_BOOSTER_RATIO_234				0b00000000
#define LCD_DOG_M132_BOOSTER_RATIO_5				0b00000001
#define LCD_DOG_M132_BOOSTER_RATIO_6				0b00000011

LCD_DOG_M132::LCD_DOG_M132( void)
            : LCD_DOG( LCD_DOG_M132_COLUMNS, LCD_DOG_M132_PAGES)
{
}

void LCD_DOG_M132::initialize( void)
{
	// All Ports to output
	LCD_DOG_DDR |= LCD_DOG_M132_USED_BITS;

	// Select.
	select();

	SPI::SendCommandByte( LCD_DOG_M132_START_LINE | 0b00000);
	SPI::SendCommandByte( LCD_DOG_M132_ADC_SELECT_NORMAL);
//	spiSendCommandByte( LCD_DOG_M132_ADC_SELECT_REVERSE);
//	spiSendCommandByte( LCD_DOG_M132_COMMON_OUTPUT_NORMAL);
	SPI::SendCommandByte( LCD_DOG_M132_COMMON_OUTPUT_REVERSE);
	SPI::SendCommandByte( LCD_DOG_M132_DISPLAY_NORMAL);
//	SPI::SendCommandByte( LCD_DOG_M132_DISPLAY_REVERSE);
	SPI::SendCommandByte( LCD_DOG_M132_BIAS_1_9);
	SPI::SendCommandByte( LCD_DOG_M132_INTERNAL_POWER);
	SPI::SendCommandByte( LCD_DOG_M132_BOOSTER_RATIO);
	SPI::SendCommandByte( LCD_DOG_M132_BOOSTER_RATIO_234);
	SPI::SendCommandByte( LCD_DOG_M132_RESISTOR_RATIO | 0b011);
	SPI::SendCommandByte( LCD_DOG_M132_ELECTRONIC_VOLUME_MODE);
	SPI::SendCommandByte( 0x1f); // 00011000
	SPI::SendCommandByte( LCD_DOG_M132_STATIC_INDICATOR_OFF);
	SPI::SendCommandByte( 0x00);
	SPI::SendCommandByte( LCD_DOG_M132_DISPLAY_ON);

	deselect();
}

void LCD_DOG_M132::select( void)
{
	// Select.
	SPI::Select( LCD_DOG_SPI_ID);
}

void LCD_DOG_M132::deselect( void)
{
	// Deselect.
	SPI::Deselect( LCD_DOG_SPI_ID);
}

void LCD_DOG_M132::setPage( uint8_t Page)
{
	SPI::SendCommandByte( LCD_DOG_M132_PAGE_ADDRESS | Page);
}

void LCD_DOG_M132::setColumn( uint8_t Column)
{
	Column += LCD_DOG_M132_COLUMN_OFFSET;

	SPI::SendCommandByte( LCD_DOG_M132_ADDRESS_UPPER | (( Column & 0xf0) >> 4));
	SPI::SendCommandByte( LCD_DOG_M132_ADDRESS_LOWER | ( Column & 0x0f));
}

void LCD_DOG_M132::write( uint8_t Data)
{
	SPI::SendDataByte( Data);
}

void LCD_DOG_M132::setBacklight( void)
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

void LCD_DOG_M132::setContrast( void)
{
	uint16_t Normalized = GetContrast() * 25 / 100;

	select();

		Not done.

	deselect();
}

void LCD_DOG_M132::setInverted( void)
{
	select();

	if( inverted == true)
	{
		SPI::SendCommandByte( LCD_DOG_M132_DISPLAY_REVERSE);
	}
	else
	{
		SPI::SendCommandByte( LCD_DOG_M132_DISPLAY_NORMAL);
	}

	deselect();
}
