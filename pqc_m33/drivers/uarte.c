#include <nrf.h>
#include <stdbool.h>

#define TX_BUF_SIZE 1


static bool m_initialized = false;

void hal_uarte_init(void)
{
  NRF_UARTE_Type * uarte_instance = (NRF_UARTE_Type *)CONFIG_HW_UARTE_INSTANCE;
  
  uarte_instance->BAUDRATE = UARTE_BAUDRATE_BAUDRATE_Baud1M;
  uarte_instance->PSEL.TXD = 4<<0 | 1<<5;//UART_TX_PIN;
  uarte_instance->PSEL.RXD = 5<<0 | 1<<5;//UART_TX_PIN;
/*  uarte_instance->BAUDRATE = UARTE_BAUDRATE_BAUDRATE_Baud921600;*/
  uint32_t hwfc   = (UARTE_CONFIG_HWFC_Enabled << UARTE_CONFIG_HWFC_Pos);
  uint32_t parity = (UARTE_CONFIG_PARITY_Excluded << UARTE_CONFIG_PARITY_Pos);
  uarte_instance->CONFIG = (uint32_t)hwfc | (uint32_t)parity;
  uarte_instance->ENABLE = (UARTE_ENABLE_ENABLE_Enabled << UARTE_ENABLE_ENABLE_Pos);

  
  m_initialized = true;
}

uint32_t hal_uarte_char_write(uint8_t ch) {
    if (!m_initialized) {
        hal_uarte_init();
    }

    NRF_UARTE_Type * uarte_instance = (NRF_UARTE_Type *)CONFIG_HW_UARTE_INSTANCE;
    uarte_instance->ERRORSRC = 0;


    static volatile uint8_t m_tx_buf[TX_BUF_SIZE];
    (void)m_tx_buf;


    m_tx_buf[0] = ch;

    uarte_instance->DMA.TX.PTR = (uint32_t)((uint8_t *)m_tx_buf);
    uarte_instance->DMA.TX.MAXCNT = (uint32_t)sizeof(m_tx_buf);
    uarte_instance->TASKS_DMA.TX.START = 1;


    while((0 == uarte_instance->EVENTS_TXDRDY)) ;

    uarte_instance->EVENTS_TXDRDY  = 0;
    uarte_instance->TASKS_DMA.TX.STOP  = 1;

    return uarte_instance->ERRORSRC;
}

uint32_t hal_uarte_char_read(uint8_t * ch) {


}
