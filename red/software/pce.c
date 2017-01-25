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


void initPCE() 
{
	DDRB = 0xFF;
	DDRC = 0x03;
	DDRD = 0xFF;
	PORTC = 0x00;
	PORTD = 0xFF;
	PORTB = 0xFF;
}


void scanPCE() 
{	
	// Select High & OE Low
	PORTC &= ~PCE_OE;
	PORTC |= PCE_SELECT;
	
	// /OE LOW
	PORTC &= ~PCE_OE;
	_delay_us(10);

	controller.up = !(PINC & PCE_D0);
	controller.down = !(PINC & PCE_D1);
	controller.left = !(PINC & PCE_D2);
	controller.right = !(PINC & PCE_D3);

	PORTC &= ~PCE_SELECT;
	_delay_us(10);

	controller.b1 = !(PINC & PCE_D0);
	controller.b2 = !(PINC & PCE_D3);
	controller.start = !(PINC & PCE_D2);
	controller.coin = !(PINC & PCE_D1);

	// Data Select HIGH
	PORTC |= PCE_SELECT;
	_delay_us(10);
}
