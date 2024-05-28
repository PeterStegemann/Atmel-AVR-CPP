// Copyright 2009 Peter Stegemann

#include "DOG_S65.h"

#include "AVR/Source/Utility.h"

#define LCD_DOG_S65_COLUMNS				102
#define LCD_DOG_S65_PAGES				8

LCD_DOG_S65::LCD_DOG_S65( void)
           : LCD_DOG( LCD_DOG_S65_COLUMNS, LCD_DOG_S65_PAGES)
{
	column = 0;
	page = 0;
}

void LCD_DOG_S65::initialize( void)
{
	s65.Initialize();
	s65.Clear( LCD_65K_RGB::C_Black);
}

void LCD_DOG_S65::select( void)
{
}

void LCD_DOG_S65::deselect( void)
{
}

void LCD_DOG_S65::setPage( uint8_t Page)
{
	page = Page;
}

void LCD_DOG_S65::setColumn( uint8_t Column)
{
	column = Column;
}

void LCD_DOG_S65::sendDataByte( uint8_t Data)
{
	uint8_t X = column % GetWidth();
	uint8_t Y = ( page * 8) % GetHeight();

	for( uint8_t YOffset = 0; YOffset < 8; YOffset++)
	{
		s65.DrawPixel( X, Y + YOffset,
					   ( Data & ( 1 << YOffset)) ? LCD_65K_RGB::C_White : LCD_65K_RGB::C_Black);
/*		LCD_DOG_S65.FillRect( X, Y + ( YOffset * 2),
							  2, 2,
							  ( Data & ( 1 << YOffset)) ? LCD_65K_RGB::C_White : LCD_65K_RGB::C_Black);
*/	}

	// Move column after write.
	column++;
}

void LCD_DOG_S65::setBacklight( void)
{
	s65.SetBacklight( GetBacklight());
}

void LCD_DOG_S65::setContrast( void)
{
}

void LCD_DOG_M132::setInverted( void)
{
}
