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

#define SPI_MODE0 0x00
#define SPI_MODE1 0x04
#define SPI_MODE2 0x08
#define SPI_MODE3 0x0A

#define MASTER 0xFA
#define SLAVE  0x00

#define MSB_ORDER 0x00
#define LSB_ORDER 0x01

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


//SPE =  Enable
//MSTR = is Master
#define ENABLE_MASTER (_BV(SPE) | _BV(MSTR))
#define ENABLE_SLAVE  (_BV(SPE) & ~_BV(MSTR))

#else
#error This MCU does not support SPI from Cavrn. Add proper defines to continue.
#endif

// Clock Speed options
#define F_OSC2   0x02
#define F_OSC4   0x04
#define F_OSC8   0x08
#define F_OSC16  0x16
#define F_OSC32  0x32
#define F_OSC64  0x64
#define F_OSC128 0xFF


void spi_init(const bool isMaster,const byte mode,const uint8_t clk);
void spi_multiTransfer(const uint8_t* const dataout,uint8_t* const  datain,const uint8_t len);
uint8_t spi_transfer(uint8_t data);
void spi_setDataOrder(bool const dord);
void spi_setInterrupts(bool const isInterrupt);
void spi_disable();

struct spi_t {
  void    (*init) (const bool,const byte,const uint8_t); 
  uint8_t (*transfer) (uint8_t const);  
  void    (*multiTransfer)(const uint8_t* const,uint8_t* const,const uint8_t);
  void    (*setDataOrder)(bool const);
  void    (*setInterrupts)(bool const isInterrupt);
  void    (*disable)();

  bool interruptsEnabled;
};

static struct spi_t Spi = {
  .init = &spi_init,
  .transfer = &spi_transfer,
  .multiTransfer = &spi_multiTransfer,
  .setDataOrder = &spi_setDataOrder,
  .setInterrupts = &spi_setInterrupts,
  .disable = &spi_disable,
  .interruptsEnabled = false
};

#endif 
