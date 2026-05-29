#include <stdint.h>
#include <stdio.h>
#include "nrf.h"
#include "cpucycles.h"
#include "params.h"
#define SIMEXIT_ADDR 0x20002522
#define SIM_FAIL_ADDR 0x2000252A
#define QINV -3327



const int16_t zetas[128] = {
  -1044,  -758,  -359, -1517,  1493,  1422,   287,   202,
   -171,   622,  1577,   182,   962, -1202, -1474,  1468,
    573, -1325,   264,   383,  -829,  1458, -1602,  -130,
   -681,  1017,   732,   608, -1542,   411,  -205, -1571,
   1223,   652,  -552,  1015, -1293,  1491,  -282, -1544,
    516,    -8,  -320,  -666, -1618, -1162,   126,  1469,
   -853,   -90,  -271,   830,   107, -1421,  -247,  -951,
   -398,   961, -1508,  -725,   448, -1065,   677, -1275,
  -1103,   430,   555,   843, -1251,   871,  1550,   105,
    422,   587,   177,  -235,  -291,  -460,  1574,  1653,
   -246,   778,  1159,  -147,  -777,  1483,  -602,  1119,
  -1590,   644,  -872,   349,   418,   329,  -156,   -75,
    817,  1097,   603,   610,  1322, -1285, -1465,   384,
  -1215,  -136,  1218, -1335,  -874,   220, -1187, -1659,
  -1185, -1530, -1278,   794, -1510,  -854,  -870,   478,
   -108,  -308,   996,   991,   958, -1460,  1522,  1628
};


__attribute__((noinline, used))
static int16_t montgomery_reduce(int32_t a)
{
  int16_t t;

  t = (int16_t)a*QINV;
  t = (a - (int32_t)t*KYBER_Q) >> 16;
  return t;
}

int16_t barrett_reduce(int16_t a) {
  int16_t t;
  const int16_t v = ((1<<26) + KYBER_Q/2)/KYBER_Q;

  t  = ((int32_t)v*a + (1<<25)) >> 26;
  t *= KYBER_Q;
  return a - t;
}

void __attribute__((noinline, used))sim_pass(void)
{
  while(1);
}

void __attribute__((noinline, used))sim_fail(void)
{
  while(1);
}


int __attribute__((noinline, used))bench_start(void)
{
  asm volatile("":::"memory");
  return 0;
}

int __attribute__((noinline, used))bench_end(void)
{
  asm volatile("":::"memory");
  return 0;
}



static inline int16_t mont_reduce_inst(int32_t in)
{
  int16_t out_reg;
  asm volatile(
      ".insn r CUSTOM_0, 7, 0, %[out], %[in], zero\n\t"
      : [out] "=&r" (out_reg)
      : [in] "r" (in)
      : "cc"
  );
  return out_reg; 
}

static inline int16_t barrett_reduce_inst(int16_t in)
{
  int16_t out_reg;
  asm volatile(
      ".insn r CUSTOM_0, 7, 1, %[out], %[in], zero\n\t"
      : [out] "=&r" (out_reg)
      : [in] "r" (in)
      : "cc"
  );
  return out_reg; 
}

int bench_mont_reduce(void)
{
  int16_t std_res, custom_res;
  for(volatile uint32_t i = 1; i < 4096; i++)
  {
    std_res = montgomery_reduce(i);
    custom_res = mont_reduce_inst(i);
    if(custom_res != std_res){
      return -1;
    }
  }
  return 0;
}

int bench_barrett_reduce(void)
{
  int16_t std_res, custom_res;
  bench_start();
  for(volatile uint32_t i = 1; i < 4096; i++)
  {
    int16_t input = (int16_t)i;
    std_res = barrett_reduce(input);
    custom_res = barrett_reduce_inst(input);
    if(custom_res != std_res){
      bench_end();
      return -1;
    }
  }
  return 0;
  bench_end();
}

static int16_t fqmul(int16_t a, int16_t b) {
  return montgomery_reduce((int32_t)a*b);
}

static int16_t custom_fqmul(int16_t a, int16_t b) {
  return mont_reduce_inst((int32_t)a*b);
}

void ntt(int16_t r[256]) {
  unsigned int len, start, j, k;
  int16_t t, zeta;

  k = 1;
  for(len = 128; len >= 2; len >>= 1) {
    for(start = 0; start < 256; start = j + len) {
      zeta = zetas[k++];
      for(j = start; j < start + len; j++) {
        t = fqmul(zeta, r[j + len]);
        r[j + len] = r[j] - t;
        r[j] = r[j] + t;
      }
    }
  } 
}

void custom_ntt(int16_t r[256]) {
  unsigned int len, start, j, k;
  int16_t t, zeta;

  k = 1;
  for(len = 128; len >= 2; len >>= 1) {
    for(start = 0; start < 256; start = j + len) {
      zeta = zetas[k++];
      for(j = start; j < start + len; j++) {
        t = custom_fqmul(zeta, r[j + len]);
        r[j + len] = r[j] - t;
        r[j] = r[j] + t;
      }
    }
  } 
}

int test_ntt(void)
{
  int16_t std_res[256];
  int16_t custom_res[256];
  int16_t input[256];

  for (int i = 0; i < 256; i++)
  {
    input[i] = (int16_t)((i * 17 + 123) % KYBER_Q);

    std_res[i] = input[i];
    custom_res[i] = input[i];
  }
  
  bench_start();
  ntt(std_res);
  bench_end();
  custom_ntt(custom_res);
  for(int i = 0; i < 256; i++)
  {
    if(std_res[i] != custom_res[i])
    {
      return -1;
    }
  }
  return 0; 
}

int bench_intt(void);


int main(void)
{
  int test_fail = bench_barrett_reduce();
  if(test_fail != 0)
  {
    #ifdef PRINT_DEBUG
        printf("Fail!\n");
    #else
        sim_fail();
        /*
        asm volatile(
            "li t0, %0\n"
            "jr t0"
            :
            : "i"(SIM_FAIL_ADDR)
        );
        */
    #endif
  } else { 
  #ifdef PRINT_DEBUG
    printf("Pass\n");
  #else
    sim_pass(); 
    /*
    asm volatile(
        "li t0, %0\n"
        "jr t0"
        :
        : "i"(SIM_EXIT_ADDR)
    );
    */
  #endif
  }

}

void _start(void)
{
  main();
}
