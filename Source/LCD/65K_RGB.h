// Copyright 2009 Peter Stegemann

#pragma once

#include "LCD.h"

#include "AVR/Source/Types.h"
#include "AVR/Source/Font/Font.h"
#include "AVR/Source/Font/Type.h"

#include <stdarg.h>

#define LCD_65K_RGB_MAXIMUM_GREY			0b011111

#define LCD_65K_RGB_MAXIMUM_RED				0b011111
#define LCD_65K_RGB_MAXIMUM_GREEN			0b111111
#define LCD_65K_RGB_MAXIMUM_BLUE			0b011111

// Build a color value from its three components. Be aware that green has a bit more than red and
// blue.
#define LCD_65K_RGB_COLOR( Red, Green, Blue) \
	( LCD_65K_RGB::Color)(((( uint16_t)( Red) & LCD_65K_RGB_MAXIMUM_RED) << 11) | \
						((( uint16_t)( Green) & LCD_65K_RGB_MAXIMUM_GREEN) << 5) | \
						  (( uint16_t)( Blue) & LCD_65K_RGB_MAXIMUM_BLUE))

#define LCD_65K_RGB_RED( Color)		 (( Color) >> 11)
#define LCD_65K_RGB_GREEN( Color)	((( Color) >> 5) & LCD_65K_RGB_MAXIMUM_GREEN)
#define LCD_65K_RGB_BLUE( Color)	 (( Color) & LCD_65_RGB_MAXIMUM_BLUE)

#define LCD_65K_RGB_GREY( Grey)	\
	( LCD_65K_RGB::Color) LCD_65K_RGB_COLOR(( Grey), (( Grey) << 1) + 1, ( Grey))

#define LCD_65K_RGB_BACKLIGHT_OFF		0
#define LCD_65K_RGB_BACKLIGHT_FULL		100
#define LCD_65K_RGB_BACKLIGHT_STEPS		5

class LCD_65K_RGB : public LCD
{
	public:
		#define INT_LCD_65K_RGB( Red, Green, Blue)	  ((( Red & 0b011111) << 11) | \
													 (( Green & 0b111111) << 5)  | \
													   ( Blue & 0b011111))

		// Predefined colors
		enum Color
		{
			C_White				= INT_LCD_65K_RGB( LCD_65K_RGB_MAXIMUM_RED,
												   LCD_65K_RGB_MAXIMUM_GREEN,
												   LCD_65K_RGB_MAXIMUM_BLUE),
			C_LightGrey			= INT_LCD_65K_RGB( 0b001111, 0b001111, 0b001111),
			C_Grey				= INT_LCD_65K_RGB( 0b000111, 0b000111, 0b000111),
			C_DarkGrey			= INT_LCD_65K_RGB( 0b000011, 0b000011, 0b000011),
			C_Black				= INT_LCD_65K_RGB( 0b000000, 0b000000, 0b000000),

			C_BrightRed			= INT_LCD_65K_RGB( 0b011111, 0b000111, 0b001101),
			C_Red				= INT_LCD_65K_RGB( 0b011111, 0b000000, 0b000000),
			C_DarkRed			= INT_LCD_65K_RGB( 0b100011, 0b000000, 0b000000),
			C_WarmRed			= INT_LCD_65K_RGB( 0b011111, 0b000111, 0b000000),
			
			C_BrightPink		= INT_LCD_65K_RGB( 0b011111, 0b100000, 0b001101),
			C_Pink				= INT_LCD_65K_RGB( 0b011111, 0b011110, 0b010000),

			C_BrightGreen		= INT_LCD_65K_RGB( 0b010011, 0b111111, 0b010011),
			C_Green				= INT_LCD_65K_RGB( 0b000000, 0b111111, 0b000000),
			C_DarkGreen			= INT_LCD_65K_RGB( 0b000000, 0b011011, 0b000000),

			C_BrightBlue		= INT_LCD_65K_RGB( 0b011011, 0b110110, 0b011111),
			C_Blue				= INT_LCD_65K_RGB( 0b000000, 0b000000, 0b011111),
			C_DarkBlue			= INT_LCD_65K_RGB( 0b000000, 0b000000, 0b100011),

			C_BrightYellow		= INT_LCD_65K_RGB( 0b011111, 0b111111, 0b001101),
			C_Yellow			= INT_LCD_65K_RGB( 0b011111, 0b111111, 0b000000),
			C_WarmYellow		= INT_LCD_65K_RGB( 0b011111, 0b101111, 0b000000),

			C_BrightOrange		= INT_LCD_65K_RGB( 0b011111, 0b100000, 0b001101),
			C_Orange			= INT_LCD_65K_RGB( 0b011111, 0b011000, 0b000000)
		};

	private:
		uint16_t width;
		uint16_t height;

		Orientation orientation;

		uint8_t lightness;
		bool blanked;

	protected:
		// Store the physical dimensions of the display.
		void setDimensions( uint16_t Width, uint16_t Height);
		// Store the lightness value.
		void setBacklight( uint8_t Backlight);
		// Store the blanked value.
		void setBlanked( bool Blanked);
		// Store orientation.
		void setOrientation( Orientation UseOrientation);

		// These are the minimum drawing functions you have to implement.
		// Set a single pixel.
		virtual void drawPixel( uint16_t Left, uint16_t Top, LCD_65K_RGB::Color Color) = 0;
		// Fill a rectangle.
		virtual void fillRect( uint16_t Left, uint16_t Top, int16_t Width, int16_t Height,
							   LCD_65K_RGB::Color ForegroundColor,
							   RectOptions UseRectOptions = RO_None) = 0;
		// Returns width in pixels of printed text.
		virtual uint16_t print( uint16_t Left, uint16_t Top, FONT::FontId UseFontId,
							    LCD_65K_RGB::Color ForegroundColor,
							    LCD_65K_RGB::Color BackgroundColor,
							    PrintOptions UsePrintOptions, const char* String) = 0;

		// Optional drawing functions to optimize operation.
		virtual void drawLine( uint16_t StartX, uint16_t StartY, uint16_t StopX, uint16_t StopY,
							   LCD_65K_RGB::Color Color);

	public:
		LCD_65K_RGB( void);
		virtual ~LCD_65K_RGB( void);

		// Initialize the display.
