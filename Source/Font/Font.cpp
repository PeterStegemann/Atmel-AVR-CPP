// Copyright 2007 Peter Stegemann

#include "Font.h"

#include "Large.h"
#include "Medium.h"
#include "Micro.h"
#include "Mini.h"
#include "Normal.h"

using namespace avr::font;

static Type Fonts[] =
{
    Micro(),
	Mini(),
	Medium(),
	Normal(),
	Large()
};

const Type* Font::Get( FontId Id)
{
	// Map to a valid font.
	if( Id >= FI_FontIdCount)
	{
		Id = FI_Medium;
	}

	return( &( Fonts[ Id]));
}
