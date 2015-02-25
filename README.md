![Cavrn](http://i.imgur.com/EJCUbXa.png) 
# An easy to use and extremely flexible library for AVR Microcontrollers, written in pure C.
[![Build Status](https://travis-ci.org/MaxMansfield/Cavrn.svg?branch=test)](https://travis-ci.org/MaxMansfield/Cavrn)


##### Version: 0.1.0 (*Sedimentary Olm*)
##### Major Version: 0 (Sedimentary)   
##### Minor Version: 1.0  (Olm)
##### Working Modules: Uart
##### Modules in Work: SPI Nrf24
##### Future Modules: I2C W5100 SSD1306
##### Supported MCUs: ATmega328p, ATmega103
##### Coming Soon: ATtiny85

Cavrn aims to be a fully featured AVR library that is optimized for ease of use while still retaining flexibility per device and fits in as a pure C Arduino-esque library.




Each available function (Uart,Spi,Nrf24) which I'll be calling a module uses `static struct`s full of function pointers to represent each module an its capabilities. A module is then called by the module name and then the function, similar to an object.

~~~~~~~~~~~~~~~~~~~~{.c}
#include "cavrn/uart.h"

int main (void)
{
   /* initialize UART in full duplex */
    Uart.init(ASYNC_MODE);
    
    /* only send/recieve  printable char when using Uart.txString and Uart.rxString() */
    Uart.printableCharsOnly = false;
    
    /* global interrupts Off */
    Cavrn.setInterrupts(OFF);
    
    /* enables global interrupts and enables Uart TX interrupts */
    Uart.setTxInterrupt(ON);
    
    /* byte is defined as part of Cavrn check the docs for more. */
    byte count = 0;
    while(1){
       char text[32];
       sprinf(text,"Run number %d",count++);
       Uart.txString(text);
       Uart.txByte("A");
    }
    return 0;
}
~~~~~~~~~~~~~~~~~~~~

Cavrn library is built on avr-libc, compiled with avr-gcc and meant to be easy to use while still retaining flexibility per mmcu for professional situations.
 
# Path of Knowledge
Here is a listing of the documentation you may find helpful. You can either check it out now or read the rest of this page, either way...I'll be here.

|     Content        |                Link                                                            |
|--------------------|:-------------------------------------------------------------------------------|
|__I.   Starting__   |[Cavrn Docs - Getting Started](http://maxmansfield.github.io/Cavrn/modules.html)|
|__II.  Building__   |[Cavrn Docs - Build Cavrn](http://maxmansfield.github.io/Cavrn/modules.html)    |
|__III. Installing__ |[Cavrn Docs - Install Cavrn](http://maxmansfield.github.io/Cavrn/modules.html)  |
|__IV.  Examples__   |[Cavrn Docs - Examples](http://maxmansfield.github.io/Cavrn/examples.html)      |
|__V.   Modules__    |[Cavrn Docs - Modules](http://maxmansfield.github.io/Cavrn/modules.html)        |
|__VI.  Versions__   |[Cavrn Docs - Versioning](http://maxmansfield.github.io/Cavrn/versions.html)    |
|__VII. References__ |[Cavrn Docs - Inspiration](http://maxmansfield.github.io/Cavrn/modules.html)    |  


# Requirements

###### Operating System:
+ [Linux](http://www.linux.com/): Yes
+ [OS X](https://www.apple.com/osx/): Not Tested
+ [Windows](http://windows.microsoft.com/en-us/windows/home): Not Tested



###### Device:
+ [Atmel AVR ATmega328p](http://www.atmel.com/images/Atmel-8271-8-bit-AVR-Microcontroller-ATmega48A-48PA-88A-88PA-168A-168PA-328-328P_datasheet_Complete.pdf)
+ [Atmel AVR ATmega103](http://www.atmel.com/Images/doc0945.pdf)

###### Build Tools:
+ [avr-gcc build suite](https://gcc.gnu.org/wiki/avr-gcc) 
	- [avr-ld](http://ccrma.stanford.edu/planetccrma/man/man1/avr-ld.1.html), avr-sz, etc...
+ [AVR libc](http://www.nongnu.org/avr-libc/)
+ [make](http://www.gnu.org/software/make/)

	
To upload you will need a software programmer or/and ICSP of your choice but if you install `avrdude` you can then run `make upload` if you have configured you serial port in the `settings.inc` file...more on that later if you haven't already browsed the documentation.

To view serial data you can install a serial monitor called screen and type `make console` but for long term use I recommend minicom and to configure your own profiles for it.

At the moment a board with an Atmega328p or Atmega103 is required, but this will change soon. If you have the interest, it would be very simple to add defines for a board that you own. Simply define each pin that will be used in the appropriate header file. 

Contact me if you ever need help.

# Quick Start
#####If you don't want to read docs (or even if you did) and you want to try the library really quick the best option is to build the example directory so make sure you have all the requirements and check it out...

For the time being here's the build process:

1. Download the repo and change `settings.inc` to fit your needs. (note: you don't need to change any other file). 
2. Run `make examples` 
3. That will build the library and populate the `examples/` folder.
4. The built objects and a static library file will be in the newly created `build/` directory
5. Change into the `examples/` directory and choose a module, then choose an example type.
6. Run `make` in the example folder you picked

You will now have a `main.hex` file to upload to an AVR and if you have `avrdude` installed and configured then you can type `make upload`.

# Using Cavrn
To use Cavrn include the source and objects or static library files in you project directory or link to them. At the moment this is not the easiest part of the process by any means but it has only been a few days, give it time and I'll have a killer install chain.


####Let Me Know if you ever have an issue: <mailto:max.m.mansfield@gmail.com>