//		virtual void Initialize( void) = 0;

		// Basic functions.
		uint16_t GetWidth( void);
		uint16_t GetHeight( void);

		// Set backlight intensity. Values range only from 0 to LCD_65K_RGB_BACKLIGHT_FULL.
		virtual void SetBacklight( uint8_t Backlight) = 0;
		uint8_t GetBacklight( void);

		// Screen blanking.
		virtual void SetBlanked( bool Blanked) = 0;
		bool GetBlanked( void);
	
		virtual void SetOrientation( Orientation UseOrientation) = 0;
		Orientation GetOrientation( void);

		// Drawing methods.

		// Clear screen.
		void Clear( LCD_65K_RGB::Color BackgroundColor);

		// Set a single pixel.
		void DrawPixel( uint16_t Left, uint16_t Top, LCD_65K_RGB::Color Color);
		// Draw a little dot.
		void DrawDot( uint16_t Left, uint16_t Top, LCD_65K_RGB::Color Color);

		// Draw a strictly vertical line.
		void DrawVerticalLine( uint16_t Left, uint16_t Top, int16_t Height,
							   LCD_65K_RGB::Color Color);
		// Draw a strictly horizontal line.
		void DrawHorizontalLine( uint16_t Left, uint16_t Top, int16_t Width,
								 LCD_65K_RGB::Color Color);
		// Draw a line.
		void DrawLine( uint16_t StartX, uint16_t StartY, uint16_t StopX, uint16_t StopY,
					   LCD_65K_RGB::Color Color);

		// Fill a rectangle.
		void FillRect( uint16_t Left, uint16_t Top, int16_t Width, int16_t Height,
					   LCD_65K_RGB::Color Color, LCD::RectOptions UseRectOptions = RO_None);
		// Draw a non filled rectangle.
		void DrawRect( uint16_t Left, uint16_t Top, int16_t Width, int16_t Height,
					   LCD_65K_RGB::Color Color, LCD::RectOptions UseRectOptions = RO_None);

		// Text printing support.
		// Returns printed length.
		uint16_t Print( uint16_t Left, uint16_t Top, FONT::FontId UseFontId,
					    LCD_65K_RGB::Color ForegroundColor, LCD_65K_RGB::Color BackgroundColor,
					    LCD::PrintOptions UsePrintMode, const char* String);
		uint16_t PrintFormat( uint16_t Left, uint16_t Top, FONT::FontId UseFontId,
							  LCD_65K_RGB::Color ForegroundColor,
							  LCD_65K_RGB::Color BackgroundColor,
							  LCD::PrintOptions UsePrintOptions, const char* Format, ...);
		uint16_t PrintFormatVAList( uint16_t Left, uint16_t Top, FONT::FontId UseFontId,
								    LCD_65K_RGB::Color ForegroundColor,
								    LCD_65K_RGB::Color BackgroundColor,
								    LCD::PrintOptions UsePrintOptions, const char* Format,
								    va_list* Arguments);
		uint16_t Print_P( uint16_t Left, uint16_t Top, FONT::FontId UseFontId,
						  LCD_65K_RGB::Color ForegroundColor, LCD_65K_RGB::Color BackgroundColor,
						  LCD::PrintOptions UsePrintOptions, const flash_char* String);
		uint16_t PrintFormat_P( uint16_t Left, uint16_t Top, FONT::FontId UseFontId,
							    LCD_65K_RGB::Color ForegroundColor,
							    LCD_65K_RGB::Color BackgroundColor,
							    LCD::PrintOptions UsePrintOptions, const flash_char* Format, ...);
		uint16_t PrintFormatVAList_P( uint16_t Left, uint16_t Top, FONT::FontId UseFontId,
									  LCD_65K_RGB::Color ForegroundColor,
									  LCD_65K_RGB::Color BackgroundColor,
									  LCD::PrintOptions UsePrintOptions, const flash_char* Format,
									  va_list* Arguments);
};
