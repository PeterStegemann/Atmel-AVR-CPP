// Copyright 2010 Peter Stegemann

#include "LCD_S6E63D6_Parallel.h"

#include "LCD_S6E63D6_Defines.h"
#include "Ports.h"

#include "AVR/Components/Utility.h"

#define LCD_S6E63D6_SPI_USED_BITS			UTILITY_BitValue( LCD_S6E63D6_SPI_RESET) | UTILITY_BitValue( LCD_S6E63D6_SPI_SELECT) | UTILITY_BitValue( LCD_S6E63D6_SPI_RS) | UTILITY_BitValue( LCD_S6E63D6_SPI_RW_WRB)

#define LCD_S6E63D6_SPI_SetBit( Bit)		UTILITY_SetBit( LCD_S6E63D6_SPI_PORT, Bit)
#define LCD_S6E63D6_SPI_ClearBit( Bit)		UTILITY_ClearBit( LCD_S6E63D6_SPI_PORT, Bit)

#define LCD_S6E63D6_DATA_LOW_USED_BITS		0xff;
#define LCD_S6E63D6_DATA_HIGH_USED_BITS		0xff;

LCD_S6E63D6_Parallel::~LCD_S6E63D6_Parallel( void)
{
}

void LCD_S6E63D6_Parallel::select( void)
{
	// Select.
	LCD_S6E63D6_SPI_ClearBit( LCD_S6E63D6_SPI_SELECT);
}

void LCD_S6E63D6_Parallel::deselect( void)
{
	// Deselect.
	LCD_S6E63D6_SPI_SetBit( LCD_S6E63D6_SPI_SELECT);
}

void LCD_S6E63D6_Parallel::index( uint8_t Index)
{
	// Index.
	LCD_S6E63D6_SPI_ClearBit( LCD_S6E63D6_SPI_RS);
	// Write.
	LCD_S6E63D6_SPI_ClearBit( LCD_S6E63D6_SPI_RW_WRB);

	// Select.
	LCD_S6E63D6_SPI_ClearBit( LCD_S6E63D6_SPI_SELECT);

	// Set data.
	LCD_S6E63D6_DATA_LOW_PORT = Index;

	LCD_S6E63D6_SetBit( LCD_S6E63D6_E_RDB);
	LCD_S6E63D6_ClearBit( LCD_S6E63D6_E_RDB);

	// Deselect.
	LCD_S6E63D6_SPI_SetBit( LCD_S6E63D6_SPI_SELECT);
}

void LCD_S6E63D6_Parallel::parameter( uint16_t Parameter)
{
	// Not index.
	LCD_S6E63D6_SPI_SetBit( LCD_S6E63D6_SPI_RS);
	// Write.
	LCD_S6E63D6_SPI_ClearBit( LCD_S6E63D6_SPI_RW_WRB);

	// Select.
	LCD_S6E63D6_SPI_ClearBit( LCD_S6E63D6_SPI_SELECT);
	
	// Set data.
	LCD_S6E63D6_DATA_LOW_PORT = Parameter >> 8;

	LCD_S6E63D6_SetBit( LCD_S6E63D6_E_RDB);
	LCD_S6E63D6_ClearBit( LCD_S6E63D6_E_RDB);

	// Set data.
	LCD_S6E63D6_DATA_LOW_PORT = Parameter & 0xff;

	LCD_S6E63D6_SetBit( LCD_S6E63D6_E_RDB);
	LCD_S6E63D6_ClearBit( LCD_S6E63D6_E_RDB);

	// Deselect.
	LCD_S6E63D6_SPI_SetBit( LCD_S6E63D6_SPI_SELECT);
}

void LCD_S6E63D6_Parallel::fillRect( uint16_t Left, uint16_t Top, int16_t Width, int16_t Height,
									 LCD_65K_RGB::Color Color, RectOptions UseRectOptions)
{
	if(( Width == 0) || ( Height == 0))
	{
		return;
	}
	
	if( Width < 0)
	{
		fillRect( Left + Width, Top, -Width, Height, Color, UseRectOptions);
		
		return;
	}
	
	if( Height < 0)
	{
		fillRect( Left, Top + Height, Width, -Height, Color, UseRectOptions);
		
		return;
	}
	
	// Set drawing window.
	windowStart( Left, Top, Width, Height);

	// Not index.
	LCD_S6E63D6_SPI_SetBit( LCD_S6E63D6_SPI_RS);
	// Write.
	LCD_S6E63D6_SPI_ClearBit( LCD_S6E63D6_SPI_RW_WRB);
	
	// Select.
	LCD_S6E63D6_SPI_ClearBit( LCD_S6E63D6_SPI_SELECT);

	for( uint16_t HeightCount = Height; HeightCount != 0; HeightCount--)
	{
		for( uint16_t WidthCount = Width; WidthCount != 0; WidthCount--)
		{
			// Set data.
			LCD_S6E63D6_DATA_LOW_PORT = Color >> 8;
			
			LCD_S6E63D6_SetBit( LCD_S6E63D6_E_RDB);
			LCD_S6E63D6_ClearBit( LCD_S6E63D6_E_RDB);

			// Set data.
			LCD_S6E63D6_DATA_LOW_PORT = Color & 0xff;

			LCD_S6E63D6_SetBit( LCD_S6E63D6_E_RDB);
			LCD_S6E63D6_ClearBit( LCD_S6E63D6_E_RDB);
		}
	}

	// Deselect.
	LCD_S6E63D6_SPI_SetBit( LCD_S6E63D6_SPI_SELECT);

	// End drawing operation to that window.
	windowEnd();
}

