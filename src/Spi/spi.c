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
    
    ENABLE_MASTER();

    /* Only show if/else when SPI2X is present */
    
#if defined( __AVR_ATmega328P__) || defined(SPI2X)
    if(Spi.useSpi2x){
        switch(clk){
	case (F_OSC2):
	case (F_OSC8):
	case (F_OSC32):
	case (F_OSC64x):
	  SET_SPI2X();
	  CLR_SCK_REG();
	  SPCR |= clk;
	  break;
	default:
	  SET_SPI2X();       // Use SPI2X
	  CLR_SCK_REG();     // Clear both bits to 0
	  SPCR |= F_OSC8;   // Set SPR0 to 1
	  break;
	}
    }
    else
#endif
     {
       switch(clk){
       case (F_OSC4):
       case (F_OSC16):
       case (F_OSC64):
       case (F_OSC128):
	 CLR_SPI2X();
	 CLR_SCK_REG();
	 SPCR |= clk;
	 break;
       default:
	 CLR_SPI2X();   // Don't use spi2x
	 CLR_SCK_REG();
	 SPCR |= F_OSC16;
	 break;
     }
    }	
  } else {
    //Enter Slave mode
    // MOSI=in MISO=out SCK=in SS=in
    SPI_DDR |= (_BV(SPI_MISO));
    SPI_PORT |= (_BV(SPI_MISO));
    
    SPI_DDR &= ~(_BV(SPI_MOSI)  | _BV(SPI_SCK) | _BV(SPI_SCK) );
    SPI_PORT &= ~(_BV(SPI_MOSI)  | _BV(SPI_SCK) | _BV(SPI_SCK) );
    ENABLE_SLAVE();
  }

  switch(mode){
  case (SPI_MODE0):
    INIT_SPI_MODE0();
    break;
  case (SPI_MODE1):
    INIT_SPI_MODE1();
    break;
  case(SPI_MODE2):
    INIT_SPI_MODE2();
    break;
  case(SPI_MODE3):
    INIT_SPI_MODE3();
    break;
  default:
    INIT_SPI_MODE0();
    break;
  }
  return;
}

byte spi_transfer(const byte data)
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

void spi_set_data_order(const bool dord)
{
  if(dord)
    SPCR |= _BV(DORD);
  else
    SPCR &= ~_BV(DORD);

  return;
}

void spi_set_interrupts(const bool isInterrupt)
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
void spi_multi_transfer(const uint8_t* const dataout,uint8_t* const  datain,const uint8_t len)
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


