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
 
#ifndef SUPERGUN
#define SUPERGUN

#include <math.h>
#include <stdio.h>
#include <stdint.h>
#include <avr/io.h>

#define SEL1 (1<<0)
#define SEL2 (1<<1)
#define P1_LEFT() (PORTD &= ~(1<<3))
#define P1_RIGHT() (PORTD &= ~(1<<4))
#define P1_BUTTON1() (PORTD &= ~(1<<5))
#define P1_BUTTON2() (PORTD &= ~(1<<6))
#define P1_BUTTON3() (PORTD &= ~(1<<7))
#define P1_START() (PORTD &= ~(1<<2))

#define P2_LEFT() (PORTC &= ~(1<<1))
#define P2_RIGHT() (PORTC &= ~(1<<2))
#define P2_BUTTON1() (PORTC &= ~(1<<3))
#define P2_BUTTON2() (PORTC &= ~(1<<4))
#define P2_BUTTON3() (PORTC &= ~(1<<5))
#define P2_START() (PORTC &= ~(1<<0))


#define P1_N_LEFT()		(PORTD |= (1<<3))
#define P1_N_RIGHT()	(PORTD |= (1<<4))
#define P1_N_BUTTON1()	(PORTD |= (1<<5))
#define P1_N_BUTTON2()	(PORTD |= (1<<6))
#define P1_N_BUTTON3()	(PORTD |= (1<<7))
#define P1_N_START()	(PORTD |= (1<<2))

#define P2_N_LEFT()		(PORTC |= (1<<1))
#define P2_N_RIGHT()	(PORTC |= (1<<2))
#define P2_N_BUTTON1()	(PORTC |= (1<<3))
#define P2_N_BUTTON2()	(PORTC |= (1<<4))
#define P2_N_BUTTON3()	(PORTC |= (1<<5))
#define P2_N_START()	(PORTC |= (1<<0))


#endif