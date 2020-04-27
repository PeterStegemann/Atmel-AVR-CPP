// Copyright 2007 Peter Stegemann

#pragma once

#include "AVR/Components/Types.h"

class FONT_Type;

class FONT
{
  public:
	enum FontId
	{
		FI_Micro,
		FI_Mini,
		FI_Medium,
		FI_Normal,
		FI_Large,

		FI_FontIdCount
	};

	enum Character
	{
		C_FirstTotal		= 32,
		C_FirstPrintable 	= 32,
		C_LastPrintable 	= 133,
		C_FirstSpecial		= 134,
		C_SpecialExit		= 134,
		C_SpecialBackspace,
		C_SpecialDelete,
		C_SpecialInsert,
		C_SpecialLeft,
		C_SpecialRight,
		C_LastSpecial		= C_SpecialRight,
		C_LastTotal			= C_LastSpecial
	};

  public:
	static const FONT_Type* GetFont( FontId Id);
//	static uint8_t GetFontCount( void);
};
