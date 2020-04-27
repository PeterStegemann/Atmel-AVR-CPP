// Copyright 2007 Peter Stegemann

#include "Font.h"

#include "Font_Large.h"
#include "Font_Medium.h"
#include "Font_Micro.h"
#include "Font_Mini.h"
#include "Font_Normal.h"

static FONT_Type Font[] =
{
	FONT_Micro(),
	FONT_Mini(),
	FONT_Medium(),
	FONT_Normal(),
	FONT_Large()
};

const FONT_Type* FONT::GetFont( FontId Id)
{
	// Map to a valid font.
	if( Id >= FI_FontIdCount)
	{
		Id = FI_Medium;
	}

	return( &( Font[ Id]));
}
