#ifndef _SPI_H_
#define _SPI_H_
#include "cavrn.h"

#define SPI_MODE0 0x00
#define SPI_MODE1 0x04
#define SPI_MODE2 0x08
#define SPI_MODE3 0x0A

#define MASTER 0xFA
#define SLAVE  0x00

#define MSB_ORDER 0x00
#define LSB_ORDER 0x01

#if defined(__AVR_ATmega328P__) || defined (__AVR_ATmega103__)

#define SPI_DDR  DDRB
#define SPI_PORT PORTB
#define SPI_PIN  PINB

#ifdef __AVR_ATmega328P__
#define SPI_SS   PB2
#define SPI_MOSI PB3
#define SPI_MISO PB4
#define SPI_SCK  PB5
#elif defined(__AVR_ATmega103__)
#define SPI_SS   PB0
#define SPI_SCK  PB1
#define SPI_MOSI PB2
#define SPI_MISO PB3
#endif //ATmega328P


//SPE =  Enable
//MSTR = is Master
#define ENABLE_MASTER ((1<<SPE) | (1<<MSTR))
#define ENABLE_SLAVE  ((1<<SPE) & ~(1<<MSTR))

#else
#error This MCU does not support SPI from Cavrn. Add proper defines to continue.
#endif

// Clock Speed options
#define F_OSC2   0x02
#define F_OSC4   0x04
#define F_OSC8   0x08
#define F_OSC16  0x16
#define F_OSC32  0x32
#define F_OSC64  0x64
#define F_OSC128 0xFF


void spi_init(const bool isMaster,const byte mode,const uint8_t clk);
uint8_t spi_transfer(uint8_t data);
void spi_setDataOrder(bool const dord);
void spi_disable();

struct spi_t {
  void    (*init) (const bool,const byte,const uint8_t); //Initialize SPI
  uint8_t (*transfer) (uint8_t const);  // Transfer a byte
  void    (*setDataOrder)(bool const);
  void    (*disable)();
};

static struct spi_t Spi = {
  .init = &spi_init,
  .transfer = &spi_transfer,
  .setDataOrder = &spi_setDataOrder,
  .disable = &spi_disable
};

#endif 
