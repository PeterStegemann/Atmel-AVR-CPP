// Copyright 2009 Peter Stegemann

#ifndef LCD_S6E63D6_H
#define LCD_S6E63D6_H

#include "LCD_65K_RGB_Window.h"

#include "AVR/Source/Types.h"

class LCD_S6E63D6 : public LCD_65K_RGB_Window
{
	protected:
		virtual void windowStart( uint16_t Left, uint16_t Top, int16_t Width, int16_t Height);
		virtual void pushPixel( LCD_65K_RGB::Color Color);
		virtual void windowEnd( void);
	
		virtual void index( uint8_t Index) = 0;
		virtual void parameter( uint16_t Parameter) = 0;
		virtual void command( uint8_t Index, uint16_t Parameter);

		void configureOrientation( void);

	public:
		virtual ~LCD_S6E63D6( void);

		virtual void SetBacklight( uint8_t Backlight);
		virtual void SetBlanked( bool Blanked);
		virtual void SetOrientation( Orientation UseOrientation);
};

#endif
