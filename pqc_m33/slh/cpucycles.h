#ifndef CPUCYCLES_H
#define CPUCYCLES_H

#include <stdint.h>

/*
 * Measure CPU cycles.
 *
 * On Cortex-M with nRF SDK: uses DWT->CYCCNT.
 * On PC (x86): uses RDTSC.
 * On other platforms: falls back to CLOCK_MONOTONIC_RAW in "nanoseconds".
 */

/************ PC / generic implementation ************/

#if defined(__x86_64__) || defined(__i386__)

static inline void cpucycles_init(void)
{
    /* nothing to do on PC */
}

static inline void cpucycles_deinit(void)
{
    /* nothing to do on PC */
}

static inline uint64_t cpucycles(void)
{

    /* x86: use RDTSC */
    unsigned int hi, lo;
    __asm__ __volatile__("rdtsc" : "=a"(lo), "=d"(hi));
    return ((uint64_t)hi << 32) | lo;
}
#else

uint64_t cpucycles_overhead(void);

/************ Cortex-M / nRF implementation ************/

#include "nrf.h"

static inline void cpucycles_init(void)
{
    /* enable trace + cycle counter */
    DCB->DEMCR |= DCB_DEMCR_TRCENA_Msk;
    DWT->CYCCNT = 0;
    DWT->CTRL = DWT_CTRL_CYCCNTENA_Msk;
}

static inline void cpucycles_deinit(void)
{
    /* disable cycle counter */
    DWT->CTRL &= ~DWT_CTRL_CYCCNTENA_Msk;
}

/* Use 32-bit HW counter; promote to 64-bit for arithmetic */
static inline uint64_t cpucycles(void)
{
    return (uint64_t)DWT->CYCCNT;
}




#endif




#endif /* CPUCYCLES_H */

