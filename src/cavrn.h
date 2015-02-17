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
#include <stdbool.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#define ON  0x01
#define OFF 0x00

#define HIGH 0xFF
#define LOW  0x00

#define IN  0x00
#define OUT 0x01


#define interruptsOn()   sei()
#define interruptsOff()  cli()

#define  bit(b) (1<< (b))
#define  bitSet(value, bit) ((value) |=  (bit(bit))
#define  bitClear(value, bit) ((value) &= ~(bit(bit)))

#define isprint(c)  (c>=0x20 && c<=0x7E)

/*
 * I believe that since uint8_t is so commonly used with micro code there should be a more explicit solution which
 * helps describe the context which it's being used in. Thats why below you'll see typedefs for the same type but
 *  with different names for different contexts
 */

/* word 
 * It just makes since...I mean theres a double word but no word? No more! 
 */
typedef uint16_t word;

/* byte 
 * Use a byte when you are representing raw data like an SPI transfer, instead of integer operations like 
 * incrementing,adding,subtracting,switching on, etc...
 */
typedef uint8_t  byte;

/* Use as a port */
typedef uint8_t  port;
/*or a pin */
typedef uint8_t  pin;
/* or a  */
typedef uint8_t  ddr;


/**
 * @brief: cavrn_set_global_interrupts()
 *    This function enables or disables interrupts on your AVR MCU
 * @param: const bool isInterrupts
 *    This is the switch to detemine if interrupts will be used
 */
static inline void cavrn_set_global_interrupts(const bool isInterupts);
  
struct cavrn_t {
  void (*setInterrupts)(const bool);
  bool interruptsEnabled;
};

static struct cavrn_t Cavrn = {
  .setInterrupts = &cavrn_set_global_interrupts,
  .interruptsEnabled = false
};


static inline void cavrn_set_global_interrupts(const bool isInterrupts)
{
  if((Cavrn.interruptsEnabled = isInterrupts))
    sei();
  else
    cli();
  return;
}



#endif 
