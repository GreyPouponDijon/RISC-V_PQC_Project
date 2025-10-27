#include <stdint.h>
#include "randombytes.h"

//TODO Maybe we do not want to use the hardware RNG for all randomness, but instead only read a seed and then expand that using fips202.

void randombytes(uint8_t *out, size_t outlen) {
  //printf("randombytes(%d, %d)\n", out, outlen);
  while(outlen--) *out++ = 0x29;
}
