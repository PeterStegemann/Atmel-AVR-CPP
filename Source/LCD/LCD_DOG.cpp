// Copyright 2009 Peter Stegemann

#include "LCD_DOG.h"

#include "AVR/Source/Utility.h"

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

LCD_DOG::LCD_DOG( uint8_t Columns, uint8_t Pages)
       : columns( Columns)
       , pages( Pages)
       , lightness( LCD_DOG_BACKLIGHT_FULL)
       , contrast( LCD_DOG_CONTRAST_DEFAULT)
       , blanked( false)
	   , inverted( false)
{
}

LCD_DOG::~LCD_DOG( void)
{
}

void LCD_DOG::Initialize( void)
{
	Initialize( LCD_DOG_BACKLIGHT_FULL, LCD_DOG_CONTRAST_DEFAULT, false);
}

void LCD_DOG::Initialize( uint8_t Backlight, uint8_t Contrast, bool Inverted)
{
	initialize();

	Clear();

	// Set contrast.
	SetContrast( Contrast);
	// Turn light on.
	SetBacklight( Backlight);
	// Set inverted.
	SetInverted( Inverted);
}

uint8_t LCD_DOG::GetWidth( void) const
{
	return( columns);
}

uint8_t LCD_DOG::GetHeight( void) const
{
	return( pages * 8);
}

void LCD_DOG::SetBacklight( uint8_t Backlight)
{
	if( Backlight > LCD_DOG_BACKLIGHT_FULL)
	{
		Backlight = LCD_DOG_BACKLIGHT_FULL;
	}

	lightness = Backlight;

	setBacklight();
}

uint8_t LCD_DOG::GetBacklight( void) const
{
	return( lightness);
}

void LCD_DOG::SetBlanked( bool Blanked)
{
	// Filter if this hasn't changed.
	if( blanked != Blanked)
	{
		blanked = Blanked;

		setBacklight();
	}
}

bool LCD_DOG::GetBlanked( void) const
{
	return( blanked);
}

void LCD_DOG::SetContrast( uint8_t Contrast)
{
	contrast = Contrast;

	setContrast();
}

uint8_t LCD_DOG::GetContrast( void) const
{
	return( contrast);
}

void LCD_DOG::SetInverted( bool Inverted)
{
	// Filter if this hasn't changed.
	if( inverted != Inverted)
	{
		inverted = Inverted;

		setInverted();
	}
}

bool LCD_DOG::GetInverted( void) const
{
	return( inverted);
}

void LCD_DOG::Clear( void)
{
	select();

	// Clear
	for( uint8_t Page = 0; Page < pages; Page++)
	{
		setPage( Page);
		setColumn( 0);

		for( uint8_t Column = 0; Column < columns; Column++)
		{
			sendDataByte( 0);
		}
	}

	deselect();
}

uint8_t LCD_DOG::Print( uint8_t Column, uint8_t Page, FONT::FontId UseFontId, const char* String)
{
	return( Print( Column, Page, GetWidth(), UseFontId, String));
}

