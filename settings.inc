### Select which modules to compile
MODULES   := Uart Spi Nrf24

### Choose your device
DEVICE  := atmega103

### The devices speed in Hertz 
F_OSC   := 16000000UL

### The devices baud rate
BAUD    := 115200

### The device port
PORT 	:= /dev/ttyACM0

#PORT   = /dev/tty.usbserial-A900cbrd # Mac style serial port definiton
#PORT   = /dev/ttyACM0 # Linux style serial port definition
#PORT   = COM3 # Windows style serial port definition

### Soft-Programmer
AVRDUDE := avrdude -c arduino -p ${DEVICE} -P ${PORT} -b 115200 -U flash:w:$(PROJECT).hex
RESET   := avrdude -c arduino -p ${DEVICE} -P ${PORT} -b 115200

### Use only with NRF24 library
CE_PIN_DEF =  CE_PIN=PB6
CE_DDR_DEF =  CE_DDR=DDRB
