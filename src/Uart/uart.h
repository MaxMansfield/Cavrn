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

#ifndef _UART_H_
#define _UART_H_
#include "cavrn.h"
#include <util/setbaud.h>

#define RXLEN 254

#if defined(__AVR_ATmega328P__)

#define UBRRH UBRR0H
#define UBRRL UBRR0L

#define UCSRA UCSR0A
#define UCSRB UCSR0B
#define UCSRC UCSR0C
#define UDR   UDR0
#define UDRE UDRE0

#define UCSZ0 UCSZ00
#define UCSZ1 UCSZ01

#define RXC   RXC0
#define U2X   U2X0

#define TXEN  TXEN0
#define RXEN  RXEN0

#define RXCIE RXCIE0
#define TXCIE TXCIE0
#define UDRIE UDRIE0

/* Uart Data Modes */
#define UART_ASYNC() UCSRC &= ~((1<<UMSEL01) | (1<<UMSEL00))
#define UART_SYNC() UCSRC &= ~(1<<UMSEL01); UCSRC |= (1<<UMSEL00)
#define UART_MSPI() UCSRC |= ((1<<UMSEL01) | (1<<UMSEL00))

/* Data Mode Identifiers */
#define ASYNC_MODE ((byte) 0x02)
#define SYNC_MODE  ((byte) 0x04)
#define MSPI_MODE  ((byte) 0x08)

#elif defined(__AVR_ATmega103__)
#define UCSRA USR
#define UCSRB UCR

#else
#error Unsupported MCU
#endif

#define UART_START()  UCSRB |= (1<<TXEN) | (1<<RXEN)

/*
 * Intialize UART 
 * Uart initialization can be different for various MCUs because some have available status registers
 * to mainipulate and some don't.
*/
#if defined(__AVR_ATmega328P__)


/**
 * @brief: uart_init()
 *    This function initializes the UART system and uses a mode to do so
 * @param: const byte mode
 *    The mode which to use UART in there are 3 distinct modes
 *    
 *    ASYNC_MODE - Asyncronous Full duplex communication
 *    SYNC_MODE  - Syncronous Half duplex communication
 *    MSPI_MODE  - Emulated SPI mode - (not implemented)
 */
void  uart_init(const byte mode);
#elif defined(__AVR_ATmega103__)

/**
 * @brief: uart_init()
 *    This function initializes the UART system which only has one mode to its default.
 */
void  uart_init();
#endif

/**
 * @brief: uart_tx()
 *    This function transmits a byte of information (unsigned 8bit integer) via UART  
 * @param:  const byte* const data
 *    A pointer to the data to be transmited
 */
void  uart_tx(const byte* const data);


/**
 * @brief: uart_txchr()
 *    This function transmits a character of information (signed 8bit integer) via UART  
 * @param:  const char* const data
 *    A pointer to the data to be transmited
 */
void uart_txchr (const char* const chr);

/**
 * @brief: uart_rx()
 *    This function recieves a byte of information (unsigned 8bit integer) via UART  
 * @return: The byte value recieved in the UDR register
 */
byte  uart_rx();

/**
 * @brief: uart_rxchr()
 *    This function transmits a character of information (signed 8bit integer) via UART  
 * @return: The byte data stored in the UDR register as a signed byte
 */
char uart_rxchr();

/**
 * @brief: uart_txstr()
 *    Transmit large amounts of signed 8bit integers, useful for logging to UART  
 * @param: const char* const string
 *    The string to be transmitted
 */
void  uart_txstr(const char* const string);

/**
 * @brief: uart_rxstr()
 *    Recieve large amounts of signed 8bit integers, useful for commands via UART  
 * @return: The bytes recieved until a \0,\n,\r or NULL character is reached or the rx buffer fills
 *
 */
void uart_rxstr(char* const string, const uint8_t len);


/**
 * @brief: uart_transfer()
 *    Transmit a byte and wait for a response. Unessecary when interrupts are enabled  
 * @param const byte* const data
 *    The byte to transmit
 * @return: The bytes recieved after transmission
 *
 */
byte  uart_transfer(const byte* const data);


/**
 * @brief: uart_multi_transfer()
 *    Transmit large amounts of data and wait for a response. Unessecary when interrupts are enabled.
 * @param const byte* const data
 *    The data to transmit
 * @return: The data recieved after transmission
 *
 */
void uart_multi_transfer(const byte* const data,byte* datain,const uint8_t* const len);


/**
 * @brief: uart_set_tx_interrupt()
 *    Enable UART data register empty interrupts and global interrupts if need be 
 * @param: const bool isInterrupts
 *    The switch to turn interrupts on and off
 */
void uart_set_tx_interrupt(const bool isInterrupt);


/**
 * @brief: uart_set_rx_interrupt()
 *    Enable UART byte recieved interrupts and global interrupts if need be 
 * @param: const bool isInterrupts
 *    The switch to turn interrupts on and off
 */
void uart_set_rx_interrupt(const bool isInterrupt);

/**
 * @brief: uart_set_udre_interrupt()
 *    Enable or diable the Uart Data Register Empty flag
 * @param: const bool isInterrupts
 *    The switch to turn interrupts on and off
 */
void uart_set_udre_interrupt(const bool isInterrupt);

/**
 * @brief: uart_set_interrupts()
 *    Enable or diable the all the Uart interrupts simultaneously.
 * @param: const bool isInterrupts
 *    The switch to turn interrupts on and off
 */
void uart_set_interrupts(const bool isInterrupt);
  
struct uart_t  {

  /* Choose init function */
#if defined(__AVR_ATmega328P__)
  void     (*init)    (const byte); 
#elif defined(__AVR_ATmega103__)
  void     (*init)    (); 
#endif

  /* Send/Recieve a byte bia UART */
  void     (*txByte)  (const byte* const); 
  uint8_t  (*rxByte)  ();

  /*Send/Recieve a string via UART */
  void         (*txString)(const char* const); 
  void  (*rxString)(char* const, const uint8_t);

  /* Enable/Disable interrupts */
  void (*setInterrupts)(const bool);
  void (*setTxInterrupt)(const bool);
  void (*setRxInterrupt)(const bool);
  void (*setUdreInterrupt)(const bool);

  byte (*transfer)(const byte* const);
  void (*multiTransfer)(const byte* const,byte* const,const uint8_t* const );

  /* When using txString, only send printable characters */
  bool printableCharsOnly;
};

/* Main Uart Structure */
static const struct uart_t Uart = {
  .init = &uart_init,
  
  .txByte = &uart_tx,
  .rxByte = &uart_rx,
  
  .txString = &uart_txstr,
  .rxString = &uart_rxstr,

  .transfer = &uart_transfer,
  .multiTransfer = &uart_multi_transfer,
  
  .setInterrupts = &uart_set_interrupts,
  .setUdreInterrupt = &uart_set_udre_interrupt,
  .setTxInterrupt = &uart_set_tx_interrupt,
  .setRxInterrupt = &uart_set_rx_interrupt,
  
  .printableCharsOnly = true
};

#endif
