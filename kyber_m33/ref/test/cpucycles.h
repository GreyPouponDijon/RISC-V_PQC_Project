#ifndef CPUCYCLES_H
#define CPUCYCLES_H

#include <stdint.h>


DWT DWT_TYPE



#ifdef defined(__x86_64__) || defined(_M_X64)
#ifdef USE_RDPMC  /* Needs echo 2 > /sys/devices/cpu/rdpmc */

static inline uint64_t cpucycles(void) {
  const uint32_t ecx = (1U << 30) + 1;
  uint64_t result;

  __asm__ volatile ("rdpmc; shlq $32,%%rdx; orq %%rdx,%%rax"
    : "=a" (result) : "c" (ecx) : "rdx");

  return result;
}

#else

static inline uint64_t cpucycles(void) {
  uint64_t result;

  __asm__ volatile ("rdtsc; shlq $32,%%rdx; orq %%rdx,%%rax"
    : "=a" (result) : : "%rdx");

  return result;
}

#endif

uint64_t cpucycles_overhead(void);

#elif defined(__arm__) || defined(_M_ARM)

#include "core_cm33.h"
;
static inline void cpucycles_init(void)
{
  DCB->DEMCR |= DCB_DEMCR_TRCENA_Msk;
  DWT->CYCCNT = 0;
  DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk
}

static inline uint32_t cpucycles(void) {


  uint32_t last;
  uint32_t high;
	uint32_t now = DWT->CYCCNT;
  high += (now < last);
  last = now;

	return ((uint64_t)high << 32) | now; 
}


#else

static inline uint64_t cpucycles(void) { return 0; }

#endif

