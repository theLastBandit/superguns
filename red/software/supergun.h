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
 
 /*
  *	Revision 1.2
  */
  
#ifndef SUPERGUN_H_
#define SUPERGUN_H_

typedef struct {
	uint8_t up;
	uint8_t down;
	uint8_t left;
	uint8_t right;
	uint8_t b1;
	uint8_t b2;
	uint8_t b3;
	uint8_t b4;
	uint8_t b5;
	uint8_t b6;
	uint8_t start;
	uint8_t coin;
} controller_t;

extern controller_t controller;

#define AF_DELAY		200
#define SCAN 			10
#define MD_DELAY 		14
#define PSX_DELAY		20


#define MEGADRIVE_PAD	0
#define SATURN_PAD		1
#define SNES_PAD		2
#define NES_PAD			3
#define PSX_PAD			4
#define PCE_PAD			5
#define ATARI			6
#define NEOGEO_PAD		7

#define SATURN_S0	(1<<4) 
#define SATURN_S1	(1<<5)
#define SATURN_D0	(1<<0)
#define SATURN_D1	(1<<1)
#define SATURN_D2	(1<<2)
#define SATURN_D3	(1<<3)

#define MD_DB1		(1<<0)
#define MD_DB2		(1<<1)
#define MD_DB3		(1<<2)
#define MD_DB4		(1<<3)
#define MD_DB6		(1<<4)
#define MD_DB7		(1<<7)
#define MD_DB9		(1<<5)

#define PCE_SELECT 	(1<<1)
#define PCE_OE		(1<<0)
#define PCE_D0		(1<<5)
#define PCE_D1		(1<<2)
#define PCE_D2		(1<<4)
#define PCE_D3		(1<<3)

#define NES_LATCH	(1<<0)
#define NES_CLOCK	(1<<1)
#define NES_DATA	(1<<2)

#define PSX_CLK		(1<<3)
#define PSX_DATA	(1<<0)
#define PSX_ACK		(1<<4)
#define PSX_ATN		(1<<2)
#define PSX_CMD		(1<<1)

#define JAMMA_UP() 		(PORTD &= ~(1<<3))
#define JAMMA_DOWN()	(PORTD &= ~(1<<4))
#define JAMMA_LEFT()	(PORTD &= ~(1<<5))
#define JAMMA_RIGHT()	(PORTD &= ~(1<<6))
#define JAMMA_B1()		(PORTD &= ~(1<<7))
#define JAMMA_B2()		(PORTB &= ~(1<<0))
#define JAMMA_B3()		(PORTB &= ~(1<<1))
#define JAMMA_B4()		(PORTB &= ~(1<<2))
#define JAMMA_B5()		(PORTB &= ~(1<<3))
#define JAMMA_B6()		(PORTB &= ~(1<<4))
#define JAMMA_START()	(PORTB &= ~(1<<5))
#define JAMMA_COIN()	(PORTB &= ~(1<<6))

#define N_JAMMA_UP() 	(PORTD |= (1<<3))
#define N_JAMMA_DOWN()	(PORTD |= (1<<4))
#define N_JAMMA_LEFT()	(PORTD |= (1<<5))
#define N_JAMMA_RIGHT()	(PORTD |= (1<<6))
#define N_JAMMA_B1()	(PORTD |= (1<<7))
#define N_JAMMA_B2()	(PORTB |= (1<<0))
#define N_JAMMA_B3()	(PORTB |= (1<<1))
#define N_JAMMA_B4()	(PORTB |= (1<<2))
#define N_JAMMA_B5()	(PORTB |= (1<<3))
#define N_JAMMA_B6()	(PORTB |= (1<<4))
#define N_JAMMA_START()	(PORTB |= (1<<5))
#define N_JAMMA_COIN()	(PORTB |= (1<<6))


uint8_t initMegadrive(void);
void scanMegadrive(uint8_t);
uint8_t initSaturn(void);
void scanSaturn(uint8_t);
uint8_t initPSX(void);
void scanPSX(uint8_t);
void sendCmdPSX(uint8_t [] ,uint8_t);
uint8_t moveBytePSX(uint8_t);
uint8_t initSNES(void);
void scanSNES(uint8_t);
void initNES(void);
void scanNES(void);
void initPCE(void);
void scanPCE(void);
void initNeoGeo(void);
void scanNeoGeo(void);
void driveJamma(void);

#endif