// Copyright 2009 Peter Stegemann

#include "65K_RGB.h"

#include "AVR/Source/Utility.h"

#include <stdio.h>

LCD_65K_RGB::LCD_65K_RGB( void)
           : lightness( LCD_65K_RGB_BACKLIGHT_FULL)
           , blanked( false)
{
}

LCD_65K_RGB::~LCD_65K_RGB( void)
{
}

void LCD_65K_RGB::setDimensions( uint16_t Width, uint16_t Height)
{
	width = Width;
	height = Height;
}

void LCD_65K_RGB::setBacklight( uint8_t Backlight)
{
	lightness = Backlight;
}

void LCD_65K_RGB::setBlanked( bool Blanked)
{
	blanked = Blanked;
}

void LCD_65K_RGB::setOrientation( Orientation UseOrientation)
{
	orientation = UseOrientation;
}

void LCD_65K_RGB::drawLine( uint16_t StartX, uint16_t StartY, uint16_t StopX, uint16_t StopY, LCD_65K_RGB::Color Color)
{
	int16_t Rise = StopY - StartY;
	int16_t Width = StopX - StartX;

	// Special case for vertical and horizontal lines.
	if( Width == 0)
	{
		DrawVerticalLine( StartX, StartY, Rise, Color);

		return;
	}

	if( Rise == 0)
	{
		DrawHorizontalLine( StartX, StartY, Width, Color);

		return;
	}

	uint16_t AbsRise = abs( Rise);
	uint16_t AbsWidth = abs( Width);

	// All other Lines.
	uint16_t Steps;

	if( AbsRise > AbsWidth)
	{
		Steps = AbsRise;
	}
	else
	{
		Steps = AbsWidth;
	}

	uint16_t Count = 0;

	while( Count <= Steps)
	{
		uint16_t CurrentX = StartX + (( Width * ( int32_t) Count) / Steps);
		uint16_t CurrentY = StartY + (( Rise * ( int32_t) Count) / Steps);

		drawPixel( CurrentX, CurrentY, Color);

		Count++;
	}
}

uint16_t LCD_65K_RGB::GetWidth( void)
{
	if( orientation & O_Landscape)
	{
		return( height);
	}
	else
	{
		return( width);
	}
}

uint16_t LCD_65K_RGB::GetHeight( void)
{
	if( orientation & O_Landscape)
	{
		return( width);
	}
	else
	{
		return( height);
	}
}

uint8_t LCD_65K_RGB::GetBacklight( void)
{
	return( lightness);
}

bool LCD_65K_RGB::GetBlanked( void)
{
	return( blanked);
}

void LCD_65K_RGB::SetOrientation( Orientation UseOrientation)
{
	orientation = UseOrientation;
}

LCD_65K_RGB::Orientation LCD_65K_RGB::GetOrientation( void)
{
	return( orientation);
}

void LCD_65K_RGB::Clear( LCD_65K_RGB::Color Color)
{
	fillRect( 0, 0, GetWidth(), GetHeight(), Color);
}

void LCD_65K_RGB::DrawPixel( uint16_t Left, uint16_t Top, LCD_65K_RGB::Color Color)
{
	drawPixel( Left, Top, Color);
}

void LCD_65K_RGB::DrawDot( uint16_t Left, uint16_t Top, LCD_65K_RGB::Color Color)
{
	drawPixel( Left - 1, Top, Color);
	drawPixel( Left, Top - 1, Color);
	drawPixel( Left, Top, Color);
	drawPixel( Left, Top + 1, Color);
	drawPixel( Left + 1, Top, Color);
}

void LCD_65K_RGB::DrawVerticalLine( uint16_t Left, uint16_t Top, int16_t Height,
								    LCD_65K_RGB::Color Color)
{
	fillRect( Left, Top, 1, Height, Color);
}

void LCD_65K_RGB::DrawHorizontalLine( uint16_t Left, uint16_t Top, int16_t Width,
									  LCD_65K_RGB::Color Color)
{
	fillRect( Left, Top, Width, 1, Color);
}