void LCD_S6E63D6_Parallel::windowStart( uint16_t Left, uint16_t Top, int16_t Width, int16_t Height)
{
	LCD_S6E63D6::windowStart( Left, Top, Width, Height);

	// Not index.
	LCD_S6E63D6_SPI_SetBit( LCD_S6E63D6_SPI_RS);
	// Write.
	LCD_S6E63D6_SPI_ClearBit( LCD_S6E63D6_SPI_RW_WRB);
	
	// Select.
	LCD_S6E63D6_SPI_ClearBit( LCD_S6E63D6_SPI_SELECT);
}

void LCD_S6E63D6_Parallel::pushPixel( LCD_65K_RGB::Color Color)
{
	// Set data.
	LCD_S6E63D6_DATA_LOW_PORT = Color >> 8;
	
	LCD_S6E63D6_SetBit( LCD_S6E63D6_E_RDB);
	LCD_S6E63D6_ClearBit( LCD_S6E63D6_E_RDB);
	
	// Set data.
	LCD_S6E63D6_DATA_LOW_PORT = Color & 0xff;
	
	LCD_S6E63D6_SetBit( LCD_S6E63D6_E_RDB);
	LCD_S6E63D6_ClearBit( LCD_S6E63D6_E_RDB);
}

void LCD_S6E63D6_Parallel::windowEnd( void)
{
	// Deselect.
	LCD_S6E63D6_SPI_SetBit( LCD_S6E63D6_SPI_SELECT);

	LCD_S6E63D6::windowEnd();
}

/*
void LCD_S6E63D6_Parallel::pushPixel( LCD_65K_RGB::Color Color)
{
	//	command( LCD_S6E63D6_GRAM_WRITE, Color);
	//	parameter( Color);
	// Not index.
	LCD_S6E63D6_SPI_SetBit( LCD_S6E63D6_SPI_RS);
	// Write.
	LCD_S6E63D6_SPI_ClearBit( LCD_S6E63D6_SPI_RW_WRB);
	
	// Set data.
	LCD_S6E63D6_DATA_HIGH_PORT = Color >> 8;
	LCD_S6E63D6_DATA_LOW_PORT = Color & 0xff;

	// Select.
	select();
	
	LCD_S6E63D6_SetBit( LCD_S6E63D6_E_RDB);
	LCD_S6E63D6_ClearBit( LCD_S6E63D6_E_RDB);

	// Deselect.
	deselect();
}
*/
void LCD_S6E63D6_Parallel::Initialize( void)
{
	// Make sure gate power is off.
	LCD_S6E63D6_ClearBit( LCD_S6E63D6_POWER);

	setDimensions( LCD_S6E63D6_WIDTH, LCD_S6E63D6_HEIGHT);
//	setBacklight( LCD_65K_RGB_BACKLIGHT_FULL);
	setOrientation( O_Landscape);

	// All Ports to output
	LCD_S6E63D6_DDR |= LCD_S6E63D6_USED_BITS;
	LCD_S6E63D6_SPI_DDR |= LCD_S6E63D6_SPI_USED_BITS;
	LCD_S6E63D6_DATA_LOW_DDR |= LCD_S6E63D6_DATA_LOW_USED_BITS;
	LCD_S6E63D6_DATA_HIGH_DDR |= LCD_S6E63D6_DATA_HIGH_USED_BITS;

	// Parallel mode.
	LCD_S6E63D6_ClearBit( LCD_S6E63D6_SPB);
	// For parallel mode, this is the interface mode. We pick 1 for motorola.
	LCD_S6E63D6_SetBit( LCD_S6E63D6_ID_MIB);

	// For parallel motorola mode, initialize this to one.
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

	// Go for 16bit data bus.
	index( LCD_S6E63D6_SELECT_DATA_BUS_2);

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

	// Gate power on.
	LCD_S6E63D6_SetBit( LCD_S6E63D6_POWER);
/*
	while( true)
	{
		UTILITY::Pause( 500);

		command( LCD_S6E63D6_OUTPUT, LCD_S6E63D6_OUTPUT_OFF);

		UTILITY::Pause( 500);

		command( LCD_S6E63D6_OUTPUT, LCD_S6E63D6_OUTPUT_ON);
	}
*/
}
