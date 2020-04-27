// Copyright 2009 Peter Stegemann

#pragma once

#include "AVR/Source/Types.h"

#include <avr/pgmspace.h>

class FONT_Type
{
  public:
	const flash_uint8_t* Data;

	// Width and height of the printed part of the pixel.
	uint8_t CharacterWidth;
	uint8_t CharacterHeight;

	// Width and height including spacing.
	uint8_t CellWidth;
	uint8_t CellHeight;
};
