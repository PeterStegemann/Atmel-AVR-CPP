// Copyright 2009 Peter Stegemann

#pragma once

#include "AVR/Source/Types.h"

#include <avr/pgmspace.h>

class FONT_Type
{
  private:
	const flash_uint8_t* data;

	// Width and height of the printed part of the pixel.
	uint8_t characterWidth;
	uint8_t characterHeight;

	// Width and height including spacing.
	uint8_t cellWidth;
	uint8_t cellHeight;

  public:
    FONT_Type
    (
        const flash_uint8_t* Data,
        uint8_t CharacterWidth, uint8_t CharacterHeight, uint8_t CellWidth, uint8_t CellHeight
    )
        : data( Data)
        , characterWidth( CharacterWidth)
        , characterHeight( CharacterHeight)
        , cellWidth( CellWidth)
        , cellHeight( CellHeight)
    {
    }

    const flash_uint8_t* getData( void) const
    {
        return( data);
    }

    uint8_t getCharacterWidth( void) const
    {
        return( characterWidth);
    }

    uint8_t getCharacterHeight( void) const
    {
        return( characterHeight);
    }

    uint8_t getCellWidth( void) const
    {
        return( cellWidth);
    }

    uint8_t getCellHeight( void) const
    {
        return( cellHeight);
    }
};
