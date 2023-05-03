// Copyright 2011 Peter Stegemann

#pragma once

#include "LCD_DOG.h"

#include "LCD_S65.h"

class LCD_DOG_S65 : public LCD_DOG
{
	private:
		uint8_t column;
		uint8_t page;

		LCD_S65 s65;

		virtual void initialize( void);

		virtual void select( void);
		virtual void deselect( void);

		virtual void setPage( uint8_t Page);
		virtual void setColumn( uint8_t Column);

		virtual void sendDataByte( uint8_t Data);

		virtual void setBacklight( void);
		virtual void setContrast( void);

	public:
		LCD_DOG_S65( void);
};
