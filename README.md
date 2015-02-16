#Cavrn 
## An easy to use and extremely flexible library for AVR Microcontrollers, written in pure C.
<hr>
###### Supported: ATmega328p, ATmega103
###### Coming Soon: ATtiny85

Cavrn library is built on avr-libc, compiled with avr-gcc and meant to be easy to use while still retaining flexibility per mmcu for professional situations.Each available function (uart,spi,nrf24) which I'll be calling a module has a static struct that can be treated as an object when performing its operations. Cavrn takes techniques found in the arduino library (like how Cavrn uses typedefs and defines to create more verbose types such as bool and byte, both of which mean a uint8_t but when used correctly your code becomes much more explicit) as well as borrows from multiple others across the internet (including the NRF24lo1 repo this was originally forked from) to combine them with good practices and solid compiler integration. 


##Usage 
At the moment there is not an install script to create a shared library file and install via a package manager, but I have a handy script for that which I need to modify just a bit for it to work with this.
For the time being you can simply download the repo and configure the `Makefile` to fit your needs. Then run `make` and if your board is plugged in `make upload`.

##Requirements
To compile Cavrn you will need the avr-gcc suite as well as avr-libc. To upload you will need avrdude and to view serial data you can install screen and type `make console` but for long term use I recommend minicom.

At the moment a board with an Atmega328p or Atmega103 is required, but this will change soon. If you have the interest, it would be very simple to add defines for a board that you own. Simply define easch pin that will be used in the appropriate header file.

<hr>
## UART
####A library implementation for sending/recieving bytes or strings via UART pins. 


Uart is able to take advantage of all modes given by an MCU. Just provide it during initialization.
*note: The AVR ATmega103 does not have available status control registers to determine half/full duplex so no mode is needed at initialization.*

`
Uart.init(ASYNC_MODE)
or
Uart.init(SYNC_MODE)
or
Uart.init(MSPI_MODE)
`
Uart relies on a BAUD definition at compile time because many preprocessor directives rely on it; one benefit of doing it this way is that no large 32bit integers have to be used (ex. Baud of 115200) another is the assurance that your baud rate is what you would expect throughout the program and finally no compute time is wasted on arithmatic to calculate baud rates or `F_OSC` clock rates or even to separate high and low values for the USART Baud Rate Register because the preprocessor computes it.

To Define the Baud rate add -DBAUD=9600 or any other rate to the compilation. For most situations, simply fill in the provided makefile. During the extent of your program you can change the BAUD by undefining BAUD and redefining it before reincluding the <util/setbaud.h> file. This sounds janky but the setbaud.h file is simply a collection of preprocessor directives which will only be present at compile time and infact avr-libc recommends this way.

Take this example to see how easy to use the Uart library is (and eventually all of Cavrn).
```C
#include "Cavrn/uart.h"

int main(void)
{
  Uart.init(ASYNC_MODE);
  Uart.txString("Device Initialized\n\r");
 
  while(1){
    uint8_t recieved = Uart.rxByte();
    char text[128];
    sprintf(text,"Devices Recieved Data: %d\n\rAnalyzing...",recieved);
    Uart.txString(text);
   }
  return 0;
}
```
<hr>
## SPI (Almost Operational)
#### A simple and elegant peripheral communication library.

The SPI library takes a fairly straight forward and simple process even further by encapsulating functions in a data safe manner with high pointer usage for optimization but still gives you the flexibility that you would have from coding it by hand.

