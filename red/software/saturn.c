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

uint8_t initSaturn(void) 
{
	uint8_t padcfg = 0;
	DDRB = 0xFF;
	DDRD = 0xF8;
	DDRC = 0x30;
	PORTC = 0xFF;
	PORTD = 0xFF;
	PORTB = 0xFF;
	
	DDRC &= ~(SATURN_D0 | SATURN_D1 | SATURN_D2 | SATURN_D3);
	DDRC |= (SATURN_S0 | SATURN_S1);
	
	// Test for 'X' held down to trigger flip mode
	//S0 = 0, S1 = 0	
	PORTC &= ~(SATURN_S0|SATURN_S1);
	_delay_us(2);
	if (!(PINC & SATURN_D2)) { padcfg = 1; }

	return padcfg;
}

void scanSaturn(uint8_t padcfg)
{
	_delay_us(2);

	// S0 = 1, S1 = 1
	PORTC |= (SATURN_S0 | SATURN_S1);
	_delay_us(2);
	
	controller.coin = !(PINC & SATURN_D3); 				// Left Trigger
	
	// S0 = 0,  S1 = 1
	PORTC &= ~(SATURN_S0);
	_delay_us(2);

	controller.up = !(PINC & SATURN_D0);				// Up
	controller.down = !(PINC & SATURN_D1);				// Down
	controller.left = !(PINC & SATURN_D2);				// Left
	controller.right = !(PINC & SATURN_D3);				// Right

	// S0 = 1, S1 = 0
	PORTC = (PORTC & ~(SATURN_S1)) | (SATURN_S0);
	_delay_us(2);

	if (!padcfg)  // Flip buttons rows 
	{
		controller.b2 = !(PINC & SATURN_D0);			// B
		controller.b3 = !(PINC & SATURN_D1);			// C
		controller.b1 = !(PINC & SATURN_D2);			// A
	}
	else
	{
		controller.b5 = !(PINC & SATURN_D0);			// B - Y
		controller.b6 = !(PINC & SATURN_D1);			// C - Z
		controller.b4 = !(PINC & SATURN_D2);			// A - X
	}
	controller.start = !(PINC & SATURN_D3);				// Start

	// S0 = 0, S1 = 0
	PORTC &= ~(SATURN_S0|SATURN_S1);
	_delay_us(2);

	if (!padcfg)
	{
		controller.b6 = !(PINC & SATURN_D0);			// Z
		controller.b5 = !(PINC & SATURN_D1);			// Y
		controller.b4 = !(PINC & SATURN_D2);			// X
	}
	else 
	{
		controller.b3 = !(PINC & SATURN_D0);			// Z - C
		controller.b2 = !(PINC & SATURN_D1);			// Y - B
		controller.b1 = !(PINC & SATURN_D2);			// X - A		
	}
	controller.coin = !(PINC & SATURN_D3);				// Right Trigger
}

