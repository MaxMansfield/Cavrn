#include "uart.h"


#if defined(__AVR_ATmega328P__)
void uart_init(const byte  mode)
{

  UBRRH = UBRRH_VALUE;
  UBRRL = UBRRL_VALUE;

#if USE_2X 
  UCSRA |= (1<<U2X);
#else
  UCSRA &= ~(1<<U2X);
#endif

  // Enable TX and RX
  UART_START();
  
  switch(mode){
  case (ASYNC_MODE):
    UART_ASYNC();
    break;
  case (SYNC_MODE):
    UART_SYNC();
    break;
  case (MSPI_MODE):
    UART_MSPI();
    break;
  default:
    UART_ASYNC();
    break;
  }

  //Set Frame Size to 8 bit
  UCSRC |= (1<<UCSZ0);
  
  return;
}

#elif defined(__AVR_ATmega103__)
void uart_init(){
  UBRR = UBRR_VALUE; 
  // Enable TX and RX
  UART_START();
  return;
}
#endif 

void uart_tx(const byte* const data){
  // Wait for the Data Register empty flag
  while (!(UCSRA & (1<<UDRE)));
  UDR = *data;
}

uint8_t uart_rx(){
  while(!((UCSRA) & (1<<RXC)));
  return UDR;
}

char uart_rxchr(){
  while(!((UCSRA) & (1<<RXC)));
  return UDR;
}
void uart_txchr (const char* const chr)
{
  if(chr != NULL){
    // Wait for the Data Register empty flag
    while (!(UCSRA & (1<<UDRE)));
    UDR = *chr;
  }
  return;
}

void uart_txstr(const char*  string){
  uint16_t i = 0;
  while(i < strlen(string) && string[i] != '\0' && string != NULL)
    uart_txchr(&string[i++]);
}

const char* uart_rxstr(){
  static char string[RXLEN];
  static char* tmp;

  uint8_t i = 0;
  while((*tmp = uart_rxchr()) != '\n' && *tmp != '\0' && tmp != NULL && i < RXLEN)
    string[i] = *tmp;
  
  return string;
}
