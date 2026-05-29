#include <stdint.h>
#include <stdio.h>

int test_bench_keccak()
{
  uint64_t state_ref[25];
  uint32_t state_opt[50];

  for(int i = 0; i<25; i++){
    state_ref[i] = 0xFFFFFFFFFFFFFFFF ^ i;
    state_opt[i * 2] = (uint32_t)(state_ref[i] & 0xFFFFFFFF);
    state_opt[i * 2 + 1] = (uint32_t)(state_ref[i] >> 32);
  }

  //KeccakF1600_StatePermute_32bit(state_opt);
  //KeccakF1600_StatePermute(state_ref);

  uint64_t state64_concat[25];

  for (int i = 0; i < 25; i++){
    state64_concat[i] = ((uint64_t)state_opt[2*i]) | ((uint64_t)state_opt[2*i + 1] << 32);
  }

  for(int i = 0; i < 25; i++){
      printf("%16x, %16x, %d\n", state_ref[i], state64_concat[i], i);

      if(state_ref[i] != state64_concat[i]){
                return -1;
      }
  }

  return 0;

}

int main(void){

  int test_fail = test_bench_keccak();
  
  if(test_fail != 0) {
      printf("Fail!\n"); 
  } else {
      printf("Pass!\n");
  }

}
