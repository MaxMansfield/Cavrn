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
#ifndef _SPI_H_
#define _SPI_H_
#include "cavrn.h"


/* Clear the SCK data speed bits on SPCR */
#define CLR_SCK_REG() SPCR &= ~(_BV(SPR1) | _BV(SPR0))

/* SPI_MODEn
 * The bit mask of the CPOL and CPHA bits which can be directly used
 * to set SPCR
 */
#define SPI_MODE0 0xf3 // CPOL = 0; CPHA = 0; (use AND not OR)
#define SPI_MODE1 0x04 // CPOL = 0; CPHA = 1;
#define SPI_MODE2 0x08 // CPOL = 1; CPHA = 0;
#define SPI_MODE3 0x0C // CPOL = 1; CPHA = 1;

/* SCK rate control.
 * This also directly effects the Oscillator Clock frequency, so it is refered to as F_OSC.
 * Each clock value is the bitmask of what needs to be put into the SPCR. SPI2X F_OSC speeds 
 * are defined as necessary below.
 */
#define F_OSC4   0x00
#define F_OSC16  (_BV(SPR0))
#define F_OSC64  (_BV(SPR1))
#define F_OSC128 (_BV(SPR1) | _BV(SPR0))


/* SPI2X 
 * Check for the SPI2X register. If available then define the speeds (F_OSC64 is only defined once)
 * If it's not available then define the functions as nothing so that the finished program has just
 * a semicolon which is the nop instruction in C.
 */
#ifdef SPI2X
#define F_OSC2 0x00                         // Will not change the bits, bit will already be clear
#define F_OSC8   (_BV(SPR0))                // Set only one bit
#define F_OSC32  (_BV(SPR1))                // Set only one bit
#define F_OSC64x (_BV(SPR1) | _BV(SPR0))    // Set both bits

#define SET_SPI2X() SPSR |= _BV(SPI2X)
#define CLR_SPI2X()  SPSR &= ~_BV(SPI2X)

#else
#define SET_SPI2X()  
#define CLR_SPI2X() 
#endif //SPI2X

#define INIT_SPI_MODE0() SPCR &= SPI_MODE0
#define INIT_SPI_MODE1() SPCR |= SPI_MODE1
#define INIT_SPI_MODE2() SPCR |= SPI_MODE2
#define INIT_SPI_MODE3() SPCR |= SPI_MODE3

#define MASTER 0x01
#define SLAVE  0x00

#define MSB_ORDER 0x01
#define LSB_ORDER 0x00

/*
  Define SPI pins per MCU
*/
#if defined(__AVR_ATmega328P__) || defined (__AVR_ATmega103__)

#define SPI_DDR  DDRB
#define SPI_PORT PORTB
#define SPI_PIN  PINB

#ifdef __AVR_ATmega328P__
#define SPI_SS   PB2
#define SPI_MOSI PB3
#define SPI_MISO PB4
#define SPI_SCK  PB5
#elif defined(__AVR_ATmega103__)
#define SPI_SS   PB0
#define SPI_SCK  PB1
#define SPI_MOSI PB2
#define SPI_MISO PB3
#endif //ATmega328P

#define ENABLE_MASTER() SPCR |= (_BV(SPE) | _BV(MSTR))
#define ENABLE_SLAVE()  SPCR |= _BV(SPE); SPCR &= ~(_BV(MSTR))

#else
#error This MCU does not support SPI from Cavrn. Add proper defines to continue.
#endif // defined(__AVR_ATmega328P__) || defined (__AVR_ATmega103__)

/**
 * @brief: spi_init()
 *    This method initializes the registers of the MCU and determines the clock polarity and clock rate for the transfers
 * @param: const bool isMaster
 *    This uint8_t is used to determine whether or not a Master or Slave init process should be used. Many different identifiers 
 *    can be used like MASTER,SLAVE,true,false,ON,OFF,HIGH,LOW...all of which are defined by Cavrn
 * @param: const byte mode
 *    The mode is the clock polarity setting (SPI_MODE0 through SPI_MODE3). Read Atmel documentation if you are confused about this.
 * @param: const uint8_t clk
 *    This is the speed of the SCK clock F_OSC. Use F_OSCn with n being the speed you want to use this functions
 */
void spi_init(const bool isMaster,const byte mode,const uint8_t clk);

/**
 * @brief: spi_multiTransfer()
 *    This function stops interrupts if they are enabled during transfer and utilizes spi_transfer(byte) until all information has been sent and recieved
 * @param: const byte* const dataout
 *    A pointer to the data to be sent via SPI.
 * @param: byte* const datain
 *    A pointer to the data to be recieved via SPI. Can be NULL to only send data.
 * @param: const uint8_t len
 *    They amount of bytes to trancieve
 */
void spi_multi_transfer(const byte* const dataout,byte* const  datain,const uint8_t len);

/**
 * @brief: spi_transfer()
 *    This function will send a byte and wait for a response via spi before returning its value.
 * @param: const byte* const data
 *    The data to transmit via SPI.
 * @return: the byte contained at the SPI Data Register after recieving a response
 */
byte spi_transfer(const byte data);


/**
 * @brief: spi_set_data_order()
 *    This funtion changes the data order from MSB (whichis equivelent to true) to LSB (false) and backagain
 * @param: bool const dord
 *    The data order to use. Can be MSB_ORDER,LSB_ORDER,true,false,ON,OFF,HIGH,LOW,IN,OUT,1,0
 */
void spi_set_data_order(const bool dord);

/**
 * @brief: spi_set_interrupts()
 *    This funtion changes the data order from MSB (whichis equivelent to true) to LSB (false) and backagain
 * @param: bool const isInterrupt
 *    Enable spi interrupts (or disble) and signale to the Spi.interrputsEnabled variable
 */
void spi_set_interrupts(const bool isInterrupt);

/**
 * @brief: spi_disable()
 *    Opposite of init. Disable SPI.
 */
void spi_disable();


/* Create a nice home for all these functions */
struct spi_t {
  void    (*init) (const bool,const byte,const uint8_t); 
  byte    (*transfer) (const byte);  
  void    (*multiTransfer)(const uint8_t* const,uint8_t* const,const uint8_t);
  void    (*setDataOrder)(const bool);
  void    (*setInterrupts)(const bool);
  void    (*disable)();

  bool interruptsEnabled;

#ifdef SPI2X
  bool useSpi2x;
#endif
};

/* Main SPI Struct */
static struct spi_t Spi = {
  .init = &spi_init,
  .transfer = &spi_transfer,
  .multiTransfer = &spi_multi_transfer,
  .setDataOrder = &spi_set_data_order,
  .setInterrupts = &spi_set_interrupts,
  .disable = &spi_disable,
  .interruptsEnabled = false,
#ifdef SPI2X
  .useSpi2x = false
#endif
};

#endif 

