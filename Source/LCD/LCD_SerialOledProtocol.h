// Copyright 2010 Peter Stegemann

#pragma once

class LCD_SerialOledProtocol
{
  public:
	enum Id		// uint8
	{
		I_Ok,
		I_Error,

		I_Ping,
		I_Clear,
		I_DrawPixel,
		I_DrawLine,
		I_DrawRect,
		I_FillRect,
		I_Print,
		I_Backlight,
		I_Blank,

		I_IdCount
	};
};
