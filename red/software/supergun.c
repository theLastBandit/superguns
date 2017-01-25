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
#include <avr/interrupt.h>
#include "supergun.h"

controller_t controller;

void main(void) 
{
	uint8_t padcfg; 
	DDRB = 0xFF;
	DDRC = 0x00;
	DDRD = 0xF8;
	PORTB = 0xFF;
	PORTC = 0xFF;
	PORTD = 0xFF;

	cli();
	// Setup timer for Autofire
	TCCR1B |= ((1 << CS10) | (1 << CS11));

	switch (PIND & 0x07)
	{
		case SATURN_PAD: 
			padcfg = initSaturn();
			while(1)
			{
				scanSaturn(padcfg);
				driveJamma();
				_delay_ms(SCAN);
			}
		case PSX_PAD:
			padcfg = initPSX();
			while(1)
			{
				scanPSX(padcfg);
				driveJamma();
				_delay_ms(SCAN);
			}
		case MEGADRIVE_PAD:
			padcfg = initMegadrive();
			while(1)
			{	
				scanMegadrive(padcfg);
				driveJamma();
				_delay_ms(SCAN);
			}
		case SNES_PAD:
			padcfg = initSNES();
			while(1)
			{	
				scanSNES(padcfg);
				driveJamma();
				_delay_ms(SCAN);
			}
		case NES_PAD:
			initNES();
			while(1)
			{	
				scanNES();
				driveJamma();
				_delay_ms(SCAN);
			}
		case PCE_PAD:
			initPCE();
			while(1)
			{	
				scanPCE();
				driveJamma();
				_delay_ms(SCAN);
			}
		default: // Neogeo
			initNeoGeo();
			while(1)
			{	
				scanNeoGeo();
				driveJamma();
				_delay_ms(SCAN);
			}
	}
}


void driveJamma()
{
	static uint8_t autofire;
	static uint16_t startcount;
	static volatile uint8_t autotick;
	
	(controller.up) 	? 	JAMMA_UP() 		: N_JAMMA_UP();		
	(controller.down) 	? 	JAMMA_DOWN() 	: N_JAMMA_DOWN();	
	(controller.left) 	?	JAMMA_LEFT() 	: N_JAMMA_LEFT();	
	(controller.right) 	? 	JAMMA_RIGHT() 	: N_JAMMA_RIGHT();	
	(controller.coin) 	?	JAMMA_COIN() 	: N_JAMMA_COIN();	

	// Is Start button held for approx 6 seconds - used to enable/disable Autofire
	if (controller.start) 	
	{	
		startcount++;
		if (startcount > 400 ) 
		{	
			autofire = autofire ^ 1;
			startcount = 0;
		} 
		JAMMA_START();
	}
	else 
	{
		N_JAMMA_START();
		startcount = 0;
	}
	
	// Is Autofire set ?
	if (autofire)
	{
		if ((controller.b1) && (autotick))
		{ 
			JAMMA_B1(); 
		}
		if ((controller.b2) && (autotick))
		{ 
			JAMMA_B2(); 
		}
		if ((controller.b3) && (autotick))
		{ 
			JAMMA_B3(); 
		}
		if ((controller.b4) && (autotick))
		{ 
			JAMMA_B4(); 
		}
		if ((controller.b5) && (autotick))
		{ 
			JAMMA_B5(); 
		}
		if ((controller.b6) && (autotick))
		{ 
			JAMMA_B6(); 
		}
		
		// Check Timer
		if (TCNT1 > 14000) 
		{
			TCNT1 = 0;
			autotick = autotick ^ 1;
			N_JAMMA_B1();N_JAMMA_B2();N_JAMMA_B3();
			N_JAMMA_B4();N_JAMMA_B5();N_JAMMA_B6();
			
		}
	}
	else 
	{
		(controller.b1) ? JAMMA_B1() : N_JAMMA_B1();
		(controller.b2) ? JAMMA_B2() : N_JAMMA_B2();
		(controller.b3) ? JAMMA_B3() : N_JAMMA_B3();
		(controller.b4) ? JAMMA_B4() : N_JAMMA_B4();
		(controller.b5) ? JAMMA_B5() : N_JAMMA_B5();
		(controller.b6) ? JAMMA_B6() : N_JAMMA_B6();
	}
}
