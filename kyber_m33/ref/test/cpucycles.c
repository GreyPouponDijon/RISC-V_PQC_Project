#include <stdint.h>
#include "cpucycles.h"


#ifdef defined(__arm__) || defined(_M_ARM)

uint32_t cpucycles_overhead(void) {
	uint32_t t0, t1, overhead = -1L;

#elif defined(__x86_64__) || defined(_M_X64)

uint64_t cpucycles_overhead(void) {
  uint64_t t0, t1, overhead = -1LL;
#endif
  
  unsigned int i;

  for(i=0;i<100000;i++) {
    t0 = cpucycles();
    __asm__ volatile ("");
    t1 = cpucycles();
    if(t1 - t0 < overhead)
      overhead = t1 - t0;
  }

  return overhead;
}



