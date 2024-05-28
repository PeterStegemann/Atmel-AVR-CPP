// Copyright 2007 Peter Stegemann

#include "Large.h"

#include <avr/pgmspace.h>

using namespace avr::font;

const flash_uint8_t Data[] PROGMEM =
{
	// space
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	// !
	0b11000000,
	0b11000000,
	0b11000000,
	0b11000000,
	0b11000000,
	0b11000000,
	0b11000000,
	0b11000000,
	0b00000000,
	0b00000000,
	0b11000000,
	0b11000000,
	0b00000000,
	0b00000000,
	0b00000000,
	// "
	0b11011000,
	0b11011000,
	0b11011000,
	0b11011000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	// #
	0b01100110,
	0b01100110,
	0b11111111,
	0b11111111,
	0b01100110,
	0b01100110,
	0b01100110,
	0b01100110,
	0b11111111,
	0b11111111,
	0b01100110,
	0b01100110,
	0b00000000,
	0b00000000,
	0b00000000,
	// $
	0b00011000,
	0b01111110,
	0b11011011,
	0b10011000,
	0b11011000,
	0b01111000,
	0b00011110,
	0b00011011,
	0b00011001,
	0b11011011,
	0b01111110,
	0b00011000,
	0b00000000,
	0b00000000,
	0b00000000,
	// %
	0b11100011,
	0b10100011,
	0b11100110,
	0b00000110,
	0b00001100,
	0b00011000,
	0b00011000,
	0b00110000,
	0b01100000,
	0b01100111,
	0b11000101,
	0b11000111,
	0b00000000,
	0b00000000,
	0b00000000,
	// &
	0b01111000,
	0b11001100,
	0b11001100,
	0b11001100,
	0b11011000,
	0b01110000,
	0b01111011,
	0b11011111,
	0b11001100,
	0b11001110,
	0b11111111,
	0b01110011,
	0b00000000,
	0b00000000,
	0b00000000,
	//
	0b01100000,
	0b01100000,
	0b01100000,
	0b11000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	// (
	0b00011000,
	0b00110000,
	0b01100000,
	0b11000000,
	0b11000000,
	0b11000000,
	0b11000000,
	0b11000000,
	0b11000000,
	0b01100000,
	0b00110000,
	0b00011000,
	0b00000000,
	0b00000000,
	0b00000000,
	// )
	0b11000000,
	0b01100000,
	0b00110000,
	0b00011000,
	0b00011000,
	0b00011000,
	0b00011000,
	0b00011000,
	0b00011000,
	0b00110000,
	0b01100000,
	0b11000000,
	0b00000000,
	0b00000000,
	0b00000000,
	// *
	0b00000000,
	0b00000000,
	0b00011000,
	0b11011011,
	0b11111111,
	0b00111100,
	0b00111100,
	0b11111111,
	0b11011011,
	0b00011000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	// +
	0b00000000,
	0b00000000,
	0b00011000,
	0b00011000,
	0b00011000,
	0b11111111,
	0b11111111,
	0b00011000,
	0b00011000,
	0b00011000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	// ,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b01100000,
	0b01100000,
	0b01100000,
	0b11000000,
	0b00000000,
	// -
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b11111111,
	0b11111111,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	// .
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b11000000,
	0b11000000,
	0b00000000,
	0b00000000,
	0b00000000,
	// /
	0b00000011,
	0b00000011,
	0b00000110,
	0b00000110,
	0b00001100,
	0b00011000,
	0b00011000,
	0b00110000,
	0b01100000,
	0b01100000,
	0b11000000,
	0b11000000,
	0b00000000,
	0b00000000,
	0b00000000,
	// 0
	0b01111110,
	0b11111111,
	0b11000011,
	0b11000011,
	0b11001011,
	0b11001011,
	0b11010011,
	0b11010011,
	0b11000011,
	0b11000011,
	0b11111111,
	0b01111110,
	0b00000000,
	0b00000000,
	0b00000000,
	// 1
	0b00000111,
	0b00001111,
	0b00011111,
	0b00111011,
	0b01110011,
	0b00000011,
	0b00000011,
	0b00000011,
	0b00000011,
	0b00000011,
	0b00000011,
	0b00000011,
	0b00000000,
	0b00000000,
	0b00000000,
	// 2
	0b01111110,
	0b11111111,
	0b11000011,
	0b00000011,
	0b00000011,
	0b00000110,
	0b00001100,
	0b00011000,
	0b00110000,
	0b01100000,
	0b11111111,
	0b11111111,
	0b00000000,
	0b00000000,
	0b00000000,
	// 3
	0b01111110,
	0b11111111,
	0b11000011,
	0b00000011,
	0b00000011,
	0b00011110,
	0b00011110,
	0b00000011,
	0b00000011,
	0b11000011,
	0b11111111,
	0b01111110,
	0b00000000,
	0b00000000,
	0b00000000,
	// 4
	0b11000011,
	0b11000011,
	0b11000011,
	0b11000011,
	0b11000011,
	0b11111111,
	0b11111111,
	0b00000011,
	0b00000011,
	0b00000011,
	0b00000011,
	0b00000011,
	0b00000000,
	0b00000000,
	0b00000000,
	// 5
	0b11111111,
	0b11111111,
	0b11000000,
	0b11000000,
	0b11000000,
	0b11111110,
	0b01111111,
	0b00000011,
	0b00000011,
	0b11000011,
	0b11111111,
	0b01111110,
	0b00000000,
	0b00000000,
	0b00000000,
	// 6
	0b01111110,
	0b11111111,
	0b11000011,
	0b11000000,
	0b11000000,
	0b11111110,
	0b11111111,
	0b11000011,
	0b11000011,
	0b11000011,
	0b11111111,
	0b01111110,
	0b00000000,
	0b00000000,
	0b00000000,
	// 7
	0b11111111,
	0b11111111,
	0b00000011,
	0b00000011,
	0b00000111,
	0b00001110,
	0b00011100,
	0b00011000,
	0b00011000,
	0b00011000,
	0b00011000,
	0b00011000,
	0b00000000,
	0b00000000,
	0b00000000,
	// 8
	0b01111110,
	0b11111111,
	0b11000011,
	0b11000011,
	0b11000011,
	0b01111110,
	0b01111110,
	0b11000011,
	0b11000011,
	0b11000011,
	0b11111111,
	0b01111110,
	0b00000000,
	0b00000000,
	0b00000000,
	// 9
	0b01111110,
	0b11111111,
	0b11000011,
	0b11000011,
	0b11000011,
	0b11111111,
	0b01111111,
	0b00000011,
	0b00000011,
	0b11000011,
	0b11111111,
	0b01111110,
	0b00000000,
	0b00000000,
	0b00000000,
	// :
	0b00000000,
	0b00000000,
	0b00000000,
	0b11000000,
	0b11000000,
	0b00000000,
	0b00000000,
	0b11000000,
	0b11000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	// ;
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b01100000,
	0b01100000,
	0b00000000,
	0b00000000,
	0b01100000,
	0b01100000,
	0b01100000,
	0b11000000,
	0b00000000,
	0b00000000,
	// >
	0b00000000,
	0b00001110,
	0b00011100,
	0b00111000,
	0b01110000,
	0b11100000,
	0b11100000,
	0b01110000,
	0b00111000,
	0b00011100,
	0b00001110,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	// =
	0b00000000,
	0b00000000,
	0b00000000,
	0b11111111,
	0b11111111,
	0b00000000,
	0b00000000,
	0b11111111,
	0b11111111,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	// <
	0b00000000,
	0b1110000,
	0b0111000,
	0b0011100,
	0b0001110,
	0b0000111,
	0b0000111,
	0b0001110,
	0b0011100,
	0b0111000,
	0b1110000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	// ?
	0b01111110,
	0b11111111,
	0b11000011,
	0b00000011,
	0b00000110,
	0b00001100,
	0b00011000,
	0b00011000,
	0b00000000,
	0b00000000,
	0b00011000,
	0b00011000,
	0b00000000,
	0b00000000,
	0b00000000,
	// @
	0b00111110,
	0b01111111,
	0b11100011,
	0b11001111,
	0b11011111,
	0b11011011,
	0b11011011,
	0b11011111,
	0b11001110,
	0b11100001,
	0b01111111,
	0b00111110,
	0b00000000,
	0b00000000,
	0b00000000,
	// A
	0b01111110,
	0b11111111,
	0b11000011,
	0b11000011,
	0b11000011,
	0b11111111,
	0b11111111,
	0b11000011,
	0b11000011,
	0b11000011,
	0b11000011,
	0b11000011,
	0b00000000,
	0b00000000,
	0b00000000,
	// B
	0b11111110,
	0b11111111,
	0b11000011,
	0b11000011,
	0b11000011,
	0b11111110,
	0b11111111,
	0b11000011,
	0b11000011,
	0b11000011,
	0b11111111,
	0b11111110,
	0b00000000,
	0b00000000,
	0b00000000,
	// C
	0b01111110,
	0b11111111,
	0b11000011,
	0b11000000,
	0b11000000,
	0b11000000,
	0b11000000,
	0b11000000,
	0b11000000,
	0b11000011,
	0b11111111,
	0b01111110,
	0b00000000,
	0b00000000,
	0b00000000,
	// D
	0b11111110,
	0b11111111,
	0b11000011,
	0b11000011,
	0b11000011,
	0b11000011,
	0b11000011,
	0b11000011,
	0b11000011,
	0b11000011,
	0b11111111,
	0b11111110,
	0b00000000,
	0b00000000,
	0b00000000,
	// E
	0b11111111,
	0b11111111,
	0b11000000,
	0b11000000,
	0b11000000,
	0b11111100,
	0b11111100,
	0b11000000,
	0b11000000,
	0b11000000,
	0b11111111,
	0b11111111,
	0b00000000,
	0b00000000,
	0b00000000,
	// F
	0b11111111,
	0b11111111,
	0b11000000,
	0b11000000,
	0b11000000,
	0b11111100,
	0b11111100,
	0b11000000,
	0b11000000,
	0b11000000,
	0b11000000,
	0b11000000,
	0b00000000,
	0b00000000,
	0b00000000,
	// G
	0b01111110,
	0b11111111,
	0b11000011,
	0b11000000,
	0b11000000,
	0b11001111,
	0b11001111,
	0b11000011,
	0b11000011,
	0b11000011,
	0b11111111,
	0b01111110,
	0b00000000,
	0b00000000,
	0b00000000,
	// H
	0b11000011,
	0b11000011,
	0b11000011,
	0b11000011,
	0b11000011,
	0b11111111,
	0b11111111,
	0b11000011,
	0b11000011,
	0b11000011,
	0b11000011,
	0b11000011,
	0b00000000,
	0b00000000,
	0b00000000,
	// I
	0b11000000,
	0b11000000,
	0b11000000,
	0b11000000,
	0b11000000,
	0b11000000,
	0b11000000,
	0b11000000,
	0b11000000,
	0b11000000,
	0b11000000,
	0b11000000,
	0b00000000,
	0b00000000,
	0b00000000,
	// J
	0b11111110,
	0b11111110,
	0b00000110,
	0b00000110,
	0b00000110,
	0b00000110,
	0b00000110,
	0b00000110,
	0b00000110,
	0b11000110,
	0b11111110,
	0b01111100,
	0b00000000,
	0b00000000,
	0b00000000,
	// K
	0b11000011,
	0b11000111,
	0b11001110,
	0b11011100,
	0b11111000,
	0b11110000,
	0b11111000,
	0b11111100,
	0b11001110,
	0b11000111,
	0b11000011,
	0b11000011,
	0b00000000,
	0b00000000,
	0b00000000,
	// L
	0b11000000,
	0b11000000,
	0b11000000,
	0b11000000,
	0b11000000,
	0b11000000,
	0b11000000,
	0b11000000,
	0b11000000,
	0b11000000,
	0b11111111,
	0b11111111,
	0b00000000,
	0b00000000,
	0b00000000,
	// M
	0b11000011,
	0b11100111,
	0b11111111,
	0b11111111,
	0b11011011,
	0b11000011,
	0b11000011,
	0b11000011,
	0b11000011,
	0b11000011,
	0b11000011,
	0b11000011,
	0b00000000,
	0b00000000,
	0b00000000,
	// N
	0b11000011,
	0b11000011,
	0b11100011,
	0b11110011,
	0b11111011,
	0b11011111,
	0b11001111,
	0b11000111,
	0b11000011,
	0b11000011,
	0b11000011,
	0b11000011,
	0b00000000,
	0b00000000,
	0b00000000,
	// O
	0b01111110,
	0b11111111,
	0b11000011,
	0b11000011,
	0b11000011,
	0b11000011,
	0b11000011,
	0b11000011,
	0b11000011,
	0b11000011,
	0b11111111,
	0b01111110,
	0b00000000,
	0b00000000,
	0b00000000,
	// P
	0b11111110,
	0b11111111,
	0b11000011,
	0b11000011,
	0b11000011,
	0b11111111,
	0b11111110,
	0b11000000,
	0b11000000,
	0b11000000,
	0b11000000,
	0b11000000,
	0b00000000,
	0b00000000,
	0b00000000,
	// Q
	0b01111110,
	0b11111111,
	0b11000011,
	0b11000011,
	0b11000011,
	0b11000011,
	0b11000011,
	0b11000011,
	0b11000011,
	0b11000011,
	0b11111111,
	0b01111110,
	0b00000111,
	0b00000011,
	0b00000000,
	// R
	0b11111110,
	0b11111111,
	0b11000011,
	0b11000011,
	0b11000011,
	0b11111110,
	0b11111110,
	0b11000011,
	0b11000011,
	0b11000011,
	0b11000011,
	0b11000011,
	0b00000000,
	0b00000000,
	0b00000000,
	// S
	0b01111110,
	0b11111111,
	0b11000011,
	0b11000000,
	0b11000000,
	0b11111110,
	0b01111111,
	0b00000011,
	0b00000011,
	0b11000011,
	0b11111111,
	0b01111110,
	0b00000000,
	0b00000000,
	0b00000000,
	// T
	0b11111111,
	0b11111111,
	0b00011000,
	0b00011000,
	0b00011000,
	0b00011000,
	0b00011000,
	0b00011000,
	0b00011000,
	0b00011000,
	0b00011000,
	0b00011000,
	0b00000000,
	0b00000000,
	0b00000000,
	// U
	0b11000011,
	0b11000011,
	0b11000011,
	0b11000011,
	0b11000011,
	0b11000011,
	0b11000011,
	0b11000011,
	0b11000011,
	0b11000011,
	0b11111111,
	0b01111110,
	0b00000000,
	0b00000000,
	0b00000000,
	// V
	0b11000011,
	0b11000011,
	0b11000011,
	0b11000011,
	0b11000011,
	0b11000011,
	0b11000011,
	0b11000011,
	0b11100111,
	0b01111110,
	0b00111100,
	0b00011000,
	0b00000000,
	0b00000000,
	0b00000000,
	// W
	0b11000011,
	0b11000011,
	0b11000011,
	0b11000011,
	0b11000011,
	0b11000011,
	0b11000011,
	0b11011011,
	0b11011011,
	0b11011011,
	0b11111111,
	0b01100110,
	0b00000000,
	0b00000000,
	0b00000000,
	// X
	0b11000011,
	0b11000011,
	0b01100110,
	0b01100110,
	0b00111100,
	0b00011000,
	0b00011000,
	0b00111100,
	0b01100110,
	0b01100110,
	0b11000011,
	0b11000011,
	0b00000000,
	0b00000000,
	0b00000000,
	// Y
	0b11000011,
	0b11000011,
	0b01100110,
	0b01100110,
	0b00111100,
	0b00111100,
	0b00011000,
	0b00011000,
	0b00011000,
	0b00011000,
	0b00011000,
	0b00011000,
	0b00000000,
	0b00000000,
	0b00000000,
	// Z
	0b11111111,
	0b11111111,
	0b00000011,
	0b00000111,
	0b00001110,
	0b00011100,
	0b00111000,
	0b01110000,
	0b11100000,
	0b11000000,
	0b11111111,
	0b11111111,
	0b00000000,
	0b00000000,
	0b00000000,
	// [
	0b11111000,
	0b11111000,
	0b11000000,
	0b11000000,
	0b11000000,
	0b11000000,
	0b11000000,
	0b11000000,
	0b11000000,
	0b11000000,
	0b11111000,
	0b11111000,
	0b00000000,
	0b00000000,
	0b00000000,
	// "\"
	0b11000000,
	0b11000000,
	0b01100000,
	0b01100000,
	0b00110000,
	0b00011000,
	0b00011000,
	0b00001100,
	0b00000110,
	0b00000110,
	0b00000011,
	0b00000011,
	0b00000000,
	0b00000000,
	0b00000000,
	// ]
	0b11111000,
	0b11111000,
	0b00011000,
	0b00011000,
	0b00011000,
	0b00011000,
	0b00011000,
	0b00011000,
	0b00011000,
	0b00011000,
	0b11111000,
	0b11111000,
	0b00000000,
	0b00000000,
	0b00000000,
	// ^
	0b00011000,
	0b00111100,
	0b01111110,
	0b11100111,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	// _
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b11111111,
	0b11111111,
	0b00000000,
	0b00000000,
	0b00000000,
	// `
	0b11000000,
	0b11000000,
	0b01100000,
	0b01100000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	// a
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b01111110,
	0b11111110,
	0b11000110,
	0b11000110,
	0b11000110,
	0b11111110,
	0b01111110,
	0b00000000,
	0b00000000,
	0b00000000,
	// b
	0b11000000,
	0b11000000,
	0b11000000,
	0b11000000,
	0b11000000,
	0b11111100,
	0b11111110,
	0b11000110,
	0b11000110,
	0b11000110,
	0b11111110,
	0b11111100,
	0b00000000,
	0b00000000,
	0b00000000,
	// c
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b01111110,
	0b11111110,
	0b11000000,
	0b11000000,
	0b11000000,
	0b11111110,
	0b01111110,
	0b00000000,
	0b00000000,
	0b00000000,
	// d
	0b00000110,
	0b00000110,
	0b00000110,
	0b00000110,
	0b00000110,
	0b01111110,
	0b11111110,
	0b11000110,
	0b11000110,
	0b11000110,
	0b11111110,
	0b01111110,
	0b00000000,
	0b00000000,
	0b00000000,
	// e
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b01111100,
	0b11111110,
	0b11000110,
	0b11111100,
	0b11000000,
	0b11111110,
	0b01111110,
	0b00000000,
	0b00000000,
	0b00000000,
	// f
	0b00111100,
	0b01111100,
	0b01100000,
	0b01100000,
	0b01100000,
	0b11111000,
	0b11111000,
	0b01100000,
	0b01100000,
	0b01100000,
	0b01100000,
	0b01100000,
	0b00000000,
	0b00000000,
	0b00000000,
	// g
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b01111110,
	0b11111110,
	0b11000110,
	0b11000110,
	0b11000110,
	0b11111110,
	0b01111110,
	0b00000110,
	0b11111110,
	0b01111100,
	// h
	0b11000000,
	0b11000000,
	0b11000000,
	0b11000000,
	0b11000000,
	0b11111100,
	0b11111110,
	0b11000110,
	0b11000110,
	0b11000110,
	0b11000110,
	0b11000110,
	0b00000000,
	0b00000000,
	0b00000000,
	// i
	0b00000000,
	0b00000000,
	0b11000000,
	0b11000000,
	0b00000000,
	0b11000000,
	0b11000000,
	0b11000000,
	0b11000000,
	0b11000000,
	0b11110000,
	0b01110000,
	0b00000000,
	0b00000000,
	0b00000000,
	// j
	0b00000000,
	0b00000000,
	0b00011000,
	0b00011000,
	0b00000000,
	0b00011000,
	0b00011000,
	0b00011000,
	0b00011000,
	0b00011000,
	0b00011000,
	0b00011000,
	0b00011000,
	0b11111000,
	0b01110000,
	// k
	0b11000000,
	0b11000000,
	0b11000000,
	0b11000000,
	0b11001100,
	0b11011000,
	0b11110000,
	0b11110000,
	0b11011000,
	0b11001100,
	0b11000110,
	0b11000110,
	0b00000000,
	0b00000000,
	0b00000000,
	// l
	0b11000000,
	0b11000000,
	0b11000000,
	0b11000000,
	0b11000000,
	0b11000000,
	0b11000000,
	0b11000000,
	0b11000000,
	0b11000000,
	0b11111000,
	0b01111000,
	0b00000000,
	0b00000000,
	0b00000000,
	// m
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b01111100,
	0b11111110,
	0b11010110,
	0b11010110,
	0b11000110,
	0b11000110,
	0b11000110,
	0b00000000,
	0b00000000,
	0b00000000,
	// n
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b01111100,
	0b11111110,
	0b11000110,
	0b11000110,
	0b11000110,
	0b11000110,
	0b11000110,
	0b00000000,
	0b00000000,
	0b00000000,
	// o
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b01111100,
	0b11111110,
	0b11000110,
	0b11000110,
	0b11000110,
	0b11111110,
	0b01111100,
	0b00000000,
	0b00000000,
	0b00000000,
	// p
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b11111100,
	0b11111110,
	0b11000110,
	0b11000110,
	0b11000110,
	0b11111110,
	0b11111100,
	0b11000000,
	0b11000000,
	0b11000000,
	// q
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b01111110,
	0b11111110,
	0b11000110,
	0b11000110,
	0b11000110,
	0b11111110,
	0b01111110,
	0b00000110,
	0b00000110,
	0b00000110,
	// r
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b11011000,
	0b11111000,
	0b11100000,
	0b11000000,
	0b11000000,
	0b11000000,
	0b11000000,
	0b00000000,
	0b00000000,
	0b00000000,
	// s
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b01111100,
	0b11111110,
	0b11000000,
	0b01111100,
	0b00000110,
	0b11111110,
	0b01111100,
	0b00000000,
	0b00000000,
	0b00000000,
	// t
	0b00110000,
	0b00110000,
	0b00110000,
	0b11111100,
	0b11111100,
	0b00110000,
	0b00110000,
	0b00110000,
	0b00110000,
	0b00110000,
	0b00111110,
	0b00011110,
	0b00000000,
	0b00000000,
	0b00000000,
	// u
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b11000110,
	0b11000110,
	0b11000110,
	0b11000110,
	0b11000110,
	0b11111110,
	0b01111100,
	0b00000000,
	0b00000000,
	0b00000000,
	// v
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b11000110,
	0b11000110,
	0b11000110,
	0b11000110,
	0b11101110,
	0b01111100,
	0b00111000,
	0b00000000,
	0b00000000,
	0b00000000,
	// w
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b11000110,
	0b11000110,
	0b11000110,
	0b11010110,
	0b11010110,
	0b11111110,
	0b01111100,
	0b00000000,
	0b00000000,
	0b00000000,
	// x
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b11000110,
	0b11000110,
	0b01111100,
	0b00111000,
	0b01111100,
	0b11000110,
	0b11000110,
	0b00000000,
	0b00000000,
	0b00000000,
	// y
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b11000110,
	0b11000110,
	0b11000110,
	0b11000110,
	0b11000110,
	0b11111110,
	0b01111110,
	0b00000110,
	0b11111110,
	0b01111100,
	// z
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b11111110,
	0b11111110,
	0b00001100,
	0b00111000,
	0b01100000,
	0b11111110,
	0b11111110,
	0b00000000,
	0b00000000,
	0b00000000,
	// {
	0b00011100,
	0b00111100,
	0b00110000,
	0b00110000,
	0b00110000,
	0b11100000,
	0b11100000,
	0b00110000,
	0b00110000,
	0b00110000,
	0b00111100,
	0b00011100,
	0b00000000,
	0b00000000,
	0b00000000,
	// |
	0b11000000,
	0b11000000,
	0b11000000,
	0b11000000,
	0b11000000,
	0b11000000,
	0b11000000,
	0b11000000,
	0b11000000,
	0b11000000,
	0b11000000,
	0b11000000,
	0b00000000,
	0b00000000,
	0b00000000,
	// }
	0b11100000,
	0b11110000,
	0b00110000,
	0b00110000,
	0b00110000,
	0b00011100,
	0b00011100,
	0b00110000,
	0b00110000,
	0b00110000,
	0b11110000,
	0b11100000,
	0b00000000,
	0b00000000,
	0b00000000,
	// ~
	0b01110011,
	0b11111011,
	0b11011111,
	0b11001110,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	// ae
	0b00000000,
	0b00000000,
	0b00000000,
	0b01001000,
	0b00000000,
	0b00000000,
	0b01111000,
	0b00001100,
	0b01111100,
	0b11001100,
	0b11001100,
	0b01110110,
	0b00000000,
	0b00000000,
	0b00000000,
	// oe
	0b00000000,
	0b00000000,
	0b00000000,
	0b01001000,
	0b00000000,
	0b00000000,
	0b01111100,
	0b11000110,
	0b11000110,
	0b11000110,
	0b11000110,
	0b01111100,
	0b00000000,
	0b00000000,
	0b00000000,
	// ue
	0b00000000,
	0b00000000,
	0b00000000,
	0b01001000,
	0b00000000,
	0b00000000,
	0b11001100,
	0b11001100,
	0b11001100,
	0b11001100,
	0b11001100,
	0b01110110,
	0b00000000,
	0b00000000,
	0b00000000,
	// Ae
	0b00000000,
	0b01000100,
	0b00000000,
	0b00010000,
	0b00111000,
	0b01101100,
	0b11000110,
	0b11000110,
	0b11111110,
	0b11000110,
	0b11000110,
	0b11000110,
	0b00000000,
	0b00000000,
	0b00000000,
	// Oe
	0b00000000,
	0b01000100,
	0b00000000,
	0b01111100,
	0b11000110,
	0b11000110,
	0b11000110,
	0b11000110,
	0b11000110,
	0b11000110,
	0b11000110,
	0b01111100,
	0b00000000,
	0b00000000,
	0b00000000,
	// Ue
	0b00000000,
	0b01000100,
	0b00000000,
	0b11000110,
	0b11000110,
	0b11000110,
	0b11000110,
	0b11000110,
	0b11000110,
	0b11000110,
	0b11000110,
	0b01111100,
	0b00000000,
	0b00000000,
	0b00000000,
	// ss
	0b00000000,
	0b00000000,
	0b00000000,
	0b01111000,
	0b11001100,
	0b11001100,
	0b11111000,
	0b11001100,
	0b11001100,
	0b11001100,
	0b11111000,
	0b11000000,
	0b11000000,
	0b11000000,
	0b00000000,
	// Exit
	0b00011000,
	0b00111100,
	0b01111110,
	0b11111111,
	0b00011000,
	0b00011000,
	0b00011000,
	0b00011000,
	0b00011000,
	0b00011000,
	0b00011000,
	0b00011000,
	0b00000000,
	0b00000000,
	0b00000000,
	// Backspace
	0b00000000,
	0b00000000,
	0b00010011,
	0b00110011,
	0b01110011,
	0b11111111,
	0b11111111,
	0b01110011,
	0b00110011,
	0b00010011,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	// Delete
	0b00000000,
	0b00000000,
	0b11000010,
	0b11000110,
	0b11001110,
	0b11111111,
	0b11111111,
	0b11001110,
	0b11000110,
	0b11000010,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	// Insert
	0b00000000,
	0b00000000,
	0b11001000,
	0b11001100,
	0b11001110,
	0b11111111,
	0b11111111,
	0b11001110,
	0b11001100,
	0b11001000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	// Left
	0b00000000,
	0b00000000,
	0b00010000,
	0b00110000,
	0b01110000,
	0b11111111,
	0b11111111,
	0b01110000,
	0b00110000,
	0b00010000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	// Right
	0b00000000,
	0b00000000,
	0b00001000,
	0b00001100,
	0b00001110,
	0b11111111,
	0b11111111,
	0b00001110,
	0b00001100,
	0b00001000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
};

Large::Large( void)
     : Type( Data, 8, 15, 9, 16)
{
}