uint8_t LCD_DOG::Print( uint8_t Column, uint8_t Page, uint8_t Limit, FONT::FontId UseFontId,
						const char* String)
{
	select();

	uint8_t PrintWidth = 0;

	const FONT_Type* Font = FONT::GetFont( UseFontId);

//	const uint8_t CharacterWidth = Font->CharacterWidth;
	const uint8_t CharacterHeight = Font->CharacterHeight;
	uint8_t CellWidth = Font->CellWidth;
//	const uint8_t CellHeight = Font->CellHeight;
//	const uint8_t CellVerticalPadding = CellHeight - CharacterHeight;

	// Loop over string
	unsigned char Character;

	while(( Character = *String) != 0)
	{
		// Check if there's still space left for a character.
		if( Column >= Limit)
		{
			// Not visible, give up.
			break;
		}

		// Move string now so we don't forget it later.
		String++;

		// At the end of the font data some german special characters are defined.
		if(( Character < FONT::C_FirstTotal) || ( Character > FONT::C_LastTotal))
		{
			// Not allowed: change to ?
			Character = '?';
		}

		// Adapt to start of array.
		Character -= FONT::C_FirstTotal;

		// Multiply with the data size of this font.
		uint16_t CharacterPosition = Character * CharacterHeight;

		uint8_t CharacterWidth = 0;

		// This draws 8 bits at a time, from top to bottom.
		uint8_t RowsToGo = CharacterHeight;
		uint8_t CurrentPage = Page;

		// Go on while rows are left over.
		while( RowsToGo > 0)
		{
			uint8_t CurrentRows;

			// No more than 8 at a time.
			if( RowsToGo > 8)
			{
				CurrentRows = 8;
			}
			else
			{
				CurrentRows = RowsToGo;
			}

			RowsToGo -= CurrentRows;

			setPage( CurrentPage++);
			setColumn( Column);

			// Read character from pgm space.
			uint8_t CharacterByte[ 8];

			for( uint8_t Index = 0; Index < 8; Index++)
			{
				CharacterByte[ Index] = pgm_read_byte( &( Font->Data[ CharacterPosition++]));
			}

			// Walk trough each column.
			for( uint8_t CellColumn = 0; CellColumn < CellWidth; CellColumn++)
			{
				if(( Column + CellColumn) >= Limit)
				{
					// Won't fit, trim.
					break;
				}

				uint8_t Byte = 0;

				for( uint8_t Row = 0; Row < CurrentRows; Row++)
				{
					Byte |= (( CharacterByte[ Row] >> ( CellWidth - CellColumn - 1)) & 0x01) << Row;
				}

				sendDataByte( Byte);

				if(( Byte != 0) && ( CellColumn > CharacterWidth))
				{
				   CharacterWidth = CellColumn;
				}
			}
		}

		// Skip position to next character.
		PrintWidth += CharacterWidth + 1;
		Column += CharacterWidth + 1; //CellWidth;
	}

	deselect();

	return( PrintWidth);
}

uint8_t LCD_DOG::PrintFormat( uint8_t Column, uint8_t Page, FONT::FontId UseFontId,
							  const char* Format, ...)
{
	va_list Arguments;
    va_start( Arguments, Format);

	uint8_t Result = PrintFormatVAList( Column, Page, UseFontId, Format, &Arguments);

    va_end( Arguments);

	return( Result);
}

uint8_t LCD_DOG::PrintFormatVAList( uint8_t Column, uint8_t Page, FONT::FontId UseFontId,
									const char* Format, va_list* Arguments)
{
	// Sorry, no more than 30 characters.
	char String[ 30];

	vsnprintf( String, sizeof( String), Format, *Arguments);

	return( Print( Column, Page, UseFontId, String));
}

uint8_t LCD_DOG::Print_P( uint8_t Column, uint8_t Page, FONT::FontId UseFontId,
						  const flash_char* String)
{
	return( Print_P( Column, Page, GetWidth(), UseFontId, String));
}

uint8_t LCD_DOG::Print_P( uint8_t Column, uint8_t Page, uint8_t Limit, FONT::FontId UseFontId,
						  const flash_char* String)
{
	// Sorry, no more than 30 characters.
	char LocalString[ 30];

	strncpy_P( LocalString, String, sizeof( LocalString));

	return( Print( Column, Page, Limit, UseFontId, LocalString));
}

uint8_t LCD_DOG::PrintFormat_P( uint8_t Column, uint8_t Page, FONT::FontId UseFontId,
								const flash_char* Format, ...)
{
	va_list Arguments;
    va_start( Arguments, Format);

	uint8_t Result = PrintFormatVAList_P( Column, Page, UseFontId, Format, &Arguments);

    va_end( Arguments);

	return( Result);
}

uint8_t LCD_DOG::PrintFormatVAList_P( uint8_t Column, uint8_t Page, FONT::FontId UseFontId,
									  const flash_char* Format, va_list* Arguments)
{
	// Sorry, no more than 30 characters.
	char LocalString[ 30];

	vsnprintf_P( LocalString, sizeof( LocalString), Format, *Arguments);

	return( Print( Column, Page, UseFontId, LocalString));
}

void LCD_DOG::Write( uint8_t Data)
{
	select();

	sendDataByte( Data);

	deselect();
}

void LCD_DOG::Write( uint8_t Column, uint8_t Data)
{
	select();

	setColumn( Column);
	sendDataByte( Data);

	deselect();
}

void LCD_DOG::Write( uint8_t Column, uint8_t Page, uint8_t Data)
{
	select();

	setColumn( Column);
	setPage( Page);
	sendDataByte( Data);

	deselect();
}
