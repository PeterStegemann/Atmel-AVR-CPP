// Copyright 2009 Peter Stegemann

#pragma once

#include "AVR/Source/Types.h"

#include <avr/pgmspace.h>

namespace avr::font
{
  class Type
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
      Type
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

      const flash_uint8_t* GetData( void) const
      {
          return( data);
      }

      uint8_t GetCharacterWidth( void) const
      {
          return( characterWidth);
      }

      uint8_t GetCharacterHeight( void) const
      {
          return( characterHeight);
      }

      uint8_t GetCellWidth( void) const
      {
          return( cellWidth);
      }

      uint8_t GetCellHeight( void) const
      {
          return( cellHeight);
      }
  };
};
