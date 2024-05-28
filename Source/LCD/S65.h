// Copyright 2007 Peter Stegemann

#pragma once

#include "65K_RGB_Window.h"

#include "AVR/Source/Types.h"

class LCD_S65 : public LCD_65K_RGB_Window
{
	private:
		void select( void);
		void deselect( void);

		virtual void windowStart( uint16_t Left, uint16_t Top, int16_t Width, int16_t Height);
		virtual void pushPixel( LCD_65K_RGB::Color Color);
		virtual void windowEnd( void);

		// Optimize rect drawing.
//		virtual void fillRect( uint16_t Left, uint16_t Top, int16_t Width, int16_t Height,
//							   LCD_65K_RGB::Color ForegroundColor,
//							   RectOptions UseRectOptions = RO_None);

	public:
		virtual ~LCD_S65( void);

		virtual void Initialize( void);
		virtual void Initialize( uint8_t Backlight);

		virtual void SetBacklight( uint8_t Backlight);
		virtual void SetOrientation( Orientation UseOrientation);
};
