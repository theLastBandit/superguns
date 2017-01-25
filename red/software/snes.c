/*
* SuperGun Console Controller Interface
* Copyright (c) 2014 Shane Kiely - shane.kiely@gmail.com
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <avr/io.h>
#include <util/delay.h>
#include "supergun.h"


uint8_t initSNES()
{
	DDRB = 0xFF;
	DDRC = 0x03;
	DDRD = 0xF8;
	PORTC = 0xFF;
	PORTB = 0xFF;
	PORTD = 0xFF;
	
	_delay_ms(10);
	
	// Any buttons held down will determine if alternative mapping is used
	uint8_t i;
    uint8_t byte1 = 0;
	
    // Toggle LATCH
    PORTC |= NES_LATCH;
    _delay_us(12);
    PORTC &= ~NES_LATCH;

	// Clock in 8 bits of data
    for (i=0; i< 8; i++)
	{
		PORTC &= ~NES_CLOCK;
		_delay_us(6);
		byte1 <<= 1;
		
		if (!(PINC & NES_DATA))
		{
			byte1 |= 1;
		}
		_delay_us(6);
		PORTC |= NES_CLOCK;
    }
	
	switch (byte1)
	{
		// 'Select'
		case 0b00100000:
			return 4;
		// 'Start' 
		case 0b00010000:
			return 3;
		// 'B' 
		case 0b10000000:
			return 1;
		// 'Y'
		case 0b01000000:
			return 2;
		default:
		// 'A'
			return 0;
	}

}

void scanSNES(uint8_t padcfg)
{
	uint8_t i;
    uint8_t byte1, byte2;
		
    // Toggle LATCH
    PORTC |= NES_LATCH;
    _delay_us(12);
    PORTC &= ~NES_LATCH;

	// Clock in first 8 bits of data
    for (i=0; i< 8; i++)
	{
		PORTC &= ~NES_CLOCK;
		_delay_us(6);
		byte1 <<= 1;
		
		if (!(PINC & NES_DATA))
		{
			byte1 |= 1;
		}
		_delay_us(6);
		PORTC |= NES_CLOCK;
    }
	// Clock in second 8 bits of data
    for (i=0; i< 8; i++)
	{
		PORTC &= ~NES_CLOCK;
		_delay_us(6);
		byte2 >>= 1;
		
		if (!(PINC & NES_DATA))
		{
			byte2 |= 0x80;
		}
		_delay_us(6);
		PORTC |= NES_CLOCK;
    }

	switch (padcfg)
	{
		// Default mapping
		case 0:		// A B X Y L R	
			controller.up 		= byte1 & 0b00001000; 	// Up
			controller.down 	= byte1 & 0b00000100; 	// Down
			controller.left 	= byte1 & 0b00000010;	// Left
			controller.right 	= byte1 & 0b00000001;	// Right
			controller.b1 		= byte2 & 0b00000001;	// A
			controller.b2 		= byte1 & 0b10000000;	// B
			controller.b3 		= byte2 & 0b00000010;	// X
			controller.b4 		= byte1 & 0b01000000;	// Y
			controller.b5 		= byte2 & 0b00000100;	// L
			controller.b6 		= byte2 & 0b00001000;	// R
			controller.start 	= byte1 & 0b00010000;	// Start
			controller.coin 	= byte1 & 0b00100000;	// Select
			break;
		case 1:		// B Y A X L R
			controller.up 		= byte1 & 0b00001000; 	// Up
			controller.down 	= byte1 & 0b00000100; 	// Down
			controller.left 	= byte1 & 0b00000010;	// Left
			controller.right 	= byte1 & 0b00000001;	// Right
			controller.b3 		= byte2 & 0b00000001;	// A
			controller.b1 		= byte1 & 0b10000000;	// B
			controller.b4 		= byte2 & 0b00000010;	// X
			controller.b2 		= byte1 & 0b01000000;	// Y
			controller.b5 		= byte2 & 0b00000100;	// L
			controller.b6 		= byte2 & 0b00001000;	// R
			controller.start 	= byte1 & 0b00010000;	// Start
			controller.coin 	= byte1 & 0b00100000;	// Select
			break;
		case 2:		// Y B A X L R
			controller.up 		= byte1 & 0b00001000; 	// Up
			controller.down 	= byte1 & 0b00000100; 	// Down
			controller.left 	= byte1 & 0b00000010;	// Left
			controller.right 	= byte1 & 0b00000001;	// Right
			controller.b3 		= byte2 & 0b00000001;	// A
			controller.b2 		= byte1 & 0b10000000;	// B
			controller.b4 		= byte2 & 0b00000010;	// X
			controller.b1 		= byte1 & 0b01000000;	// Y
			controller.b5 		= byte2 & 0b00000100;	// L
			controller.b6 		= byte2 & 0b00001000;	// R
			controller.start 	= byte1 & 0b00010000;	// Start
			controller.coin 	= byte1 & 0b00100000;	// Select
			break;
		case 3:		// Y X L B A R
			controller.up 		= byte1 & 0b00001000; 	// Up
			controller.down 	= byte1 & 0b00000100; 	// Down
			controller.left 	= byte1 & 0b00000010;	// Left
			controller.right 	= byte1 & 0b00000001;	// Right
			controller.b5 		= byte2 & 0b00000001;	// A
			controller.b4 		= byte1 & 0b10000000;	// B
			controller.b2 		= byte2 & 0b00000010;	// X
			controller.b1 		= byte1 & 0b01000000;	// Y
			controller.b3 		= byte2 & 0b00000100;	// L
			controller.b6 		= byte2 & 0b00001000;	// R
			controller.start 	= byte1 & 0b00010000;	// Start
			controller.coin 	= byte1 & 0b00100000;	// Select
			break;
		case 4:		// B A R Y X L
			controller.up 		= byte1 & 0b00001000; 	// Up
			controller.down 	= byte1 & 0b00000100; 	// Down
			controller.left 	= byte1 & 0b00000010;	// Left
			controller.right 	= byte1 & 0b00000001;	// Right
			controller.b2 		= byte2 & 0b00000001;	// A
			controller.b1 		= byte1 & 0b10000000;	// B
			controller.b5 		= byte2 & 0b00000010;	// X
			controller.b4 		= byte1 & 0b01000000;	// Y
			controller.b3 		= byte2 & 0b00000100;	// L
			controller.b6 		= byte2 & 0b00001000;	// R
			controller.start 	= byte1 & 0b00010000;	// Start
			controller.coin 	= byte1 & 0b00100000;	// Select
			break;
	}		
}
