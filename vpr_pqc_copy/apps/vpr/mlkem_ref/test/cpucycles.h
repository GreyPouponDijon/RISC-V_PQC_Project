#ifndef CPUCYCLES_H
#define CPUCYCLES_H
#endif
#include <stdint.h>
#include <stdbool.h>
#include "nrf_vpr_csr.h"

uint64_t cpucycles_overhead(void);

#include "nrf.h"

static inline void cpucycles_init(void)
{
  nrf_vpr_csr_machine_cycle_counter_enable_set(true);
}

static inline void cpucycles_deinit(void)
{
  
}

static inline uint64_t cpucycles(void) 
{
  return nrf_vpr_csr_machine_cycle_counter_get();
}

