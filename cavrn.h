/*
Cavrn is an easy to use library for AVR microcontrollers designed to have enough flexibility for professional use.

Copyright (C) 2015  Max Mansfield

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

Author: Max Mansfield <Max.M.Mansfield@gmail.com>
Contributors: 

*/
#ifndef _CAVRN_H_
#define _CAVRN_H_
//Define DEBUG_MODE as 1 to use debugging features

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#define ON  0x01
#define OFF 0x00

#define IN  0x00
#define OUT 0x01

#define true  0x01
#define false 0x00

#define interruptsOn()   sei()
#define interruptsOff()  cli()


#define  bit(b) (1UL << (b))
#define  bitSet(value, bit) ((value) |=  (bit(bit))
#define  bitClear(value, bit) ((value) &= ~(bit(bit)))


typedef uint16_t word;
typedef uint8_t  byte;
typedef uint8_t  bool;

#endif 
