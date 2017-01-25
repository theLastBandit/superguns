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


void initNES()
{
	DDRB = 0xFF;
	DDRC = 0x03;
	DDRD = 0xF8;
	PORTC = 0xFF;
	PORTB = 0xFF;
	PORTD = 0xFF;	
}

void scanNES()
{
	uint8_t i;
    uint8_t data = 0 ;

    // Toggle LATCH
    PORTC |= NES_LATCH;
    _delay_us(12);
    PORTC &= ~NES_LATCH;

	// Clock in 8 bits of data
    for (i=0; i< 8; i++)
	{
		PORTC &= ~NES_CLOCK;
		_delay_us(6);
		data <<= 1;
		
      // stuff the data into a byte for further analysis
//		if (bit_is_clear(PINC, 2)){
//			data |= 1;
//		}
		if (!(PINC & NES_DATA))
		{
			data |= 1;
		}
		_delay_us(6);
		PORTC |= NES_CLOCK;
    }
	
	controller.up 		= data & 0b00001000;
	controller.down 	= data & 0b00000100;
	controller.left 	= data & 0b00000010;
	controller.right 	= data & 0b00000001;
	controller.b1 		= data & 0b10000000;
	controller.b2 		= data & 0b01000000;
	controller.start 	= data & 0b00010000;
	controller.coin 	= data & 0b00100000;
}	
	