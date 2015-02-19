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
/**
 *
 * @file uart.h
 * @version 0.1.0 (Sedimentary Olm)
 * @author Max Mansfield
 * @copyright GNU Public License v2
 * @date February 19, 2015
 * @brief Uart uses a variety of internal functions and presents them in the form of a uart_t object called Uart.
 * To access a function and its operations, simply address the function pointer. Check the examples for more.
 * @example Uart/PrintableTx Quickly use Uart.txString(const char*) to only send and recieve printable strings
 * @code
 *   Uart.init(ASYNC_MODE); 
 *   Uart.printableCharsOnly = true;
 *
 *   while(1) 
 *    Uart.txString("Hello World\n\r");
 *   
 *@endcode
 */
#ifndef _UART_H_
#define _UART_H_
#include "cavrn.h"
#include <util/setbaud.h>

#define RXLEN 254

#if defined(__AVR_ATmega328P__)

/**
 * @def UBRRH
 * @brief  Universalize the Uart Baud Rate Register High
 */
#define UBRRH UBRR0H

/**
 * @def UBRRL
 * @brief  Universalize the Uart Baud Rate Register Low
 */
#define UBRRL UBRR0L

/**
 * @def UCSRA
 * @brief  Universalize the Uart Control Status Register A
 */
#define UCSRA UCSR0A

/**
 * @def UCSRB
 * @brief  Universalize the Uart Control Status Register B
 */
#define UCSRB UCSR0B

/**
 * @def UCSRC
 * @brief  Universalize the Uart Control Status Register C
 */
#define UCSRC UCSR0C

/**
 * @def UDR
 * @brief  Universalize the Uart Data Register
 */
#define UDR   UDR0

/**
 * @def UDRE
 * @brief  Universalize the Uart Data Register Empty Flag
 */
#define UDRE UDRE0

/**
 * @def UCSZ0
 * @brief  Universalize the Uart Control Status Register Z 0
 */
#define UCSZ0 UCSZ00

/**
 * @def UCSZ1
 * @brief  Universalize the Uart Control Status Register Z 1
 */
#define UCSZ1 UCSZ01

/**
 * @def RXC
 * @brief  Universalize the Recieve Control Flag
 */
#define RXC   RXC0

/**
 * @def U2X
 * @brief  Universalize the Use 2 times Flag
 */
#define U2X   U2X0

/**
 * @def TXEN
 * @brief  Universalize the transmit enable flag
 */
#define TXEN  TXEN0

/**
 * @def RXEN
 * @brief  Universalize the recieve enable flag
 */
#define RXEN  RXEN0

/**
 * @def RXIE
 * @brief  Universalize RXC interrupt enable flag
 */
#define RXCIE RXCIE0

/**
 * @def TXIE
 * @brief  Universalize TXC interrupt enable flag
 */
#define TXCIE TXCIE0

/**
 * @def RXIE
 * @brief  Universalize UDRE interrupt enable flag
 */
#define UDRIE UDRIE0

/**
 * @def UART_ASYNC()
 * @brief  Initialize UMSEL01 and UMSEL00 for Aysyncrounous (full duplex) UART communication
 */
#define UART_ASYNC() UCSRC &= ~((1<<UMSEL01) | (1<<UMSEL00))

/**
 * @def UART_ASYNC()
 * @brief  Initialize UMSEL01 and UMSEL00 for Syncrounous (half duplex) UART communication
 */
#define UART_SYNC() UCSRC &= ~(1<<UMSEL01); UCSRC |= (1<<UMSEL00)

/**
 * @def UART_MSPI()
 * @brief  Initialize UMSEL01 and UMSEL00 for emulated SPI communication over UART.
 * @see
 */
#define UART_MSPI() UCSRC |= ((1<<UMSEL01) | (1<<UMSEL00))

/**
 * @def ASYNC_MODE
 * @brief Used as an argument for Uart.init()  start Asynchronous mode
 * @see void init(const byte)
 * @see SYNC_MODE
 * @see MSPI_MODE
 */
#define ASYNC_MODE ((byte) 0x02)

/**
 * @def SYNC_MODE
 * @brief Used as an argument for Uart.init() to start Synchronous mode
 * @see void init(const byte)
 * @see ASYNC_MODE
 * @see MSPI_MODE
 */
#define SYNC_MODE  ((byte) 0x04)

/**
 * @def MSPI_MODE
 * @brief Used as an argument for Uart.init() to start emulated SPI  mode
 * @see void init(const byte)
 * @see SYNC_MODE
 * @see MSPI_MODE
 */
#define MSPI_MODE  ((byte) 0x08)

#elif defined(__AVR_ATmega103__)
#define UCSRA USR
#define UCSRB UCR

#else
#error Unsupported MCU
#endif // Atmega328p

/**
 * @def UART_START()
 * @brief  Set UCSRB with the TX and RX enable flags
 */
#define UART_START()  UCSRB |= (1<<TXEN) | (1<<RXEN)



/**
 * !! Skip this When Documenting via the cond and endcond !!
 * @cond 0 
 * @brief These functions have another point of entry and should not be called directly. In fact, there is no Cavrn function that should not be called through a struct.
 * @code
 *    Uart.init(ASYNC_MODE);
 * @endcode
*/
#if defined(__AVR_ATmega328P__)
static void  uart_init(const byte mode);
#elif defined(__AVR_ATmega103__)
static void  uart_init();
#endif

static void  uart_tx(const byte data);
static byte  uart_rx();

