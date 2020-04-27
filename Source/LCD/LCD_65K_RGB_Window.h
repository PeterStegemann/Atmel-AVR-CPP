// Copyright 2010 Peter Stegemann

#ifndef LCD_65K_RGB_WINDOW_H
#define LCD_65K_RGB_WINDOW_H

#include "LCD_65K_RGB.h"

#include "AVR/Source/Types.h"

class LCD_65K_RGB_Window : public LCD_65K_RGB
{
	protected:
		// Always make sure you don't mix up Left<->Right and Top<->Bottom, except for lines.
		virtual void windowStart( uint16_t Left, uint16_t Top, int16_t Width, int16_t Height) = 0;
		// Push a pixel into the set window.
		virtual void pushPixel( LCD_65K_RGB::Color Color) = 0;
		// Always make sure you don't mix up Left<->Right and Top<->Bottom, except for lines.
		virtual void windowEnd( void);

		// Set a single pixel.
		virtual void drawPixel( uint16_t Left, uint16_t Top, LCD_65K_RGB::Color Color);
		// Fill a rectangle.
		virtual void fillRect( uint16_t Left, uint16_t Top, int16_t Width, int16_t Height,
							   LCD_65K_RGB::Color ForegroundColor,
							   LCD::RectOptions UseRectOptions = RO_None);
		// Returns width in pixels of printed text.
		virtual uint16_t print( uint16_t Left, uint16_t Top, FONT::FontId UseFontId,
							    LCD_65K_RGB::Color ForegroundColor,
							    LCD_65K_RGB::Color BackgroundColor,
							    LCD::PrintOptions UsePrintOptions, const char* String);

	public:
		virtual ~LCD_65K_RGB_Window( void);
};

#endif
