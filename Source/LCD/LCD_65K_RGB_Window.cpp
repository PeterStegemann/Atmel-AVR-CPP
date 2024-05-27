// Copyright 2010 Peter Stegemann

#include "LCD_65K_RGB_Window.h"

#include "AVR/Source/Utility.h"

#include <stdio.h>

LCD_65K_RGB_Window::~LCD_65K_RGB_Window( void)
{
}

void LCD_65K_RGB_Window::windowEnd( void)
{
}

void LCD_65K_RGB_Window::drawPixel( uint16_t Left, uint16_t Top, LCD_65K_RGB_Window::Color Color)
{
	// Set drawing window.
	windowStart( Left, Top, 1, 1);

	// Send color information.
	pushPixel( Color);

	// End drawing operation to that window.
	windowEnd();
}

void LCD_65K_RGB_Window::fillRect
(
    uint16_t Left, uint16_t Top, int16_t Width, int16_t Height, LCD_65K_RGB::Color Color, RectOptions UseRectOptions
)
{
	if(( Width == 0) || ( Height == 0))
	{
		return;
	}

	if( Width < 0)
	{
		fillRect( Left + Width, Top, -Width, Height, Color, UseRectOptions);

		return;
	}

	if( Height < 0)
	{
		fillRect( Left, Top + Height, Width, -Height, Color, UseRectOptions);

		return;
	}

	// Set drawing window.
	windowStart( Left, Top, Width, Height);

	for( uint16_t HeightCount = Height; HeightCount != 0; HeightCount--)
	{
		for( uint16_t WidthCount = Width; WidthCount != 0; WidthCount--)
		{
			// Send color information.
			pushPixel( Color);
		}
	}

	// End drawing operation to that window.
	windowEnd();
}

uint16_t LCD_65K_RGB_Window::print
(
    uint16_t Left, uint16_t Top, FONT::FontId UseFontId,
    LCD_65K_RGB::Color ForegroundColor, LCD_65K_RGB::Color BackgroundColor,
    PrintOptions UsePrintOptions, const char* String
)
{
	uint16_t PrintWidth = 0;

	const FONT_Type* Font = FONT::GetFont( UseFontId);

	const uint8_t CharacterWidth = Font->getCharacterWidth();
	const uint8_t CharacterHeight = Font->getCharacterHeight();
	const uint8_t CellWidth = Font->getCellWidth();
	const uint8_t CellHeight = Font->getCellHeight();
	const uint8_t CellVerticalPadding = CellHeight - CharacterHeight;

	// Loop over string
	unsigned char Character;

	while(( Character = *String) != 0)
	{
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

		// Set window for single character.
		if( Left >= GetWidth())
		{
			// Not visible, give up.
			return( PrintWidth);
		}

		windowStart( Left, Top, CellWidth, CellHeight);

		// Loop over rows.
		uint8_t CharacterMask = 0;
		uint8_t CharacterRow = 0;

		while( CharacterRow < CellHeight)
		{
			// Fetch byte value of the character's row, but blank out cell padding.
			if( CharacterRow >= CellVerticalPadding)
			{
				uint8_t CharacterByte = pgm_read_byte( &( Font->getData()[ CharacterPosition++]));
				CharacterMask |= CharacterByte;

				// Loop over columns.
				uint8_t CharacterColumn = 0;

				while( CharacterColumn < CellWidth)
				{
					// Print only the printable part, padding is always background.
					if(( CharacterColumn < CharacterWidth) &&
					   UTILITY_GetBit( CharacterByte, ( CharacterWidth - 1) - CharacterColumn))
					{
						pushPixel( ForegroundColor);
					}
					else
					{
						pushPixel( BackgroundColor);
					}

					CharacterColumn++;
				}
			}
			else
			{
				// Loop over columns.
				uint8_t CharacterColumn = 0;

				while( CharacterColumn < CellWidth)
				{
					pushPixel( BackgroundColor);

					CharacterColumn++;
				}
			}

			CharacterRow++;
		}

		// End drawing operation to that window.
		windowEnd();

		// Skip position to next character.
		uint8_t CharacterWidth = CellWidth;

		// For proportional mode, use real width, not cell with. No proportional mode for spaces!
		if(( Character != 0) && ( UsePrintOptions & PO_Proportional))
		{
			if( CharacterMask == 0)
			{
				CharacterWidth = 0;
			}
			else
			{
				while(( CharacterMask & 0x01) == 0)
				{
					CharacterWidth--;
					CharacterMask = CharacterMask >> 1;
				}
			}
		}

		PrintWidth += CharacterWidth;
		Left += CharacterWidth;
	}

	return( PrintWidth);
}
