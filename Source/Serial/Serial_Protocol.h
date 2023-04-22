// Copyright 2010 Peter Stegemann

#pragma once

class SERIAL_Protocol
{
  public:
    enum Type			// uint8
    {
        T_Command,		// uint8 Value
        T_State,		// uint8 Value
        T_Value,		// char[] Characters, char 0
        T_Complex,		// ..., T_ComplexEnd
        T_ComplexEnd
    };
};
