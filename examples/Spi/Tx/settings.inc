#enter the name of you executable without the file extension.
MAIN_FILE := main

### Select which modules to compile
MODULES   := Uart 

### Choose your device
DEVICE  := atmega328p

### The devices speed in Hertz 
F_OSC   := 16000000UL

### The devices baud rate
BAUD    := 115200

### The device port
PORT 	:= /dev/ttyACM0

#PORT   = /dev/tty.usbserial-A900cbrd # Mac style serial port definiton
#PORT   = /dev/ttyACM0 # Linux style serial port definition
#PORT   = COM3 # Windows style serial port definition



### Use only with NRF24 library
#CE_PIN_DEF =  CE_PIN=PB6
#CE_DDR_DEF =  CE_DDR=DDRB
