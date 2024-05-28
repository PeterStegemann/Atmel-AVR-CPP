// Copyright 2009 Peter Stegemann

#pragma once

#include "AVR/Source/Types.h"

#include <avr/pgmspace.h>

namespace avr
{
  class SPI
  {
    private:
      static void data( void);
      static void command( void);

    public:
      SPI( void);

      static void Initialize( void);

      static void Select( uint8_t Id);
      static void Deselect( uint8_t Id);

      static void Wait( void);

      static void SendCommandByte( uint8_t Value);
      static void SendCommandWord( uint16_t Value);

      static void SendDataByte( uint8_t Value);
      static void SendDataWord( uint16_t Value);
      static void SendDataBytes( const uint8_t Data[], uint16_t DataSize);

      static void SendDataWords_P( const flash_uint16_t Data[], uint16_t DataSize);
  };
};
