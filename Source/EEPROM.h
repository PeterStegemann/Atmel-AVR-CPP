// Copyright 2008 Peter Stegemann

#pragma once

#include "System.h"

#include "AVR/Source/Types.h"

namespace avr
{
  #define EEPROM_SIZE		(( 512L / 8L ) * 1024L)

  #define EEPROM_ReadByte( Address, Value)              avr::EEPROM::ReadByte(( uint32_t) Address, Value);
  #define EEPROM_ReadBytes( Address, Length, Value)     avr::EEPROM::ReadBytes(( uint32_t) Address, Length, Value);

  #define EEPROM_WriteByte( Address, Value)             avr::EEPROM::WriteByte(( uint32_t) Address, Value);
  #define EEPROM_WriteBytes( Address, Length, Value)    avr::EEPROM::WriteBytes(( uint32_t) Address, Length, Value);

  #define EEPROM_ReadString( Address, EepromSize, String, Length) \
      avr::EEPROM::ReadString(( uint32_t) Address, EepromSize, String, Length);
  #define EEPROM_WriteString( Address, EepromSize, String) \
	  avr::EEPROM::WriteString(( uint32_t) Address, EepromSize, String);

  class EEPROM
  {
    private:
      static bool readByteStart( uint32_t Address);

    public:
      static void Initialize( void);

      static bool ReadByte( uint32_t Address, uint8_t* Value);
      static bool ReadBytes( uint32_t Address, uint16_t Length, void* Value);

      static bool WriteByte( uint32_t Address, uint8_t Value);
      static bool WriteBytes( uint32_t Address, uint16_t Length, const void* Value);

      static bool ReadString( uint32_t Address, uint8_t EepromSize, char* String, uint8_t Length);
      static bool WriteString( uint32_t Address, uint8_t EepromSize, const char* String);
  };
};
