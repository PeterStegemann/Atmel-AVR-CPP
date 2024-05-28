// Copyright 2010 Peter Stegemann

#pragma once

#include "S6E63D6.h"

#include "AVR/Source/Types.h"

class LCD_S6E63D6_SPI : public LCD_S6E63D6
{
	private:
		virtual void select( void);
		virtual void deselect( void);

		virtual void index( uint8_t Index);
		virtual void parameter( uint16_t Parameter);

	public:
		virtual ~LCD_S6E63D6_SPI( void);

		virtual void Initialize( void);
};
