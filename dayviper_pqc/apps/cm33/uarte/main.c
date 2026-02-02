#include <stdio.h>

int main(void) {

    printf("Hello CM33\r\n");
    while (1) {
        __asm volatile ("wfi" ::: "memory");
    };
    
    return 0;
}
