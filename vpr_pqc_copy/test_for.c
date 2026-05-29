#include <stdio.h>
#include <stdint.h>


#define NROUNDS 24

/* Keccak round constants */
static const uint64_t KeccakF_RoundConstants[NROUNDS] = {
  (uint64_t)0x0000000000000001ULL,
  (uint64_t)0x0000000000008082ULL,
  (uint64_t)0x800000000000808aULL,
  (uint64_t)0x8000000080008000ULL,
  (uint64_t)0x000000000000808bULL,
  (uint64_t)0x0000000080000001ULL,
  (uint64_t)0x8000000080008081ULL,
  (uint64_t)0x8000000000008009ULL,
  (uint64_t)0x000000000000008aULL,
  (uint64_t)0x0000000000000088ULL,
  (uint64_t)0x0000000080008009ULL,
  (uint64_t)0x000000008000000aULL,
  (uint64_t)0x000000008000808bULL,
  (uint64_t)0x800000000000008bULL,
  (uint64_t)0x8000000000008089ULL,
  (uint64_t)0x8000000000008003ULL,
  (uint64_t)0x8000000000008002ULL,
  (uint64_t)0x8000000000000080ULL,
  (uint64_t)0x000000000000800aULL,
  (uint64_t)0x800000008000000aULL,
  (uint64_t)0x8000000080008081ULL,
  (uint64_t)0x8000000000008080ULL,
  (uint64_t)0x0000000080000001ULL,
  (uint64_t)0x8000000080008008ULL
};

static const uint32_t KeccakF_RoundConstants32[2 * 24] = {
    0x00000000, 0x00000001,
    0x00000000, 0x00008082,
    0x80000000, 0x0000808a,
    0x80000000, 0x80008000,
    0x00000000, 0x0000808b,
    0x00000000, 0x80000001,
    0x80000000, 0x80008081,
    0x80000000, 0x00008009,
    0x00000000, 0x0000008a,
    0x00000000, 0x00000088,
    0x00000000, 0x80008009,
    0x00000000, 0x8000000a,
    0x00000000, 0x8000808b,
    0x80000000, 0x0000008b,
    0x80000000, 0x00008089,
    0x80000000, 0x00008003,
    0x80000000, 0x00008002,
    0x80000000, 0x00000080,
    0x00000000, 0x0000800a,
    0x80000000, 0x8000000a,
    0x80000000, 0x80008081,
    0x80000000, 0x00008080,
    0x00000000, 0x80000001,
    0x80000000, 0x80008008
};

int main (void)
{

  for (int round = 0; round < 24; round++)
  {
    //printf("%d\n", round);
    uint32_t lo = (uint32_t)KeccakF_RoundConstants[round];
    uint32_t hi = (uint32_t)(KeccakF_RoundConstants[round] >> 32);
    printf("Round: %d, 64_bit lo: %08x, hi: %08x\n", round, lo, hi);
  }

  //Loop UNrolling
  for (int round = 0; round < 24; round += 2)
  {
    int i = 2 * round;

    // Round r
    uint32_t hi0 = KeccakF_RoundConstants32[i];
    uint32_t lo0 = KeccakF_RoundConstants32[i + 1];

    printf("Round %d, lo: %08x, hi: %08x\n", round, lo0, hi0);

    // Round r+1
    uint32_t hi1 = KeccakF_RoundConstants32[i + 2];
    uint32_t lo1 = KeccakF_RoundConstants32[i + 3];

    printf("Round %d, lo: %08x, hi: %08x\n", round + 1, lo1, hi1);
  }
	return 0;
}
