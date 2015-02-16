/*
  This is an attempt to rewrite the arduino libraries in pure C.
  Initially this will only suport the Arduino Uno i.e. atmega328p
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
