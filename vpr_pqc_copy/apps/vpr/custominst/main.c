//Note: This only runs on a patched Vpr. It will go to trap handler on a standard Vpr due to the CUSTOM_0 instruction.
#include <stdio.h>
#include "nrf.h"

static inline unsigned rv_mymod(unsigned rs1, unsigned rs2)
{
    unsigned rd;
    // CUSTOM_0 opcode, funct3=0, funct7=1
    asm volatile (
        ".insn r CUSTOM_0, 0x0, 0x01, %0, %1, %2"
        : "=r"(rd)
        : "r"(rs1), "r"(rs2)
        : /* no clobbers */
    );
    return rd;
}


int main(void) {

  unsigned res;
  res = rv_mymod(1, 2);
  
  printf("Vpr custom inst: %d\n", 3);

  

  while (1) {
    __asm volatile ("wfi" ::: "memory");
  };
  
  return 0;
}

void _start(void) {
    main();
}
