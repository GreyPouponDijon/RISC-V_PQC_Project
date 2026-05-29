#include <stdio.h>
#include <stdint.h>


int main(void) {

  unsigned int len, start, j, k;
  unsigned int stage_counter = 0;


  for(len = 128; len >= 2; len >>= 1) {
    for(start = 0; start < 256; start = j + len) {
      for(j = start; j < start + len; j ++) {
        printf("r[%d], r[%d]\n" ,j, (j + len));

      }
    }
    stage_counter++;
    printf("%d. stage done\n", stage_counter);
  }

  return 0; 
}
