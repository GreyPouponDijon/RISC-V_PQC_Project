#include <stdio.h>

int main(void) {

    printf("Hello VPR\r\n");
    while (1) {
        __asm volatile ("wfi" ::: "memory");
    };
    
    return 0;
}

void _start(void) {
    main();
}
