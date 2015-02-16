/*
* ----------------------------------------------------------------------------
* “THE COFFEEWARE LICENSE” (Revision 1):
* <ihsan@kehribar.me> wrote this file. As long as you retain this notice you
* can do whatever you want with this stuff. If we meet some day, and you think
* this stuff is worth it, you can buy me a coffee in return.
* -----------------------------------------------------------------------------
* This library is based on this library: 
*   https://github.com/aaronds/arduino-nrf24l01
* Which is based on this library: 
*   http://www.tinkerer.eu/AVRLib/nRF24L01
* -----------------------------------------------------------------------------
*/

#ifndef NRF24
#define NRF24


#include "spi.h"
#include "nRF24L01.h"

#define LOW 0
#define HIGH 1

#define nrf24_ADDR_LEN 5
#define nrf24_CONFIG (_BV(EN_CRC)|(0<<CRCO))

#define NRF24_TRANSMISSON_OK 0
#define NRF24_MESSAGE_LOST   1

/* adjustment functions */
void    nrf24_init();
void    nrf24_rx_address(const byte* const adr);
void    nrf24_tx_address(const byte* const adr);
void    nrf24_config(const uint8_t channel, const uint8_t pay_length);

/* state check functions */
bool nrf24_dataReady();
bool nrf24_isSending();
bool nrf24_getStatus();
bool nrf24_rxFifoEmpty();

/* core TX / RX functions */
void    nrf24_send(const byte* const value);
void    nrf24_getData(byte* const data);

/* use in dynamic length mode */
uint8_t nrf24_payloadLength();

/* post transmission analysis */
uint8_t nrf24_lastMessageStatus();
uint8_t nrf24_retransmissionCount();

/* Returns the payload length */
uint8_t nrf24_payload_length();

/* power management */
void    nrf24_powerUpRx();
void    nrf24_powerUpTx();
void    nrf24_powerDown();


/* low level interface ... */
void    nrf24_configRegister(const byte  reg, const  byte value);
void    nrf24_readRegister(const byte reg, byte* const  value, const uint8_t len);
void    nrf24_writeRegister(const byte reg, const byte* const value, const uint8_t len);


struct nrf24_t {
  /* adjustment functions */
  void (*init)();
  void (*txAddr)(const byte* const);
  void (*rxAddr)(const byte* const);
  void (*config)(const uint8_t,const uint8_t);
  

  /* state check functions */
  bool    (*dataReady)();
  bool    (*isSending)();
  uint8_t (*getStatus)();
  bool    (*rxWaiting)();

  void (*txData)(const byte* const);
  void (*rxData)(byte* const);

  /* Returns the payload length */
  uint8_t (*paylength)();

  /* post transmission analysis */
  uint8_t (*lastTxStatus)();
  uint8_t (*badTxCount)();
  
  /* power management */
  void    (*powerRx)();
  void    (*powerTx)();
  void    (*powerDown)();

  uint8_t payload_len;
		 
};



#define nrf24_ce_digitalWrite(LOW) CE_DDR &= ~_BV(CE_PIN)
#define nrf24_ce_digitalWrite(HIGH) CE_DDR |= _BV(CE_PIN)

#define nrf24_csn_digitalWrite(HIGH) SPI_DDR |= _BV(SPI_SS)
#define nrf24_csn_digitalWrite(LOW) SPI_DDR &= ~_BV(SPI_SS)

static struct nrf24_t Nrf24 = {
  /* adjustment functions */
  .init =   &nrf24_init,
  .txAddr = &nrf24_tx_address,
  .rxAddr = &nrf24_rx_address,
  .config = &nrf24_config,

  /* state check functions */
  .dataReady = &nrf24_dataReady,
  .isSending = &nrf24_isSending,
  .getStatus = &nrf24_getStatus,
  .rxWaiting = &nrf24_rxFifoEmpty,

  .txData= &nrf24_send,
  .rxData = &nrf24_getData,

  /* Returns the payload length */
  .paylength = &nrf24_payload_length,

   /* post transmission analysis */
  .lastTxStatus = &nrf24_lastMessageStatus,
  .badTxCount = &nrf24_retransmissionCount,
    
  /* power management */
  .powerRx = &nrf24_powerUpRx,
  .powerTx = &nrf24_powerUpTx,
  .powerDown = &nrf24_powerDown,

  .payload_len = 0
};

#endif
