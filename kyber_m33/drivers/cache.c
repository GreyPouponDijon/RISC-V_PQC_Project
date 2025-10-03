#include "nrf.h"

void cache_enable(void)
{
  NRF_ICACHE->ENABLE = CACHE_ENABLE_ENABLE_Enabled;
}
