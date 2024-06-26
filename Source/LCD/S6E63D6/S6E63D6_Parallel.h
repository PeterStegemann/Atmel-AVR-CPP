// Copyright 2010 Peter Stegemann

#pragma once

#include "S6E63D6.h"

#include "AVR/Source/Types.h"

class LCD_S6E63D6_Parallel : public LCD_S6E63D6
{
	private:
		virtual void select( void);
		virtual void deselect( void);

		virtual void index( uint8_t Index);
		virtual void parameter( uint16_t Parameter);

		// Fill a rectangle.
		virtual void fillRect( uint16_t Left, uint16_t Top, int16_t Width, int16_t Height,
							   LCD_65K_RGB::Color Color,
							   RectOptions UseRectOptions = RO_None);

		virtual void windowStart( uint16_t Left, uint16_t Top, int16_t Width, int16_t Height);
		virtual void pushPixel( LCD_65K_RGB::Color Color);
		virtual void windowEnd( void);
	
	public:
		virtual ~LCD_S6E63D6_Parallel( void);

		virtual void Initialize( void);
};
