// Copyright 2010 Peter Stegemann

#ifndef SERIAL_PROTOCOL_H
#define SERIAL_PROTOCOL_H

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

#endif