void LCD_65K_RGB::DrawLine( uint16_t StartX, uint16_t StartY, uint16_t StopX, uint16_t StopY,
						    LCD_65K_RGB::Color Color)
{
	drawLine( StartX, StartY, StopX, StopY, Color);
}
/*
 void LCD_65K_RGB::DrawLine( uint16_t StartX, uint16_t StartY, uint16_t StopX, uint16_t StopY,
 LCD_65K_RGB::Color ForegroundColor)
 {
 int16_t Width = StopX - StartX;
 int16_t Rise = StopY - StartY;
 
 // Special case for vertical lines.
 if( Width == 0)
 {
 LCD_65K_RGB::DrawVerticalLine( StartX, StartY, Rise, ForegroundColor);
 
 return;
 }
 
 // Special case for horizontal lines.
 if( Rise == 0)
 {
 LCD_65K_RGB::DrawHorizontalLine( StartX, StopX, Width, ForegroundColor);
 
 return;
 }
 
 uint16_t AbsRise = abs( Rise);
 uint16_t AbsWidth = abs( Width);
 
 int8_t YDirection;
 int8_t XDirection;
 
 if( Rise < 0)
 {
 YDirection = -1;
 }
 else
 {
 YDirection = 1;
 }
 
 if( Width < 0)
 {
 XDirection = -1;
 }
 else
 {
 XDirection = 1;
 }
 
 // Special case for 45 degrees!
 if( AbsRise == AbsWidth)
 {
 uint16_t Count = 0;
 
 while( Count <= AbsRise)
 {
 LCD_65K_RGB::drawPixel( StartX, StartY, ForegroundColor);
 
 StartX += XDirection;
 StartY += YDirection;
 
 Count++;
 }
 
 return;
 }
 
 // All other Lines.
 uint16_t Steps;
 
 if( AbsRise > AbsWidth)
 {
 Steps = AbsRise;
 }
 else
 {
 Steps = AbsWidth;
 }
 
 uint16_t Count = 1;
 
 uint16_t BeginX = StartX;
 uint16_t BeginY = StartY;
 uint16_t CurrentX = StartX;
 uint16_t CurrentY = StartY;
 
 while( Count <= Steps)
 {
 if( AbsRise > AbsWidth)
 {
 CurrentX = StartX + (( Width * ( int32_t) Count) / Steps);
 
 // Use vertical lines.
 if( CurrentX != BeginX)
 {
 CurrentY = StartY + ( YDirection * ( int32_t) ( Count - 1));
 
 LCD_65K_RGB::DrawVerticalLine( BeginX, BeginY, CurrentY - BeginY, ForegroundColor);
 
 BeginX = CurrentX;
 BeginY = StartY + ( YDirection * ( int32_t) Count);
 }
 }
 else
 {
 CurrentY = StartY + (( Rise * ( int32_t) Count) / Steps);
 
 // Use horizontal lines.
 if( CurrentY != BeginY)
 {
 CurrentX = StartX + ( XDirection * ( int32_t) ( Count - 1));
 
 LCD_65K_RGB::DrawHorizontalLine( BeginX, BeginY, CurrentX - BeginX, ForegroundColor);
 
 BeginX = StartX + ( XDirection * ( int32_t) Count);
 BeginY = CurrentY;
 }
 }
 
 Count++;
 }
 
 // Draw last.
 if( AbsRise > AbsWidth)
 {
 CurrentY = StartY + ( YDirection * ( int32_t) ( Count - 1));
 
 // Use vertical lines.
 LCD_65K_RGB::DrawVerticalLine( BeginX, BeginY, CurrentY - BeginY, ForegroundColor);
 }
 else
 {
 CurrentX = StartX + ( XDirection * ( int32_t) ( Count - 1));
 
 // Use horizontal lines.
 DrawHorizontalLine( BeginX, BeginY, CurrentX - BeginX, ForegroundColor);
 }
 }
 */

void LCD_65K_RGB::FillRect( uint16_t Left, uint16_t Top, int16_t Width, int16_t Height,
						    LCD_65K_RGB::Color Color, RectOptions UseRectOptions)
{
	fillRect( Left, Top, Width, Height, Color, UseRectOptions);
}

