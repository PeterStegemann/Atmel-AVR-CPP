// Copyright 2011 Peter Stegemann

#ifndef LCD_DOG_S102_H
#define LCD_DOG_S102_H

#include "LCD_DOG.h"

class LCD_DOG_S102 : public LCD_DOG
{
	private:
		virtual void initialize( void);

		virtual void select( void);
		virtual void deselect( void);

		virtual void setPage( uint8_t Page);
		virtual void setColumn( uint8_t Column);

		virtual void sendDataByte( uint8_t Data);

		virtual void setBacklight( void);
		virtual void setContrast( void);
		virtual void setInverted( void);

	public:
		LCD_DOG_S102( void);
};

#endif
