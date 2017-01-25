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

uint8_t initMegadrive(void) 
{
	// set up DDR
	DDRB = 0xFF;
	DDRC = 0x00;
	DDRD = 0xF8;
	PORTC = 0xFF;
	PORTB = 0x7F;
	PORTD = 0xFF;
  
	// Select LOW
	PORTB &= ~MD_DB7; 
	_delay_us(MD_DELAY);
	
	// Flip button rows if 'X' held
	// Select Toggle 
	PORTB |= MD_DB7; 
	_delay_us(MD_DELAY);
	PORTB &= ~MD_DB7; 
	_delay_us(MD_DELAY);
	PORTB |= MD_DB7; 
	_delay_us(MD_DELAY);	
	
	if (!(PINC & MD_DB3))  //was DB6
	{
		return 1;
	}
	else 
	{
		return 0;
	}
}

void scanMegadrive(uint8_t padcfg) 
{

	PORTB |= MD_DB7; // select HIGH
	_delay_us(MD_DELAY);

	controller.up 	= !(PINC & MD_DB1);			// Up
	controller.down = !(PINC & MD_DB2);			// Down
	controller.left = !(PINC & MD_DB3);			// Left
	controller.right = !(PINC & MD_DB4);		// Right
	
	// Buttons flipped ?
	if (!padcfg)
	{
		controller.b2 	= !(PINC & MD_DB6);			// B
		controller.b3 	= !(PINC & MD_DB9);			// C
	}
	else 
	{
		controller.b5 	= !(PINC & MD_DB6);			// B - Y
		controller.b6 	= !(PINC & MD_DB9);			// C - Z
	}
	// Select LOW
	PORTB &= ~MD_DB7;
	_delay_us(MD_DELAY);

	// Get A and START buttons state
	if (!padcfg)
	{
		controller.b1 	= !(PINC & MD_DB6);			// A
	}
	else
	{
		controller.b4 	= !(PINC & MD_DB6);			// A - X
	}
	controller.start = !(PINC & MD_DB9);			// Start
	
	// Select HIGH
	PORTB |= MD_DB7; 
	_delay_us(MD_DELAY);
	// Select LOW
	PORTB &= ~MD_DB7; 
	_delay_us(MD_DELAY);

	// Test to see if this is a 6 button controller
	if ( !(PINC & MD_DB1) && !(PINC & MD_DB2) && !(PINC & MD_DB3) && !(PINC & MD_DB4) )
	{
		// Select HIGH
		PORTB |= MD_DB7; 
		_delay_us(MD_DELAY);
		if (!padcfg)
		{
			controller.b6 	= !(PINC & MD_DB1);		// Z
			controller.b5 	= !(PINC & MD_DB2);		// Y
			controller.b4 	= !(PINC & MD_DB3);		// X
		}
		else
		{	
			controller.b3 	= !(PINC & MD_DB1);		// Z - C
			controller.b2 	= !(PINC & MD_DB2);		// Y - B
			controller.b1 	= !(PINC & MD_DB3);		// X - A
		}
		controller.coin = !(PINC & MD_DB4);		// Mode
		
		PORTB &= ~MD_DB7; 
		_delay_us(MD_DELAY);
		PORTB |= MD_DB7;
		_delay_us(MD_DELAY);
		PORTB &= ~MD_DB7;
		
		_delay_ms(2);
	}	
}