static void  uart_txstr(const char* const string);
static void uart_rxstr(char* const string, const uint8_t len);

static byte  uart_transfer(const byte data);
static void uart_multi_transfer(const byte* const data,byte* datain,const uint8_t* const len);

static void uart_set_tx_interrupt(const bool isInterrupt);
static void uart_set_rx_interrupt(const bool isInterrupt);
static void uart_set_udre_interrupt(const bool isInterrupt);
static void uart_set_interrupts(const bool isInterrupt);

/**
 * 
 * @fn  static void uart_txchr (const char  chr)
 * @brief Transmits a character of information (signed 8bit integer) via UART  
 * @param  const char* const data
 *    The data to be transmited
 * @return void
 */
static void uart_txchr (const char  chr);

/**
 * @fn uart_rxchr()
 * @brief Recieves a character of information (signed 8 bit integer) via UART  
 * @return char
 */
static char uart_rxchr();
/**
@endcond 
*/



/**
 * @typedef uart_t
 * @brief A struct meant to control UART capabilities with such as interrupts and transfers. 
 * Use the provided Uart struct to perform any operations.
 */
typedef struct  {
 /**
     @brief The access point for Uart capabilities.
     @addtogroup Uart 
  @{
*/
#if defined(__AVR_ATmega328P__)
/**
 * @fn void init(const byte)
 * @brief Initializes the UART system and uses a mode to do so
 *
 * This will set the Baud rate registers with precompiled values then on some MCUs
 * it will decide to use 2x speeds. Then it decides which mode and clock divisor to 
 * use before setting the frame size to 8-N-1
 *
 * @param const byte mode
 *    The mode which to use UART in there are 3 distinct modes
 *    
 *   -# ASYNC_MODE - Asyncronous Full duplex communication
 *   -# SYNC_MODE  - Syncronous Half duplex communication
 *   -# MSPI_MODE  - Emulated SPI mode - (not implemented)
 * @return void
 */
   void     (*const init)    (const byte); 
#elif defined(__AVR_ATmega103__)
/**
 * @fn void init()
 * @brief Initializes the UART system which only has one mode to its default.
 */
  void     (*const init)    (); 
#endif

/**
 * @fn void (*const txByte)(const byte)
 * @brief Transmits a byte of information (unsigned 8 bit integer) via UART  
 * @param  const byte const data
 *    The data to be transmited
 * @return void
 */
  void ( *const txByte)  (const byte);

/**
 * @fn byte (*const rxByte)()
 * @brief Recieves a byte of information (unsigned 8bit integer) via UART  
 * @return byte
 */
  byte  (*const rxByte)  ();

  /**
 * @fn void (*const txString)(const char* const)
 * @brief Transmit large amounts of signed 8bit integers, useful for logging to UART  
 * @param const char* const string
 *    The string to be transmitted
 * @return void
 */
  void         (*const txString)(const char* const);

  
/**
 * @brief (*const rxString)(char* const, const uint8_t)
 *    Recieve large amounts of signed 8bit integers, useful for commands via UART  
 * @return void
 *
 */
  void  (*const rxString)(char* const, const uint8_t);

/**
 * @fn void (*const setInterrupts)(const bool)
 * @brief: Enable or diable the all the Uart interrupts simultaneously.
 * @param: const bool isInterrupts
 *    The switch to turn interrupts on and off
 */
  void (*const setInterrupts)(const bool);
  
/**
 * @fn void (*const setTxInterrupt) (const bool)
 * @brief Enable UART data register empty interrupts and global interrupts if need be 
 * @param const bool isInterrupts
 *    The switch to turn interrupts on and off
 * @return void
 */
  void (*const setTxInterrupt)(const bool);

/**
 * @fn void (*const setRxInterrupt)(const bool)
 * @brief Enable UART byte recieved interrupts and global interrupts if need be 
 * @param const bool isInterrupts
 *    The switch to turn interrupts on and off
 * @return void
 */
  void (*const setRxInterrupt)(const bool);

/**
 * @fn void (*const setUdreInterrupt)(const bool)
 * @brief Enable or diable the Uart Data Register Empty flag
 * @param const bool isInterrupts
 *    The switch to turn interrupts on and off
 */
  void (*const setUdreInterrupt)(const bool);

  
/**
 * @fn byte (*const transfer)(const byte)
 * @brief Transmit a byte and wait for a response. Unessecary when interrupts are enabled  
 * @see  void multiTransfer(const byte* const,byte*,const uint8_t* const)
 * @param const byte* const data
 *    The byte to transmit
 * @return byte
 *
 */
  byte (*const transfer)(const byte);

 /**
 * @fn void (*const multiTransfer)(const byte* const,byte*,const uint8_t* const)
 * @brief Transmit large amounts of data by repeadtedly calling Uart.transfer(const byte) and wait for a response. Unessecary when interrupts are enabled.
 * @see byte transfer(const byte)
 * @param const byte* const data
 *    The data to transmit
 * @return void
 *
 */
  void (*const multiTransfer)(const byte* const,byte* const,const uint8_t* const );

  /**
   * @var bool printableCharsOnly
   * @brief When set UART will only transmit and recieve characters the can be printed
   */
  bool printableCharsOnly;
  
/**
@}
*/
} uart_t;

/**
 * @struct Uart
 * @brief The way to control any Uart functions is through this struct.
 * 
 * Use Uart like an object when performing operations
 */
static uart_t Uart = {
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
  
  .printableCharsOnly = false
};



#endif
