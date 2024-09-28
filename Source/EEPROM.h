// Copyright 2008 Peter Stegemann

#pragma once

#include "System.h"

#include "AVR/Source/TWI.h"
#include "AVR/Source/Types.h"

namespace avr
{
  #define EEPROM_SIZE		            (( 512L / 8L ) * 1024L)

  #define EEPROM_Address( Address)	    (( uint32_t) &( Address))

  class EEPROM
  {
    public:
      static void Initialize( void);

      static bool ReadByte( uint32_t Address, uint8_t* Value);
      static bool ReadBytes( uint32_t Address, uint16_t Length, void* Value);

      static bool WriteByte( uint32_t Address, uint8_t Value);
      static bool WriteBytes( uint32_t Address, uint16_t Length, const void* Value);

      static bool ReadString( uint32_t Address, uint8_t EepromSize, char* String, uint8_t Length);
      static bool WriteString( uint32_t Address, uint8_t EepromSize, const char* String);
  };
}
