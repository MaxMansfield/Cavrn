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

*/

/**
 * @file cavrn.h
 * @version 0.1.0 (Sedimentary Olm)
 * @author Max Mansfield
 * @copyright GNU Public License v2
 * @date February 19, 2015
 * @brief The main file which defines import macros and contains the Cavrn structure which is used for enabling and disabling
 * global functions in order to control global facilities which have no place in the other modules as well as unify files and 
 * apply various macros, Cavrn is provided. Use the Cavrn struct instead of calling its methods directly. Check the examples page 
 * for more detail
 *
 *@example Cavrn/setInterrupts Enable or Disable interrupts globally
 *@code
 *   Cavrn.setInterrupts(true);//globally set interrupts
 *   Cavrn.setInterrupts(OFF); //clear global interrupts 
 *@endcode
 */

#ifndef _CAVRN_H_
#define _CAVRN_H_


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <avr/io.h>
#include <avr/interrupt.h>

/**
 * @def ON
 * @brief  ON as 1 or true
 */
#define ON  0x01

/**
 * @def OFF
 * @brief OFF as 0 or false
 */
#define OFF 0x00

/**
 * @def HIGH
 * @brief HIGH as 255 or true
 */
#define HIGH 0xFF

/**
 * @def LOW
 * @brief LOW as 0 or false
 */
#define LOW  0x00

/**
 * @def IN
 * @brief IN as 0 or false
 */
#define IN  0x00

/**
 * @def OUT
 * @brief OUT as 1 or true
 */
#define OUT 0x01

/**
 * @def interruptsOn()
 * @brief A more readable function for setting global interupts
 */
#define interruptsOn()   sei()

/**
 * @def interruptsOff()
 * @brief A more readable function for clearing global interupts
 */
#define interruptsOff()  cli()

/**
 * @def isprint(c)
 * @brief Decides if a character is a printable or not. Very useful for transmitting strings. Taken from the C std library but I didn't want to include the entire file just for this function.
 */
#define isprint(c)  (c>=0x20 && c<=0x7E)

/*
 * I believe that since uint8_t is so commonly used with micro code there should be a more explicit solution which
 * helps describe the context which it's being used in. Thats why below you'll see typedefs for the same type but
 *  with different names for different contexts
 */

/**
 * @typedef word
 * @brief Use the word typedef when you mean to refer to 16 bit of information instead of something that would requitre an integer operation. 
 */
typedef uint16_t word;

/**
 * @typedef byte 
 * @brief Use a byte when you are representing raw 8 bit data like an SPI transfer, instead of integer operations like 
 * incrementing,adding,subtracting,switching on, etc...
 */
typedef uint8_t  byte;

/**
 * @typedef port
 * @brief Use a port to represent an 8 bit data input location, specifically a port on your AVR
 * @see pin
 */
typedef uint8_t  port;

/**
 * @typedef pin
 * @brief Use a pin to represent an 8 bit data output location, specifically a pin  on your AVR
 * @see port
 */
typedef uint8_t  pin;

/**
 * @typedef ddr
 * @brief Use to represent a data direction register on your AVR
 */
typedef uint8_t  ddr;


/**
 * !! SKIP THIS WHEN RUNNING DOXYGEN !!
 * @cond 0
 * @fn static inline void cavrn_set_global_interrupts(const bool isInterupts);
 * @brief: Set interrupts on/off. To be used via a function pointer in the Cavrn struct.
 *
 * Sets cavrn_t.interruptsEnabled on/off and then calls the right function to initialize interrupts.. 
 * @param: const bool isInterrupts
 *    This is the switch to detemine if interrupts will be used
 */
static inline void cavrn_set_global_interrupts(const bool isInterupts);
/**
 * @endcond
 */

/**
 * @typedef cavrn_t
 * @brief The global control structure. Use this as you would any other module. 
 *
 * It is important that you consistanly use these structures (intead of maybe calling
 * sei() yourself) so that operations are carried out successfully.
 *
 */
typedef struct  {
/**
 * @brief The static cavrn_t struct to execute functions with 
 * @addtogroup Cavrn
 * @{
 */
  
 /**
 * @fn void (*const setInterrupts)(const bool)
 * @brief: Enables or disables global interrupts on your AVR MCU
 *
 * Sets cavrn_t::interruptsEnabled on/off and then calls the right function to initialize interrupts..
 *
 * @param: const bool isInterrupts
 *    This is the switch to detemine if interrupts will be used
 */
  void (*const setInterrupts)(const bool);

/**
 * @var interruptsEnabled
 * @brief: Signifies that interrupts are enabled/disabled. For use by other modules as well as users.
 */
  bool interruptsEnabled;

/** @}*/

} cavrn_t ;

/**
 * @struct Cavrn
 * @brief The main entry point for global Cavrn functionality. Access cavrn_t Cavrn's functionality by addressing its function pointers. Check the Examples page for more.

 */
static  cavrn_t Cavrn = {
  .setInterrupts = &cavrn_set_global_interrupts,
  .interruptsEnabled = false
};

/**
 * !! Skip this when running doxygen
 * @cond 0
 */
static inline void cavrn_set_global_interrupts(const bool isInterrupts)
{
  if((Cavrn.interruptsEnabled = isInterrupts))
    interruptsOn();
  else
    interruptsOff();
  return;
}
/**
 *@endcond
 */

#endif 