You can choose from the 4 clock polarity modes provided by Atmel.
![Table of SPI MODES 0-3](http://i.imgur.com/S5VM2XL.png)

By initializing SPI with one of the four modes like so...
```C
#include "Cavrn/spi.h"

int main(void){
  /* To assign as a master device */
  Spi.init(MASTER,SPI_MODE0,F_OSC16);
  
  //or another way to assign as a master device (true is defined as part of Cavrn)
  Spi.init(true,SPI_MODE0,F_OSC16); 
  
  // or as a slave device
  Spi.init(SLAVE,SPI_MODE2,F_OSC8); 
  
  // and the data order can be changed from MSB to LSB and back by using setDataOrder from Spi...
  Spi.setDataOrder(MSB_ORDER);
  //Spi.setDataOrder(true) try using...HIGH,OUT,ON instead of true
  
  // or for least significant bit
  Spi.setDataOrder(LSB_ORDER);
  //Spi.setDataOrder(false);
  
  Spi.setInterrupts(true);
  //Spi.setInterrupts(ON);
  
  // To transfer via SPI
  char letter_L = 'L';
  uint8_t recieved = Spi.transfer(letter_L);
  // To transfer large amounts
  byte[128] text;
  byte[128] out = "Hello World";
  Spi.multiTransfer(out,text,128);
  
  
  Spi.disable();
 
   return 0;
}
```
<hr>
## NRF24 (Relies on SPI)
#### Making wireless connectivity quick and painless.

This module enables the auto acknowledgement and auto retransmission features of the nrf24L01+ in static length payload mode. 

These two features are basically the most important features of the nrf24L01+ modules. With this module, after you make a tranmission attempt, you'll know for sure wheter the slave device got your message properly or not with minimal MCU involvement. Also, nrf24L01+ chipsets automatically handle the retranmission of the same message if it they lost in transmission, up to o limited trials with adjustable delays in between attempts.

## Usage

### File strutcture

The module basically consists of only three files: `nrf24.c `, `nrf24.h` and `nRF24L01.h` (as well as the SPI module it relies on).

### Configuration

Configuration of the module is simple. Max retransmission count is set to 15 and delays between each retranmission is set to 1000 us. Also the CRC is enabled with 1byte length. Data rate is set to 1Mbps.

Via the config function, you can chose the channel and the payload length. Max payload length is 32. After the config function the module automatically goes to RX mode. Payload length and the RF channel values have to be consistent among the devices.

```C
	/* initializes hardware pins */
	Nrf24.init();
	
	/* RF channel: #2 , payload length: 4 */
	Nrf24.config(2,4)
```
### Addressing

Address length is 5 bytes. You can configure the transmit and receive addresses as follows:
```C	
	uint8_t rx_mac[5] = {0xE7,0xE7,0xE7,0xE7,0xE7};
	uint8_t tx_mac[5] = {0xD7,0xD7,0xD7,0xD7,0xD7};
		
	/* Set the module's own address */
	Nrf24.rxAddr(rx_mac);
	
	/* Set the transmit address */
	Nrf24.txAddr(tx_mac);
```
### Transmit

Let's say the payload length is set to 4 and you have the following payload.
```C	
	uint8_t data_array[4];
	
	data_array[0] = 0x00;
	data_array[1] = 0xAA;
	data_array[2] = 0x55;
	data_array[3] = 0xFF;
```	
The basic transmit function is the `Nrf24.txData()` function. The module automatically switches to the TX mode and power up if required.
```C
	/* Automatically goes to TX mode */
	Nrf24.txData(data_array);		
```	
After the `nrf24_send()`, you must wait for transmission to end. MCU can sleep or do another tasks during that period.
```C	
	/* Wait for transmission to end */
	while(Nrf24.isSending());
```	
After the transmission end, optionally you can make analysis on the last transmission attempt.
```C
	uint8_t temp;
	
	/* Make analysis on last tranmission attempt */
	temp = Nrf24.lastTxStatus();

	if(temp == NRF24_TRANSMISSON_OK)
	{					
		Uart.txString("Tranmission went OK\r\n");
	}
	else if(temp == NRF24_MESSAGE_LOST)
	{					
		Uart.txString("Message is lost ...\r\n");	
	}
     	
    /* Retranmission count indicates the tranmission quality */
    temp = Nrf24.badTxCount();
    
    char msg[64];
    sprintf(msg,"Retranmission count: %d\r\n",temp);
    Uart.txString(msg);
  ```
After the tranmission finishes, nrf24L01+ module stays in Standby mode. You can manually go back to RX mode:
```C
   /* Go back to RX mode ... */
   Nrf24.powerRx();
 ```
Or you can power down the module to lower the current consumption.
```C
    /* Power down the module */
    Nrf24.powerDown();	
```
### Receive

This library doesn't use the IRQ pin of the nrf24L01+ (yet) , therefore you need to poll the `nrf24_dataReady()` function periodically. Otherwise you might miss some packets. 

Also, you need to be in RX mode in order to be able to receive messages.

`nrf24_dataReady()` function returns non-zero only if a valid payload is awaiting in the RX fifo. `nrf24_getData(uint8_t* buf)` function copies the received message into the given buffer. 
```C
	uint8_t data_array[4];

	if(nNrf24.dataReady())
	{
		Nrf24.rxData(data_array);		
	}
```
## References

This module is proudly and heavily based on the following libraries:

- https://github.com/aaronds/arduino-nrf24l01
- http://www.tinkerer.eu/AVRLib/nRF24L01
