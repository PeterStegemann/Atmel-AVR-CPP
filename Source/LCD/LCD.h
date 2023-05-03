// Copyright 2009 Peter Stegemann

#pragma once

class LCD
{
	public:
		enum Orientation
		{
			O_Portrait			= 0b00000001,
			O_Landscape			= 0b00000010,
			O_HorizontalFlip	= 0b00000100,
			O_VerticalFlip		= 0b00001000
		};

		enum RectOptions
		{
			RO_None				= 0b00000000,
			RO_Boxed			= 0b00000000,
			RO_Rounded			= 0b00000001
		};

		enum PrintOptions
		{
			PO_Fixed			= 0b00000000,
			PO_Proportional		= 0b00000001
		};

	public:
		virtual ~LCD( void);
};

