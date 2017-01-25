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

void initNeoGeo()
{
	DDRB = 0x7F;
	DDRC = 0x00;
	DDRD = 0x78;
	PORTC = 0xFF;
	PORTB = 0xFF;
	PORTD = 0xFF;
}

void scanNeoGeo()
{
	//	Other controls directly connected to Jamma
	controller.down = !(PINC & (1<<4));
	controller.right = !(PINC & (1<<3));
	controller.coin = !(PINC & (1<<0));
	controller.start = !(PINC & (1<<5));
	controller.b4 = !(PINC & (1<<1));
	controller.b3 = !(PINB & (1<<7));
	controller.b2 = !(PINC & (1<<2));
	controller.b5 = !(PIND & (1<<2));
	controller.b6 = !(PIND & (1<<0));
}
