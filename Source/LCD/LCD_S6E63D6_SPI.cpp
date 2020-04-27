// Copyright 2010 Peter Stegemann

#include "LCD_S6E63D6_SPI.h"

#include "LCD_S6E63D6_Defines.h"
#include "Ports.h"

#include "AVR/Source/SPI.h"
#include "AVR/Source/Utility.h"

#define LCD_S6E63D6_SPI_USED_BITS			UTILITY_BitValue( LCD_S6E63D6_SPI_RESET) | UTILITY_BitValue( LCD_S6E63D6_SPI_SELECT) | UTILITY_BitValue( LCD_S6E63D6_SPI_RS) | UTILITY_BitValue( LCD_S6E63D6_SPI_RW_WRB)

#define LCD_S6E63D6_SPI_SetBit( Bit)		UTILITY_SetBit( LCD_S6E63D6_SPI_PORT, Bit)
#define LCD_S6E63D6_SPI_ClearBit( Bit)		UTILITY_ClearBit( LCD_S6E63D6_SPI_PORT, Bit)

#define LCD_S6E63D6_DATA_LOW_USED_BITS		0xff;
#define LCD_S6E63D6_DATA_HIGH_USED_BITS		0xff;

LCD_S6E63D6_SPI::~LCD_S6E63D6_SPI( void)
{
}

void LCD_S6E63D6_SPI::select( void)
{
	// Select.
	SPI::Select( LCD_S6E63D6_SPI_ID);
}

void LCD_S6E63D6_SPI::deselect( void)
{
	// Deselect.
	SPI::Deselect( LCD_S6E63D6_SPI_ID);
}

void LCD_S6E63D6_SPI::index( uint8_t Index)
{
	// Select.
	select();

	SPI::SendDataByte( 0b01110000);
    SPI::SendDataWord( Index);

	deselect();
}

void LCD_S6E63D6_SPI::parameter( uint16_t Parameter)
{
	select();

	SPI::SendDataByte( 0b01110010);
    SPI::SendDataWord( Parameter);

	deselect();
}

void LCD_S6E63D6_SPI::Initialize( void)
{
	LCD_S6E63D6_ClearBit( LCD_S6E63D6_POWER);

	setDimensions( LCD_S6E63D6_WIDTH, LCD_S6E63D6_HEIGHT);
//	setBacklight( LCD_65K_RGB_BACKLIGHT_FULL);
	setOrientation( O_Landscape);

	// All Ports to output
	LCD_S6E63D6_DDR |= LCD_S6E63D6_USED_BITS;
	LCD_S6E63D6_SPI_DDR |= LCD_S6E63D6_SPI_USED_BITS;
	LCD_S6E63D6_DATA_LOW_DDR |= LCD_S6E63D6_DATA_LOW_USED_BITS;
	LCD_S6E63D6_DATA_HIGH_DDR |= LCD_S6E63D6_DATA_HIGH_USED_BITS;
	
	// Serial mode.
	LCD_S6E63D6_SetBit( LCD_S6E63D6_SPB);
	// For serial mode, this is the device id. We pick 0.
	LCD_S6E63D6_ClearBit( LCD_S6E63D6_ID_MIB);

	// For SPI mode, E_RDB ist fixed to up.
	LCD_S6E63D6_SetBit( LCD_S6E63D6_E_RDB);
	
	// Reset display.
	// Select.
	LCD_S6E63D6_SPI_ClearBit( LCD_S6E63D6_SPI_SELECT);
	
	LCD_S6E63D6_SPI_ClearBit( LCD_S6E63D6_SPI_RESET);
	UTILITY::Pause( 75);
	
	// Return from reset.
	LCD_S6E63D6_SPI_SetBit( LCD_S6E63D6_SPI_RESET);
	UTILITY::Pause( 75);
	
	// Deselect.
	LCD_S6E63D6_SPI_SetBit( LCD_S6E63D6_SPI_SELECT);
	
	command( LCD_S6E63D6_OUTPUT, LCD_S6E63D6_OUTPUT_OFF);

	configureOrientation();

	Clear( LCD_65K_RGB::C_Black);

	command( LCD_S6E63D6_OSCILLATOR_CONTROL, LCD_S6E63D6_OSCILLATOR_CONTROL_81_HZ);

	// VCI=3.3v VCI1=2.2v VINT=-2v VGH=5.6v VGL=-5.6v
	// VLOUT1=VCI1+VCI=5.5 VLOUT2=VCI+(VCI1x2)=7.7 VLOUT3=-((VCIx2)+(VCI1x2))=-11
	command( LCD_S6E63D6_POWER_GEN_VCI1, LCD_S6E63D6_POWER_GEN_VCI1_2_20);

	command( LCD_S6E63D6_POWER_GEN_VGH, LCD_S6E63D6_POWER_GEN_VGH_5_6);
	command( LCD_S6E63D6_POWER_GEN_VGL, LCD_S6E63D6_POWER_GEN_VGL_5_6);
/*
	index(0x70);		// Gamma Top/Bottom R
	parameter(0x2B80);
	index(0x71);		// Gamma Top/Bottom G
	parameter(0x3600);
	index(0x72);		// Gamma Top/Bottom B
	parameter(0x3E00);
	index(0x73);		// Gamma Top Bottom R1,2
	parameter(0x1F19);
	index(0x74);		// Gamma Top Bottom R3,4
	parameter(0x2214);
	index(0x75);		// Gamma Top Bottom G1,2
	parameter(0x221B);
	index(0x76);		// Gamma Top Bottom G3,4
	parameter(0x1E16);
	index(0x77);		// Gamma Top Bottom B1,2
	parameter(0x241E);
	index(0x78);		// Gamma Top Bottom B3,4
	parameter(0x2617);
*/
	/*
	 R70h:   0x2580 
	 R71h:   0x2780 
	 R72h:   0x3380 
	 R73h:   0x1D18 
	 R74h:   0x1F11 
	 R75h:   0x2419 
	 R76h:   0x1A14 
	 R77h:   0x211A 
	 R78h:   0x2013
	*/

	command( LCD_S6E63D6_STAND_BY, LCD_S6E63D6_STAND_BY_OFF);
	command( LCD_S6E63D6_EL_CONTROL, LCD_S6E63D6_EL_CONTROL_TEST);

	UTILITY::Pause( 140);

    command( LCD_S6E63D6_OUTPUT, LCD_S6E63D6_OUTPUT_ON);

	UTILITY::Pause( 500);

	LCD_S6E63D6_SetBit( LCD_S6E63D6_POWER);
}
