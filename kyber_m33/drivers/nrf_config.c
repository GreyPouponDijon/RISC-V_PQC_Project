#include "nrf.h"

void nrf_config_init(void)
{
  NRF_ICACHE->ENABLE      = CACHE_ENABLE_ENABLE_Enabled;
  NRF_RRAMC->POWER.CONFIG = 0xFFFF;
}
