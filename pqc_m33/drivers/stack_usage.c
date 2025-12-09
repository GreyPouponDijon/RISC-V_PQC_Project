#include <stdint.h>
#include <stddef.h>
#include "stack_usage.h"

extern char end;

static char* heap_end = &end;

const uint32_t stack_pattern = 0xCAFEBABElu;

static void* last_sp = NULL;

void fill_stack(void){

  char* _heap_end = heap_end;
  asm volatile ("mov %0, sp\n"
                ".L%=:\n\t"
                "str %2, [%1], #4\n\t"
                "cmp %1, %0\n\t"
                "blt .L%=\n\t"
                : "+r" (last_sp), "+r" (_heap_end) : "r" (stack_pattern) : "cc", "memory");
}

size_t check_stack(void)
{
  size_t result = 0;
  asm volatile("sub %0, %1, %2\n"
               ".L%=:\n\t"
               "ldr ip, [%2], #4\n\t"
               "cmp ip, %3\n\t"
               "ite eq\n\t"
               "subeq %0, #4\n\t"
               "bne .LE%=\n\t"
               "cmp %2, %1\n\t"
               "blt .L%=\n\t"
               ".LE%=:\n"
               : "+r"(result) : "r" (last_sp), "r" (heap_end), "r" (stack_pattern) : "ip", "cc");
  return result;
}
