// Copyright 2016 Peter Stegemann

#pragma once

namespace avr::serial
{
  enum TransferOptions
  {
      TO_None		= 0b00000000,
      TO_Block		= 0b00000000,
      TO_NonBlock	= 0b00000001,
      TO_ShortBlock	= 0b00000010
  };
};
