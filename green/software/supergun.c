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


#include "supergun.h"
#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>


int main(void)
{
	while(1)
	{

		DDRB = 0b00000000;
		DDRC = 0b11111111;
		DDRD = 0b11111111;
		PORTC = 0xFF;
		PORTB = 0xFF;
		PORTD = 0xFF;

		for(;;){
			// SELECT Low
			PORTD &= ~SEL1;
			PORTD &= ~SEL2;
			_delay_us(10);
			if (bit_is_clear(PINB,2)){
				P1_BUTTON1();
			}
			else {
				P1_N_BUTTON1();
			}
			if (bit_is_clear(PINB,3)){
				P1_START();
			}
			else {
				P1_N_START();
			}
			if (bit_is_clear(PINB,6)){
				P2_BUTTON1();
			}
			else {
				P2_N_BUTTON1();
			}
			if (bit_is_clear(PINB,7)){
				P2_START();
			}
			else {
				P2_N_START();
			}
			
			// SELECT High
			PORTD |= SEL1;
			PORTD |= SEL2;
			_delay_us(10);
			if (bit_is_clear(PINB,0)){
				P1_LEFT();
			}
			else {
				P1_N_LEFT();
			}
			if (bit_is_clear(PINB,1)){
				P1_RIGHT();
			}
			else {
				P1_N_RIGHT();
			}
			if (bit_is_clear(PINB,4)){
				P2_LEFT();
			}
			else {
				P2_N_LEFT();
			}
			if (bit_is_clear(PINB,5)){
				P2_RIGHT();
			}
			else {
				P2_N_RIGHT();
			}
			if (bit_is_clear(PINB,2)){
				P1_BUTTON2();
			}
			else {
				P1_N_BUTTON2();
			}
			if (bit_is_clear(PINB,3)){
				P1_BUTTON3();
			}
			else {
				P1_N_BUTTON3();
			}
			if (bit_is_clear(PINB,6)){
				P2_BUTTON2();
			}
			else {
				P2_N_BUTTON2();
			}
			if (bit_is_clear(PINB,7)){
				P2_BUTTON3();
			}
			else {
				P2_N_BUTTON3();
			}
			_delay_ms(10);
		}
	}
}

