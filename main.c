#include "uart.h"
#include "spi.h"

int main()
{
  Uart.init(ASYNC_MODE);


  uint8_t counter = 0;

  while(1){
    char text[128];
    sprintf(text,"From Slave: Sent Data: %d \n\r", counter++);
    Uart.txString(text);
  }
  return 0;
}
