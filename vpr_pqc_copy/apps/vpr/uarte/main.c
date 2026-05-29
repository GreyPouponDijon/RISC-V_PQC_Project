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
  
  //printf("vpr_accres: %d\n", res);

  printf("vpr_accres: %d\n", 3);

  printf("print again\n");

  
  //printf("Hello, VPR! Acc \r\n");
    while (1) {
        __asm volatile ("wfi" ::: "memory");
    };
    
    return 0;
}

void _start(void) {
    main();
}


