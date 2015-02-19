/**
 * This is a simple Uart Tx example to showcase Cavrn
 */


// Include uart (duh!)
#include "cavrn/uart.h"

int main(void)
{

  // Initialize Uart
  Uart.init(ASYNC_MODE);

  // Only send printable chars...good for logging with UART
  Uart.printableCharsOnly = true;
  Uart.txString("Device Initialized.\n\r");

    uint8_t count = 0;
  while(1){
    Uart.txByte(count++);
    Uart.txString(": From Device!");
    Uart.txString("What the fuck");
  }
  return 0;
}
