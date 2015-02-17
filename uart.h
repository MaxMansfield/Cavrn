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
void  uart_init(const byte mode);
#elif defined(__AVR_ATmega103__)
void  uart_init();
#endif

/* Send Bytes of signed/unsigned information */
void  uart_tx(const byte* const data);
void uart_txchr (const char* const chr);

/* Recieve bytes of signed/unsigned information */
uint8_t  uart_rx();
char uart_rxchr();

/* Send and Recieve entire strings of information */
void  uart_txstr(const char* const string);
const char* uart_rxstr();


struct uart_t  {

  /* Choose init function */
#if defined(__AVR_ATmega328P__)
  void     (*init)    (const byte mode); 
#elif defined(__AVR_ATmega103__)
  void     (*init)    (); 
#endif

  /* Send/Recieve a byte bia UART */
  void     (*txByte)  (const byte* const); 
  uint8_t  (*rxByte)  ();

  /*Send/Recieve a string via UART */
  void         (*txString)(const char* const string); 
  const char*  (*rxString)(); 
};

/* Main Uart Structure */
static const struct uart_t Uart = {
  .init = &uart_init,
  .txByte = &uart_tx,
  .rxByte = &uart_rx,
  .txString = &uart_txstr,
  .rxString = &uart_rxstr
};

#endif
