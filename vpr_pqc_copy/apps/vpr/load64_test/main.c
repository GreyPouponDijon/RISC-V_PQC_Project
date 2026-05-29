#include <stdint.h>

#define LOAD64_INST ".4byte 0x0000500b\n\t"

static inline void load64(uint32_t *addr, uint32_t *offset, volatile uint32_t *rd1, volatile uint32_t *rd2)
{
  uint32_t lo, hi;
  asm volatile(
     ".insn r CUSTOM_0, 0x4, 0x1, %[lo], %[addr], zero\n\t" //dummy_inst(addr, rd1) -> res1, res2;
     "nop\n\t"
     ".insn r CUSTOM_0, 0x4, 0x0, %[hi], %[offset], zero\n\t" //dummy_inst(addr, rd2) -> res3, res4;
     "nop\n\t"
     LOAD64_INST
     : [lo] "=&r" (lo),
     [hi] "=&r" (hi)
     : [addr] "r" (addr),
     [offset] "r" (offset)
     : "memory"
     );
    
  *rd1 = lo;
  *rd2 = hi;
}


int load64_test(void)
{
  uint32_t word[2];

  word[0] = 0xACABACAB;
  word[1] = 0xCAFEBABE;

  volatile uint32_t lo_loaded, hi_loaded;

  load64(&word[0], 0, &lo_loaded, &hi_loaded);

  if((word[0] != lo_loaded) && (word[1] == hi_loaded))
  {
    return 0;
  } else {
    return -1;
  }
}



void __attribute__((noinline, used))sim_pass(void)
{ 
  while(1);
}

void __attribute__((noinline, used))sim_fail(void)
{
  while(1);
}



int main(void)
{
  int result = load64_test();
  if(result != 0){
    sim_fail();
  } else {
    sim_pass();
  }
}


int _start(void)
{
  main();
}