void LCD_65K_RGB::DrawRect( uint16_t Left, uint16_t Top, int16_t Width, int16_t Height,
						    LCD_65K_RGB::Color Color, RectOptions UseRectOptions)
{
	if( UseRectOptions & RO_Rounded)
	{
		// Draw top, bottom, left, right.
		DrawHorizontalLine( Left + 1, Top, Width - 2, Color);
		DrawHorizontalLine( Left + 1, Top + Height - 1, Width - 2, Color);
	}
	else
	{
		// Draw top, bottom, left, right.
		DrawHorizontalLine( Left, Top, Width, Color);
		DrawHorizontalLine( Left, Top + Height - 1, Width, Color);
	}

	DrawVerticalLine( Left, Top + 1, Height - 2, Color);
	DrawVerticalLine( Left + Width - 1, Top + 1, Height - 2, Color);
}

uint16_t LCD_65K_RGB::Print( uint16_t Left, uint16_t Top, FONT::FontId UseFontId,
							 LCD_65K_RGB::Color ForegroundColor, LCD_65K_RGB::Color BackgroundColor,
							 PrintOptions UsePrintOptions, const char* String)
{
	return( print( Left, Top, UseFontId, ForegroundColor, BackgroundColor, UsePrintOptions, String));
}

uint16_t LCD_65K_RGB::PrintFormat( uint16_t Left, uint16_t Top, FONT::FontId UseFontId,
								   LCD_65K_RGB::Color ForegroundColor,
								   LCD_65K_RGB::Color BackgroundColor,
								   PrintOptions UsePrintOptions, const char* Format, ...)
{
	va_list Arguments;
    va_start( Arguments, Format);

	uint16_t Result =
		PrintFormatVAList( Left, Top, UseFontId, ForegroundColor, BackgroundColor, UsePrintOptions,
						   Format, &Arguments);

    va_end( Arguments);

	return( Result);
}

uint16_t LCD_65K_RGB::PrintFormatVAList( uint16_t Left, uint16_t Top, FONT::FontId UseFontId,
										 LCD_65K_RGB::Color ForegroundColor,
										 LCD_65K_RGB::Color BackgroundColor,
										 PrintOptions UsePrintOptions, const char* Format,
										 va_list* Arguments)
{
	// Sorry, no more than 60 characters.
	char String[ 60];

	vsnprintf( String, sizeof( String), Format, *Arguments);

	return( print( Left, Top, UseFontId, ForegroundColor, BackgroundColor, UsePrintOptions, String));
}

uint16_t LCD_65K_RGB::Print_P( uint16_t Left, uint16_t Top, FONT::FontId UseFontId,
							   LCD_65K_RGB::Color ForegroundColor,
							   LCD_65K_RGB::Color BackgroundColor,
							   PrintOptions UsePrintOptions, const flash_char* String)
{
	// Sorry, no more than 60 characters.
	char LocalString[ 60];

	strncpy_P( LocalString, String, sizeof( LocalString));

	return( print( Left, Top, UseFontId, ForegroundColor, BackgroundColor, UsePrintOptions, LocalString));
}

uint16_t LCD_65K_RGB::PrintFormat_P( uint16_t Left, uint16_t Top, FONT::FontId UseFontId,
									 LCD_65K_RGB::Color ForegroundColor,
									 LCD_65K_RGB::Color BackgroundColor,
									 PrintOptions UsePrintOptions, const flash_char* Format, ...)
{
	va_list Arguments;
    va_start( Arguments, Format);

	uint16_t Result =
		PrintFormatVAList_P( Left, Top, UseFontId, ForegroundColor, BackgroundColor,
							 UsePrintOptions, Format, &Arguments);

    va_end( Arguments);

	return( Result);
}

uint16_t LCD_65K_RGB::PrintFormatVAList_P( uint16_t Left, uint16_t Top, FONT::FontId UseFontId,
										   LCD_65K_RGB::Color ForegroundColor,
										   LCD_65K_RGB::Color BackgroundColor,
										   PrintOptions UsePrintOptions, const flash_char* Format,
										   va_list* Arguments)
{
	// Sorry, no more than 60 characters.
	char String[ 60];

	vsnprintf_P( String, sizeof( String), Format, *Arguments);

	return( print( Left, Top, UseFontId, ForegroundColor, BackgroundColor, UsePrintOptions, String));
}
