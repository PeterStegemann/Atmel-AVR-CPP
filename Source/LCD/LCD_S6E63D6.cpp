// Copyright 2009 Peter Stegemann

#include "LCD_S6E63D6.h"

#include "LCD_S6E63D6_Defines.h"
#include "Ports.h"

#include "AVR/Source/Utility.h"

LCD_S6E63D6::~LCD_S6E63D6( void)
{
}

void LCD_S6E63D6::windowStart( uint16_t Left, uint16_t Top, int16_t Width, int16_t Height)
{
	// If we're using the display rotated, Left + Width go to the vertical registers, Top + Height
	// go to the horizontal ones.
	uint16_t HorizontalStart, HorizontalEnd, VerticalStart, VerticalEnd, GRAMLow, GRAMHigh;

	Orientation CurrentOrientation = GetOrientation();

	if( CurrentOrientation & O_Landscape)
	{
		if( !( CurrentOrientation & O_HorizontalFlip))
		{
			Left = LCD_S6E63D6_HEIGHT - ( Left + Width);
		}

		if( !( CurrentOrientation & O_VerticalFlip))
		{
			Top = LCD_S6E63D6_WIDTH - ( Top + Height);
		}

		HorizontalStart = Top;
		HorizontalEnd = HorizontalStart + Height - 1;
		VerticalStart = Left;
		VerticalEnd = VerticalStart + Width - 1;		

		if( CurrentOrientation & O_HorizontalFlip)
		{
			GRAMHigh = VerticalStart;
		}
		else
		{
			GRAMHigh = VerticalEnd;
		}

		if( CurrentOrientation & O_VerticalFlip)
		{
			GRAMLow = HorizontalStart;
		}
		else
		{
			GRAMLow = HorizontalEnd;
		}
	}
	else
	{
		HorizontalStart = Left;
		HorizontalEnd = HorizontalStart + Width - 1;
		VerticalStart = Top;
		VerticalEnd = VerticalStart + Height - 1;

		GRAMHigh = VerticalStart;
		GRAMLow = HorizontalStart;
	}

	// 22. Vertical RAM address position (R35h, R36h) : VSA8_0=0_0000_0000, VEA8_0=1_0011_1111 (319)
	// 23. Horizontal RAM address position (R37h) : HAS7_0=0000_0000, HEA7_0=1110_1111 (239)
	command( LCD_S6E63D6_VERTICAL_RAM_ADDRESS_START, VerticalStart);
	command( LCD_S6E63D6_VERTICAL_RAM_ADDRESS_END, VerticalEnd);
	command( LCD_S6E63D6_HORIZONTAL_RAM_ADDRESS, ( HorizontalStart << 8) | HorizontalEnd);

	command( LCD_S6E63D6_GRAM_ADDRESS_SET_LOW, GRAMLow);
	command( LCD_S6E63D6_GRAM_ADDRESS_SET_HIGH, GRAMHigh);

	index( LCD_S6E63D6_GRAM_WRITE);
}

void LCD_S6E63D6::pushPixel( LCD_65K_RGB::Color Color)
{
	parameter( Color);
}

void LCD_S6E63D6::windowEnd( void)
{
	index( LCD_S6E63D6_TERMINATE_GRAM_WRITE);
}

void LCD_S6E63D6::command( uint8_t Index, uint16_t Parameter)
{
	index( Index);
	parameter( Parameter);
}

void LCD_S6E63D6::configureOrientation( void)
{
	Orientation CurrentOrientation = GetOrientation();

	if( CurrentOrientation & O_Portrait)
	{
		// Portrait
	}
	else
	{
		// Landscape
		if( CurrentOrientation & O_VerticalFlip)
		{
			// Vertical flip
			if( CurrentOrientation & O_HorizontalFlip)
			{
				// Horizontal flip
				command( LCD_S6E63D6_ENTRY_MODE,
						 LCD_S6E63D6_ENTRY_MODE_ID0 | LCD_S6E63D6_ENTRY_MODE_ID1 |
						 LCD_S6E63D6_ENTRY_MODE_AM);
			}
			else
			{
				// No horizontal flip
				command( LCD_S6E63D6_ENTRY_MODE,
						 LCD_S6E63D6_ENTRY_MODE_ID0 | LCD_S6E63D6_ENTRY_MODE_AM);
			}
		}
		else
		{
			// No vertical flip
			if( CurrentOrientation & O_HorizontalFlip)
			{
				// Horizontal flip
				command( LCD_S6E63D6_ENTRY_MODE,
						 LCD_S6E63D6_ENTRY_MODE_ID1 | LCD_S6E63D6_ENTRY_MODE_AM);
			}
			else
			{
				// No horizontal flip
				command( LCD_S6E63D6_ENTRY_MODE, LCD_S6E63D6_ENTRY_MODE_AM);
			}
		}
	}
}

void LCD_S6E63D6::SetBacklight( uint8_t Backlight)
{
	setBacklight( Backlight);
}

void LCD_S6E63D6::SetBlanked( bool Blanked)
{
	setBlanked( Blanked);

	if( Blanked == true)
	{
		// Make sure gate power is off.
		LCD_S6E63D6_ClearBit( LCD_S6E63D6_POWER);
	}
	else
	{
		// Gate power on.
		LCD_S6E63D6_SetBit( LCD_S6E63D6_POWER);
	}
}

void LCD_S6E63D6::SetOrientation( Orientation UseOrientation)
{
	setOrientation( UseOrientation);

	configureOrientation();
}
