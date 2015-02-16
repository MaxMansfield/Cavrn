#ifndef _UART_H_
#define _UART_H_
#include "cavrn.h"
#include <util/setbaud.h>

#define RXLEN 254
#define ASYNC_MODE ((byte) 0x02)
#define SYNC_MODE  ((byte) 0x04)
#define MSPI_MODE  ((byte) 0x08)

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

#define UART_ASYNC() UCSRC &= ~((1<<UMSEL01) | (1<<UMSEL00))
#define UART_SYNC() UCSRC &= ~(1<<UMSEL01); UCSRC |= (1<<UMSEL00)
#define UART_MSPI() UCSRC |= ((1<<UMSEL01) | (1<<UMSEL00))


#elif defined(__AVR_ATmega103__)
#define UCSRA USR
#define UCSRB UCR

#else
#error Unsupported MCU
#endif

#define UART_START()  UCSRB |= (1<<TXEN) | (1<<RXEN)

/* Intialize UART */
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
#if defined(__AVR_ATmega328P__)
  void     (*init)    (const byte mode); //Initialize UART w/ mode choice
#elif defined(__AVR_ATmega103__)
  void     (*init)    (); //Initialize UART without mode choice
#endif
  void           (*txByte)  (const byte* const); // Send a byte
  uint8_t  (*rxByte)  (); // get a byte
  void         (*txString)(const char* const string); // Send a string 
  const char*  (*rxString)();  // get a string
};

static const struct uart_t Uart = {
  .init = &uart_init,
  .txByte = &uart_tx,
  .rxByte = &uart_rx,
  .txString = &uart_txstr,
  .rxString = &uart_rxstr
};

#endif
