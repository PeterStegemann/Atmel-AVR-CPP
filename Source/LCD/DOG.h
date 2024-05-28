// Copyright 2009 Peter Stegemann

#pragma once

#include "AVR/Source/Types.h"
#include "AVR/Source/Font/Font.h"
#include "AVR/Source/Font/Type.h"

#include <stdarg.h>

#define LCD_DOG_BACKLIGHT_OFF		0
#define LCD_DOG_BACKLIGHT_FULL		100
#define LCD_DOG_BACKLIGHT_STEPS		5

#define LCD_DOG_CONTRAST_OFF		0
#define LCD_DOG_CONTRAST_DEFAULT	50
#define LCD_DOG_CONTRAST_FULL		100
#define LCD_DOG_CONTRAST_STEPS		5

class LCD_DOG
{
	private:
		uint8_t columns;
		uint8_t pages;

		uint8_t lightness;
		uint8_t contrast;
		bool blanked;
		bool inverted;

	protected:
		virtual void initialize( void) = 0;

		virtual void select( void) = 0; 
		virtual void deselect( void) = 0;

		virtual void setPage( uint8_t Page) = 0;
		virtual void setColumn( uint8_t Column) = 0;

		virtual void sendDataByte( uint8_t Data) = 0;

		virtual void setBacklight( void) = 0;
		virtual void setContrast( void) = 0;
		virtual void setInverted( void) = 0;

	public:
		LCD_DOG( uint8_t Columns, uint8_t Pages);
		virtual ~LCD_DOG( void);

		// Initialize.
		void Initialize( void);
		void Initialize( uint8_t Backlight, uint8_t Contrast, bool Inverted);

		// Basic functions.
		uint8_t GetWidth( void) const;
		uint8_t GetHeight( void) const;

		// Set backlight intensity.
		void SetBacklight( uint8_t Backlight);
		uint8_t GetBacklight( void) const;

		// Screen blanking.
		void SetBlanked( bool Blanked);
		bool GetBlanked( void) const;

		// Set backlight intensity.
		void SetContrast( uint8_t Contrast);
		uint8_t GetContrast( void) const;

		// Set inverted display.
		void SetInverted( bool Inverted);
		bool GetInverted( void) const;

		void Clear( void);
		void Draw( void);

		uint8_t Print( uint8_t Column, uint8_t Page, FONT::FontId UseFontId, const char* String);
		uint8_t Print( uint8_t Column, uint8_t Page, uint8_t Limit, FONT::FontId UseFontId,
					   const char* String);
		uint8_t PrintFormat( uint8_t Column, uint8_t Page, FONT::FontId UseFontId,
							 const char* Format, ...);
		uint8_t PrintFormatVAList( uint8_t Column, uint8_t Page, FONT::FontId UseFontId,
								   const char* Format, va_list* Arguments);

		uint8_t Print_P( uint8_t Column, uint8_t Page, FONT::FontId UseFontId,
						 const flash_char* String);
		uint8_t Print_P( uint8_t Column, uint8_t Page, uint8_t Limit, FONT::FontId UseFontId,
						 const flash_char* String);
		uint8_t PrintFormat_P( uint8_t Column, uint8_t Page, FONT::FontId UseFontId,
							   const flash_char* Format, ...);
		uint8_t PrintFormatVAList_P( uint8_t Column, uint8_t Page, FONT::FontId UseFontId,
									 const flash_char* Format, va_list* Arguments);

		void Write( uint8_t Data);
		void Write( uint8_t Column, uint8_t Data);
		void Write( uint8_t Column, uint8_t Page, uint8_t Data);
};
