#ifndef CPUCYCLES_H
#define CPUCYCLES_H

#include <stdint.h>



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

static inline uint32_t cpu_cycles(void) {
	
	
	result = DWT->CYCCNT;
	return result;
}


static inline uint32_t cpu_overhead(void)


#else

static inline uint64_t cpu_cycles(void) { return 0; }

#endif
