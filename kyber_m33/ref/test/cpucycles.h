#ifndef CPUCYCLES_H
#define CPUCYCLES_H
#endif
#include <stdint.h>


uint64_t cpucycles_overhead(void);


#include "nrf.h"

static inline void cpucycles_init(void)
{
  DCB->DEMCR |= DCB_DEMCR_TRCENA_Msk;
  DWT->CYCCNT = 0;
  DWT->CTRL = DWT_CTRL_CYCCNTENA_Msk;
}

static inline void cpucycles_deinit(void)
{
  DWT->CYCCNT &= ~DWT_CTRL_CYCCNTENA_Msk;
}

static inline uint32_t cpucycles(void) { 
  return DWT->CYCCNT;
}

