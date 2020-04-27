// Copyright 2010 Peter Stegemann

#ifndef LCD_S6E63D6_SPI_H
#define LCD_S6E63D6_SPI_H

#include "LCD_S6E63D6.h"

#include "AVR/Components/Types.h"

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

#endif
