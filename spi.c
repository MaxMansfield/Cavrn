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

#include "spi.h"

void spi_init(const bool isMaster,const byte mode,const uint8_t clk)
{

  SPI_DDR |= (_BV(SPI_SCK) | _BV(SPI_SS));
  SPI_PORT |= (_BV(SPI_SCK) | _BV(SPI_SS));
  SPCR |= _BV(SPE);
  if(isMaster){

    // MOSI=out MISO=in SCK=out SS=out
    SPI_DDR |= _BV(SPI_MOSI)  | _BV(SPI_SCK) | _BV(SPI_SCK);
    SPI_PORT |= _BV(SPI_MOSI)  | _BV(SPI_SCK) | _BV(SPI_SCK);
    
    SPI_DDR &= ~_BV(SPI_MISO);
    SPI_PORT &= ~_BV(SPI_MISO);
    //Set as Master
    SPCR |= (ENABLE_MASTER);

    // Choose clock speed
    
#if defined( __AVR_ATmega328P__)
    switch(clk){
    case (F_OSC2):
      SPCR |= _BV(SPI2X);
      SPCR &= ~(_BV(SPR1) | _BV(SPR0));
      break;
    case (F_OSC4):
      SPCR &= ~(_BV(SPR1) | _BV(SPR0) | _BV(SPI2X));
      break;
    case (F_OSC8):
      SPCR |= (_BV(SPI2X) | _BV(SPR0));
      SPCR &= ~_BV(SPR1);
      break;
    case (F_OSC16):
      SPCR |= _BV(SPR0);
      SPCR &= ~(_BV(SPR1) |  _BV(SPI2X));
      break;
    case (F_OSC32):
      SPCR |= (_BV(SPI2X) | _BV(SPR1));
      SPCR &= ~_BV(SPR0);
      break;
    case (F_OSC64):
      SPCR |= (_BV(SPR1) | _BV(SPR0) | _BV(SPI2X));
      break;
    case (F_OSC128):
      SPCR |= (_BV(SPR0) | _BV(SPR1));
      SPCR &= ~_BV(SPI2X);
      break;
    default:
      SPCR |= _BV(SPR0);
      SPCR &= ~(_BV(SPR1) |  _BV(SPI2X));
      break;
    }
#elif defined(__AVR_ATmega103__)
    switch(clk){
    case (F_OSC4):
      SPCR &= ~(_BV(SPR1) | _BV(SPR0));
      break;
    case (F_OSC16):
      SPCR |= _BV(SPR0);
      SPCR &= ~(_BV(SPR1));
      break;
    case (F_OSC64):
      SPCR |= (_BV(SPR1) | _BV(SPR0));
      break;
    case (F_OSC128):
      SPCR |= (_BV(SPR0) | _BV(SPR1));
      break;
    default:
      SPCR |= _BV(SPR0);
      SPCR &= ~(_BV(SPR1));
      break;
    }
#endif	
  } else {
    //Enter Slave mode
    // MOSI=in MISO=out SCK=in SS=in
    SPI_DDR |= (_BV(SPI_MISO));
    SPI_PORT |= (_BV(SPI_MISO));
    
    SPI_DDR &= ~(_BV(SPI_MOSI)  | _BV(SPI_SCK) | _BV(SPI_SCK) );
    SPI_PORT &= ~(_BV(SPI_MOSI)  | _BV(SPI_SCK) | _BV(SPI_SCK) );
    SPCR |= (ENABLE_SLAVE);
  }

  switch(mode){
  case (SPI_MODE0):
    SPCR &= ~_BV(CPOL);
    SPCR &= ~_BV(CPHA);
    break;
  case (SPI_MODE1):
    SPCR &= ~_BV(CPOL);
    SPCR |= _BV(CPHA);
    break;
  case(SPI_MODE2):
    SPCR |= _BV(CPOL);
    SPCR &= ~_BV(CPHA);
    break;
  case(SPI_MODE3):
    SPCR |= _BV(CPOL) | _BV(CPHA);
    break;
  default:
    SPCR &= ~_BV(CPOL);
    SPCR &= ~_BV(CPHA);
    break;
  }
    

  return;
}

uint8_t spi_transfer(uint8_t data)
{ 
  SPDR = data; 
  loop_until_bit_is_set(SPSR,SPIF);
  return (SPDR);
}

void spi_disable()
{
  SPCR = 0;
  return;
}

void spi_setDataOrder(const bool dord)
{

  if(dord)
    SPCR |= _BV(DORD);
  else
    SPCR &= ~_BV(DORD);

  return;
}

void spi_setInterrupts(bool const isInterrupt)
{
  if(isInterrupt){
    SPCR |= _BV(SPIE);
  } else {
    SPCR &= ~_BV(SPIE);
  }
  Spi.interruptsEnabled = isInterrupt;  
  return;
}
/* send and receive multiple bytes over SPI */
void spi_multiTransfer(const uint8_t* const dataout,uint8_t* const  datain,const uint8_t len)
{
  //Disable interrupts during transfer
    uint8_t i;

    if(dataout){    
      /* Disable interrupts if need be */
      byte sreg = SREG;
      bool intr;
      if((intr = Spi.interruptsEnabled))
	Spi.setInterrupts(OFF);
    
      for(i=0;i<len;i++)
	{
	  if(datain)
	    datain[i] = spi_transfer(dataout[i]);
	  else
	    spi_transfer(dataout[i]);
	}

      SREG = sreg;

      //Enable interrupts if they were disabled
      if(intr)
	Spi.setInterrupts(ON);
    }

   
    return;
}


