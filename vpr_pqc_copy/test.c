#include <stdint.h>
#include <stdio.h>

#define NROUNDS 24

#define ROL(a, offset) ((a << offset) ^ (a >> (64-offset)))


static inline void rol64_concat(uint32_t hi, uint32_t lo, uint32_t offset, uint32_t *out_hi, uint32_t *out_lo)
{
  uint64_t concat_val = ((uint64_t)hi << 32) | lo;
  uint64_t rot_val = (concat_val << offset) ^ (concat_val >> (64-offset));

  *out_hi = (uint32_t)(rot_val >> 32);
  *out_lo = (uint32_t)rot_val;
}

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

int main(void)
{
  uint64_t rol_result, rol_concat_result;
  uint32_t temp_hi, temp_lo;
  for(int j = 1; j < 65; j++)
  {
    for(int i = 0; i < NROUNDS; i++)
    {
      rol_result = ROL(KeccakF_RoundConstants[i], j);
      uint32_t i_hi = (uint32_t)(KeccakF_RoundConstants[i] >> 32);
      uint32_t i_lo = (uint32_t)KeccakF_RoundConstants[i];
      rol64_concat(i_hi, i_lo, j, &temp_hi, &temp_lo);
      rol_concat_result = ((uint64_t)temp_hi << 32) | temp_lo;
      printf("Start Val: %016x, Regular rol: %016x, Concat and rol: %016x, Rotate offset %d\n", i, rol_result, rol_concat_result, j);
      //printf("Concat and rol: %08x\n", rol_concat_result);
      //printf("Rotate offset: %d\n", j);
      if(rol_result != rol_concat_result){
        printf("Fail!\n");
        return 0;
      }
    }
  }
  printf("Pass\n");
  return 0;
}
