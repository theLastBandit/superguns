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
#include <avr/pgmspace.h>
#include <util/delay.h>
#include "supergun.h"

static uint8_t msgin[9];

uint8_t initPSX()
{
	uint8_t padcfg = 2;
	DDRB = 0xFF;
	DDRD = 0xF8;
	DDRC = 0x0E;
	PORTB = 0xFF;
	PORTC = 0xFF;
	PORTD = 0xFF;
  
	PORTC |= PSX_ATN;
	PORTC |= PSX_CMD;
	PORTC |= PSX_CLK;

	uint8_t poke[] = {0x01, 0x42, 0x00, 0x00, 0x00};
	sendCmdPSX(poke, 5);
	sendCmdPSX(poke, 5);
	PORTC &= ~PSX_ATN;
	PORTC |= PSX_CMD;
	PORTC |= PSX_CLK;
	_delay_us(6);
		
	// Setup pad
	uint8_t entercfg[] = {0x01, 0x43, 0x00, 0x01, 0x00};
	sendCmdPSX(entercfg, 5);
	
	uint8_t gettype[] = {0x01, 0x45, 0x00, 0x5A, 0x5A, 0x5A, 0x5A, 0x5A, 0x5A};
	sendCmdPSX(gettype, 9);
	
	uint8_t setmode[] = {0x01, 0x44, 0x00, 0x01, 0x03, 0x00, 0x00, 0x00, 0x00};
	sendCmdPSX(setmode,9);
	
	uint8_t exitcfg[] = {0x01, 0x43, 0x00, 0x00, 0x5A, 0x5A, 0x5A, 0x5A, 0x5A};
	sendCmdPSX(exitcfg,9);
	
	scanPSX(0);
	
	// Test to see if any buttons held down

	if (!(msgin[4] & 0x02)) // R2
	{
		padcfg = 0; 
	}	
	if (!(msgin[4] & 0x08)) // R1
	{
		padcfg = 1; 
	}	
	if (!(msgin[4] & 0x40)) // X
	{
		padcfg = 2; 
	}
	if (!(msgin[4] & 0x80)) // []
	{
		padcfg = 3; 
	}
	return padcfg;
 }


 uint8_t moveBytePSX(uint8_t byteout)
 {
	uint8_t bytein,i;
	
		for(i = 0; i < 8; i++) 
		{
			// Clock Low
			PORTC &= ~PSX_CLK;
			if( byteout & (1 << i))
			{
				PORTC |= PSX_CMD;
			}
			else
			{
				PORTC &= ~PSX_CMD;
			}
			_delay_us(PSX_DELAY);

			bytein >>= 1;
			// Clock High
			PORTC |= PSX_CLK;
			if( PINC & PSX_DATA) 
			{ 
				bytein |= (1 << 7);
			}
			_delay_us(PSX_DELAY);
		}
		
	PORTC |= PSX_CLK;
	_delay_us(3);

	return bytein;
 }
 
 void sendCmdPSX(uint8_t msgout[], uint8_t msgsize)
{
	uint8_t i;
	
	// ATN Low, CMD High, CLK High
	PORTC &= ~PSX_ATN;
	PORTC |= PSX_CMD;
	PORTC |= PSX_CLK;
	_delay_us(6);

	for(i = 0; i < msgsize; i++) 
	{
		msgin[i] = moveBytePSX(msgout[i]);
	}
	// ATN High
	PORTC |= PSX_ATN;
	_delay_ms(1);
}

void scanPSX(uint8_t padcfg)
{
	uint8_t poke[] = {0x01, 0x42, 0x00, 0x5a, 0x5a, 0x5a, 0x5a, 0x5a, 0x5a};
	sendCmdPSX(poke, 9);
	
	switch (padcfg)
	{
		// Default mapping
		case 0:	 // Namco Stick bottom row first
			controller.b1 = !(msgin[4] & 0x40);	// X
			controller.b2 = !(msgin[4] & 0x20); // O
			controller.b3 = !(msgin[4] & 0x02); // R2
			controller.b4 = !(msgin[4] & 0x80); // []
			controller.b5 = !(msgin[4] & 0x10); // ^
			controller.b6 = !(msgin[4] & 0x08); // R1
		break;
		case 1: // Namo Stick top row first
			controller.b1 = !(msgin[4] & 0x80); // []
			controller.b2 = !(msgin[4] & 0x10); // ^
			controller.b3 = !(msgin[4] & 0x08); // R1
			controller.b4 = !(msgin[4] & 0x40); // X
			controller.b5 = !(msgin[4] & 0x20); // O
			controller.b6 = !(msgin[4] & 0x02); // R2
		break;
		case 2:	// PS2 layout
			controller.b1 = !(msgin[4] & 0x40);	// X
			controller.b2 = !(msgin[4] & 0x20); // O
			controller.b3 = !(msgin[4] & 0x80); // []
			controller.b4 = !(msgin[4] & 0x10); // ^
			controller.b5 = !(msgin[4] & 0x04); // L1
			controller.b6 = !(msgin[4] & 0x08); // R1
		break;
		case 3:	// PS2 alt layout
			controller.b1 = !(msgin[4] & 0x80); // []
			controller.b2 = !(msgin[4] & 0x40);	// X
			controller.b3 = !(msgin[4] & 0x20); // O
			controller.b4 = !(msgin[4] & 0x10); // ^
			controller.b5 = !(msgin[4] & 0x04); // L1
			controller.b6 = !(msgin[4] & 0x08); // R1
		break;				
	}
	
	controller.start = !(msgin[3] & 0x08);
	controller.coin = !(msgin[3] & 0x01);

	// Analogue Pad
	if ((msgin[1] == 0x73) || (msgin[1] == 0x79))
	{
		if ((msgin[8] < 40) || !(msgin[3] & 0x10))
		{
			controller.up = 1;
		} 
		else 
		{
			controller.up = 0;
		}
		if ((msgin[8] > 210) || !(msgin[3] & 0x40))
		{
			controller.down = 1;
		} 
		else 
		{
			controller.down = 0;
		}
		
		if ((msgin[7] < 40) || !(msgin[3] & 0x80))
		{
			controller.left = 1;
		} 
		else 
		{
			controller.left = 0;
		}
		if ((msgin[7] > 210) || !(msgin[3] & 0x20))
		{
			controller.right = 1;
		} 
		else 
		{
			controller.right = 0;
		}		
	}
	else 
	{	// Digital Pad - we assume or not care if its a bogey device..
		controller.up =  !(msgin[3] & 0x10);
		controller.down =  !(msgin[3] & 0x40);
		controller.left =  !(msgin[3] & 0x80);
		controller.right =  !(msgin[3] & 0x20);
	}
}
