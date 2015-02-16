#include "spi.h"



void spi_init(const bool isMaster,const byte mode,const uint8_t clk)
{

  SPI_DDR |= ((1<<SPI_SCK) | (1<<SPI_SS));
  SPCR |= (1<<SPE) | (1<<SPIE);
  if(isMaster){

    // MOSI=out MISO=in SCK=out SS=out
    SPI_DDR |= (1<<SPI_MOSI) | (0<<SPI_MISO) | (1<<SPI_SCK) | (1<<SPI_SCK);
    
    //Set as Master, Enable interrupts
    SPCR |= (ENABLE_MASTER);

    // Choose clock speed
    
#if defined( __AVR_ATmega328P__)
    switch(clk){
    case (F_OSC2):
      SPCR |= (1<<SPI2X);
      SPCR &= ~((1<<SPR1) | (1<<SPR0));
      break;
    case (F_OSC4):
      SPCR &= ~((1<<SPR1) | (1<<SPR0) | (1<<SPI2X));
      break;
    case (F_OSC8):
      SPCR |= ((1<<SPI2X) | (1<<SPR0));
      SPCR &= ~(1<<SPR1);
      break;
    case (F_OSC16):
      SPCR |= (1<<SPR0);
      SPCR &= ~((1<<SPR1) |  (1<<SPI2X));
      break;
    case (F_OSC32):
      SPCR |= ((1<<SPI2X) | (1<<SPR1));
      SPCR &= ~(1<<SPR0);
      break;
    case (F_OSC64):
      SPCR |= ((1<<SPR1) | (1<<SPR0) | (1<<SPI2X));
      break;
    case (F_OSC128):
      SPCR |= ((1<<SPR0) | (1<<SPR1));
      SPCR &= ~(1<<SPI2X);
      break;
    default:
      SPCR |= (1<<SPR0);
      SPCR &= ~((1<<SPR1) |  (1<<SPI2X));
      break;
    }
#elif defined(__AVR_ATmega103__)
    switch(clk){
    case (F_OSC4):
      SPCR &= ~((1<<SPR1) | (1<<SPR0));
      break;
    case (F_OSC16):
      SPCR |= (1<<SPR0);
      SPCR &= ~((1<<SPR1));
      break;
    case (F_OSC64):
      SPCR |= ((1<<SPR1) | (1<<SPR0));
      break;
    case (F_OSC128):
      SPCR |= ((1<<SPR0) | (1<<SPR1));
      break;
    default:
      SPCR |= (1<<SPR0);
      SPCR &= ~((1<<SPR1));
      break;
    }
#endif	
  } else {
    //Enter Slave mode
    // MOSI=in MISO=out SCK=in SS=in
    SPI_DDR |= ((0<<SPI_MOSI) |  (1<<SPI_MISO) | (0<<SPI_SCK) | (0<<SPI_SCK));
    SPCR |= (ENABLE_SLAVE);
  }

  switch(mode){
  case (SPI_MODE0):
    SPCR &= ~(1<<CPOL);
    SPCR &= ~(1<<CPHA);
    break;
  case (SPI_MODE1):
    SPCR &= ~(1<<CPOL);
    SPCR |= (1<<CPHA);
    break;
  case(SPI_MODE2):
    SPCR |= (1<<CPOL);
    SPCR &= ~(1<<CPHA);
    break;
  case(SPI_MODE3):
    SPCR |= (1<<CPOL) | (1<<CPHA);
    break;
  default:
    SPCR &= ~(1<<CPOL);
    SPCR &= ~(1<<CPHA);
    break;
  }
    
  interruptsOn();
  return;
}

uint8_t spi_transfer(uint8_t data)
{
  SPDR = data;

  //Wait for completion
  while(! ((SPSR) & (1<<SPIF)));

  return (SPDR);
}

void spi_disable()
{
  SPCR = 0;
  return;
}

void spi_setDataOrder(const bool dord)
{

  if(dord)
    SPCR |= (1<<DORD);
  else
    SPCR &= ~(1<<DORD);

  return;
}
