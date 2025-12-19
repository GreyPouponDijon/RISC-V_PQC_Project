#include <stdio.h>
#include <stdint.h>
#include <stddef.h>

static inline uint32_t calc_percentage(uint32_t n,
                                       uint32_t cyc,
                                       uint32_t total,
                                       uint32_t n_tests)
{
    uint64_t num, den;

    if (total == 0 || n_tests == 0) return 0;

    num = (uint64_t)n * (uint64_t)cyc * 100ULL;
    den = (uint64_t)total * (uint64_t)n_tests;

    return (uint32_t)((num + den / 2) / den);
}

int main()
{
  uint32_t n = 27;
  uint32_t cyc = 16719;
  uint32_t n_tests = 1;
  uint32_t total = 914451;
  uint32_t percentage = calc_percentage(n, cyc, total, n_tests);
  printf("%d\n", percentage);
  
  return 0;
}
