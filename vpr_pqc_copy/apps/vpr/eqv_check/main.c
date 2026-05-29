#include <stdint.h>
#include <stdio.h>
#include "nrf.h"
#include "cpucycles.h"
#include "fips202.h"
#include "fips202_32bit.h"


#define SIM_EXIT_ADDR 0x20002522
#define SIM_FAIL_ADDR 0x2000252A

#define NROUNDS 24

#define ROL(a, offset) ((a << offset) ^ (a >> (64-offset)))

//uint32_t rol64_count, bcop_count, three_xor_count;

uint32_t unopt_cyc, split_cyc, custom_cyc;

static inline void load_into_regs(uint32_t *a, uint32_t *b, uint32_t *c)
{
  asm volatile(
      "lw a0, 0(%0)\n\t"
      "lw a1, 0(%1)\n\t"
      "lw a2, 0(%2)\n\t"
      :
      : "r"(a), "r"(b), "r"(c)
      : "a0", "a1", "a2", "memory"
      );
}

static inline void rol64_lo(uint32_t in_lo, uint32_t in_hi, uint32_t offset, uint32_t *out_lo)
{
  uint32_t lo;
  asm volatile(
      ".insn r4 CUSTOM_0, 0x2, 0x0, %[lo_bits], %[in_lo], %[in_hi], %[offset]\n\t"
        : [lo_bits] "=&r" (lo)
        : [in_lo] "r"(in_lo), [in_hi] "r"(in_hi), [offset] "r"(offset)    
        : "cc"
        );
  *out_lo = lo;
}

static inline void rol64_hi(uint32_t in_lo, uint32_t in_hi, uint32_t offset, uint32_t *out_hi)
{
  uint32_t hi;
  asm volatile(
      ".insn r4 CUSTOM_0, 0x2, 0x1, %[out_hi], %[in_lo], %[in_hi], %[offset]\n\t"
        : [out_hi] "=&r" (hi)
        : [in_lo] "r"(in_lo), [in_hi] "r"(in_hi), [offset] "r"(offset)    
        : "cc"
        );
  *out_hi = hi;
}

static inline void rol64_concat(uint32_t in_lo, uint32_t in_hi, uint32_t offset, uint32_t *out_lo, uint32_t *out_hi)
{
  #ifndef STD_ROL64
  //uint32_t lo, hi;
  asm volatile(
      ".insn r4 CUSTOM_0, 0x2, 0x0, %[lo_bits], %[in_lo], %[in_hi], %[offset]" 
        : [lo_bits] "=&r" (*out_lo)
        : [in_lo] "r"(in_lo), [in_hi] "r"(in_hi), [offset] "r"(offset)    
        : "cc"
        );
  //*out_lo = lo;
  //asm volatile("" ::: "memory");
  asm ("nop");
  asm volatile(
      ".insn r4 CUSTOM_0, 0x2, 0x1, %[out_hi], %[in_lo], %[in_hi], %[offset]"
        : [out_hi] "=&r" (*out_hi)
        : [in_lo] "r"(in_lo), [in_hi] "r"(in_hi), [offset] "r"(offset)    
        : "cc"
        );
  //*out_hi = hi;
  #else
  uint64_t concat_val = ((uint64_t)in_hi << 32) | in_lo;
  uint64_t rot_val = (concat_val << offset) ^ (concat_val >> (64-offset));

  *out_hi = (uint32_t)(rot_val >> 32);
  *out_lo = (uint32_t)rot_val;
  #endif
}

/* Keccak round constants */
static const uint64_t KeccakF_RoundConstants[NROUNDS] = {
  (uint64_t)0x0000000000000001ULL,
  (uint64_t)0x0000000000008082ULL,
  (uint64_t)0x800000000000808aULL,
  (uint64_t)0x8000000080008000ULL,
  (uint64_t)0x000000000000808bULL,
  (uint64_t)0x0000000080000001ULL,
  (uint64_t)0x8000000080008081ULL,
  (uint64_t)0x8000000000008009ULL,
  (uint64_t)0x000000000000008aULL,
  (uint64_t)0x0000000000000088ULL,
  (uint64_t)0x0000000080008009ULL,
  (uint64_t)0x000000008000000aULL,
  (uint64_t)0x000000008000808bULL,
  (uint64_t)0x800000000000008bULL,
  (uint64_t)0x8000000000008089ULL,
  (uint64_t)0x8000000000008003ULL,
  (uint64_t)0x8000000000008002ULL,
  (uint64_t)0x8000000000000080ULL,
  (uint64_t)0x000000000000800aULL,
  (uint64_t)0x800000008000000aULL,
  (uint64_t)0x8000000080008081ULL,
  (uint64_t)0x8000000000008080ULL,
  (uint64_t)0x0000000080000001ULL,
  (uint64_t)0x8000000080008008ULL
};


static inline void rv_bcop(uint32_t rs1_lo, uint32_t rs1_hi, uint32_t rs2_lo, uint32_t rs2_hi, uint32_t rs3_lo, uint32_t rs3_hi, uint32_t *rd_lo, uint32_t *rd_hi)
{
  #ifndef STD_BCOP
  asm volatile(
  ".insn r4 CUSTOM_0, 0x1, 0x0, %[d_lo], %[a_lo], %[b_lo], %[c_lo]\n\t"
  "nop\n\t"
  ".insn r4 CUSTOM_0, 0x1, 0x0, %[d_hi],%[a_hi], %[b_hi], %[c_hi]\n\t"
  : [d_lo] "=&r" (*rd_lo), [d_hi] "=&r" (*rd_hi)
  : [a_lo] "r"(rs1_lo), [b_lo] "r"(rs2_lo), [c_lo] "r"(rs3_lo),
    [a_hi] "r"(rs1_hi), [b_hi] "r"(rs2_hi), [c_hi] "r"(rs3_hi)
  : "cc"
  ); 
  #else
  *rd_lo = rs1_lo ^ ((~rs2_lo) & rs3_lo);
  *rd_hi = rs1_hi ^ ((~rs2_hi) & rs3_hi);
  #endif  
}

static inline void rv_3xor(uint32_t rs1, uint32_t rs2, uint32_t rs3, uint32_t *rd)
{
  #ifndef STD_3XOR
  asm volatile(
  ".insn r4 CUSTOM_0, 0x3, 0x0, %[rd], %[rs1], %[rs2], %[rs3]\n\t"
  : [rd] "=&r" (*rd)
  : [rs1] "r"(rs1), [rs2] "r"(rs2), [rs3] "r"(rs3)
  : "cc"
  );
  #else
  *rd = rs1 ^ rs2 ^ rs3;
  #endif
}


/*
static inline void rv_bcop(uint32_t rs1_lo, uint32_t rs1_hi, uint32_t rs2_lo, uint32_t rs2_hi, uint32_t rs3_lo, uint32_t rs3_hi, uint32_t *rd_lo, uint32_t *rd_hi)
{
  uint32_t out_lo, out_hi;
  asm volatile(
  ".insn r4 CUSTOM_0, 0x1, 0x0, %[d_lo], %[a_lo], %[b_lo], %[c_lo]\n\t"
  : [d_lo] "=&r" (out_lo)
  : [a_lo] "r"(rs1_lo), [b_lo] "r"(rs2_lo), [c_lo] "r"(rs3_lo)    
  : "cc"
  );
  asm volatile("" ::: "memory");
  asm ("nop");
  asm volatile(
  ".insn r4 CUSTOM_0, 0x1, 0x0, %[d_hi],%[a_hi], %[b_hi], %[c_hi]\n\t"
  : [d_hi] "=&r"(out_hi) 
  : [a_hi] "r"(rs1_hi), [b_hi] "r"(rs2_hi), [c_hi] "r"(rs3_hi)
  : "cc"
  );

  *rd_lo = out_lo; 
  *rd_hi = out_hi;
}
*/
static void rv_bcop_half(uint32_t rs1_lo, uint32_t rs2_lo,  uint32_t rs3_lo,  uint32_t *rd_lo)
{
  uint32_t out_lo;
    asm volatile(
  ".insn r CUSTOM_0, 0x1, 0x0, %[d_lo], %[a_lo], %[b_lo], %[c_lo]\n\t" 
  : [d_lo] "=&r" (out_lo)
  : [a_lo] "r"(rs1_lo), [b_lo] "r"(rs2_lo), [c_lo] "r"(rs3_lo) 
  : "cc"
  );

  *rd_lo = out_lo; 
}

int test_rol(void)
{
  uint64_t rol_result, rol_concat_result;
  uint32_t temp_hi, temp_lo;
  for(int j = 1; j < 64; j++)
  {
    for(int i = 0; i < NROUNDS; i++)
    {
      rol_result = ROL(KeccakF_RoundConstants[i], j);
      uint32_t i_hi = (uint32_t)(KeccakF_RoundConstants[i] >> 32);
      uint32_t i_lo = (uint32_t)KeccakF_RoundConstants[i];
      rol64_concat(i_lo, i_hi, j, &temp_lo, &temp_hi);
      //rol64_hi(i_lo, i_hi, j, &temp_hi);
      //asm("nop");
      //rol64_lo(i_lo, i_hi, j, &temp_lo); 

      //rol_concat_result = ((uint64_t)temp_hi << 32) | temp_lo;
      uint32_t reg_hi, reg_lo;
      reg_hi = (uint32_t)(rol_result >> 32);
      reg_lo = (uint32_t)rol_result;
      #ifdef PRINT_DEBUG
      printf("Start Val: %016x, Regular rol: %016x, Concat and rol: %016x, Rotate offset %d\n", i, rol_result, rol_concat_result, j);
      #endif
      //printf("Concat and rol: %08x\n", rol_concat_result);
      //printf("Rotate offset: %d\n", j);
      if((temp_hi != reg_hi) || (temp_lo != reg_lo)){
        #ifdef PRINT_DEBUG
        printf("Fail!\n");
        #else
        return -1;
        #endif
      }
    }
  }
 #ifdef PRINT_DEBUG
  printf("Pass\n"); 
 #else
  return 0;
  #endif

}

int test_minimal_rol()
{
  uint32_t lo, hi, offset;
  lo = 0xCAFEBABE;
  hi = 0xACABACAB;
  offset = 37;

  uint32_t custom_lo, custom_hi;
  uint32_t std_lo, std_hi;
  
  //rol64_hi(lo, hi, offset, &custom_hi);
  //asm("nop");
  //rol64_lo(lo, hi, offset, &custom_lo); 

  
 
  volatile uint64_t concat_val = ((uint64_t)hi << 32) | lo;
  volatile uint64_t rot_val = (concat_val << offset) ^ (concat_val >> (64-offset));

  std_hi = (uint32_t)(rot_val >> 32);
  std_lo = (uint32_t)rot_val;

  rol64_concat(lo, hi, offset, &custom_lo, &custom_hi);

  if ((std_hi != custom_hi) || (std_lo != custom_lo))
  {
    return -1;
  } else {
    return 0;
  }

}

int test_minimal_bcop()
{
  uint32_t a_lo, b_lo, c_lo;
  uint32_t a_hi, b_hi, c_hi;
  uint32_t d_lo = 0xFAFAFAFA;
  uint32_t d_hi = 0xACABACAB;
  volatile uint32_t correct_d_lo, correct_d_hi;
  uint32_t d1_lo = 0xCAFEBABE;
  uint32_t d1_hi = 0xDEADBEEF;

  a_lo = 1;
  b_lo = 2;
  c_lo = 3;
  a_hi = 4;
  b_hi = 5;
  c_hi = 6;
  correct_d_lo = a_lo ^ ((~b_lo) & c_lo); 
  correct_d_hi = a_hi ^ ((~b_hi) & c_hi);

  //rv_bcop_half(a_lo, b_lo, c_lo, &d_lo);
  //rv_bcop_half(a_hi, b_hi, c_hi, &d_hi);

  rv_bcop(a_lo, a_hi, b_lo, b_hi, c_lo, c_hi, &d_lo, &d_hi);

  if (d_lo != correct_d_lo || d_hi != correct_d_hi)  {
    return -1;
  } else {
    return 0;
  }
}

#pragma gcc push_options
#pragma gcc optimize ("O0")
int test_bcop()
{
  volatile uint64_t a, b, c;
  uint32_t a_lo, b_lo, c_lo, d_lo;
  uint32_t a_hi, b_hi, c_hi, d_hi;
  uint64_t unopt_res, split_res, custom_res;
  uint32_t split_res_lo, split_res_hi;
  uint32_t custom_res_lo, custom_res_hi;
  uint32_t cnt1, cnt2;
  volatile uint32_t dummy;
  int test_fail = 0;
  
  for(int i = 0; i < 8; i++)
  { 
    a = KeccakF_RoundConstants[i];
    b = KeccakF_RoundConstants[i+1];
    c = KeccakF_RoundConstants[i+2];
    a_hi = (uint32_t)(a >> 32);
    a_lo = (uint32_t)a;
    b_hi = (uint32_t)(b >> 32);
    b_lo = (uint32_t)b;
    c_hi = (uint32_t)(c >> 32);
    c_lo = (uint32_t)c;
    
    //cnt1 = cpucycles();
    unopt_res = a ^ ((~b) & c);
    //cnt2 = cpucycles();
    //unopt_cyc = cnt2 - cnt1;

    //cnt1 = cpucycles();
    split_res_lo = a_lo ^ ((~b_lo) & c_lo);
    split_res_hi = a_hi ^ ((~b_hi) & c_hi);
    //cnt2 = cpucycles();
    //split_cyc = cnt2 - cnt1;

    //cnt1 = cpucycles();
    rv_bcop(a_lo, a_hi,  b_lo, b_hi,  c_lo, c_hi, &d_lo, &d_hi);
    custom_res_lo = d_lo;
    custom_res_hi = d_hi;
    //cnt2 = cpucycles();
    //custom_cyc = cnt2 -cnt1; 
    split_res = ((uint64_t)split_res_hi << 32) | split_res_lo;
    custom_res = ((uint64_t)custom_res_hi << 32) | custom_res_lo;
    //printf("%016x, %016x, %016x", unopt_res, split_res, custom_res);
    if((unopt_res != custom_res) ||(unopt_res != split_res))
    {
      test_fail = -1;
    } else {
      dummy = i; 
    }
  }
  //load_into_regs()
  return test_fail;
  
}
#pragma gcc pop_options

int bench_bcop()
{
  uint64_t a = 0x9e3779b97f4a7c15ULL;
  uint64_t b = 0xbf58476d1ce4e5b9ULL;
  uint64_t c = 0x94d049bb133111ebULL;
  uint32_t a_hi = (uint32_t)(a >> 32);
  uint32_t a_lo = (uint32_t)a;
  uint32_t b_hi = (uint32_t)(b >> 32);
  uint32_t b_lo = (uint32_t)b;
  uint32_t c_hi = (uint32_t)(c >> 32);
  uint32_t c_lo = (uint32_t)c;
  uint32_t d_lo, d_hi;
  rv_bcop(a_lo, a_hi,  b_lo, b_hi,  c_lo, c_hi, &d_lo, &d_hi);
  uint32_t custom_res_lo = d_lo;
  uint32_t custom_res_hi = d_hi;

  return 0;
}

int bench_keccak()
{
  uint64_t state_ref[25];
  uint32_t state_opt[50];

  for(int i = 0; i<25; i++){
    state_ref[i] = 0xFFFFFFFFFFFFFFFF ^ i;
    state_opt[i * 2] = (uint32_t)(state_ref[i]);
    state_opt[i * 2 + 1] = (uint32_t)(state_ref[i] >> 32);
  }

  KeccakF1600_StatePermute_32bit(state_opt);
  KeccakF1600_StatePermute(state_ref);

  uint32_t state_ref_split[50];

  for (int i = 0; i < 25; i += 1){
    state_ref_split[i*2] = (uint32_t)state_ref[i];
    state_ref_split[i*2 + 1] = (uint32_t)(state_ref[i] >> 32);
  }

  for(int i = 0; i < 50; i++){
      if(state_ref_split[i] != state_opt[i]){
        //printf("%016x, %016x, %d", state_ref_split[i], state_opt[i], i);
        return -1;
      }
  }

  return 0;

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

int run_32keccak()
{
  uint32_t state[50];
  uint32_t state_start[50];
  for(uint32_t i = 0; i<50; i++){
    state[i] = 0x1234567812345678 ^ i;
    state_start[i] = state[i];
  }
  bench_start();
  
  KeccakF1600_StatePermute_32bit(state);
  bench_end();
  
  for(int i = 0; i < 50; i++){
    if(state[i] == state_start[i]){
      return -1;
    }
  }
  return 0;
}


int run_64keccak()
{
  uint64_t state[25];
  uint64_t state_start[25];
  for(uint64_t i = 0; i<25; i++){
    state[i] = 0x1234567812345678 ^ i;
    state_start[i] = state[i];
  }
  KeccakF1600_StatePermute(state);
  for(int i = 0; i < 25; i++){
    if(state[i] == state_start[i]){
      return -1;
    }
  }
  return 0;
}





int test_3xor()
{
  uint32_t custom_res;
  volatile uint32_t std_res;
  uint32_t a, b, c;
  a = 0xACABACAB;
  b = 0xCAFEBABE;
  c = 0x12345678;

  rv_3xor(a, b, c, &custom_res);
  std_res = a ^ b ^ c;

  if(custom_res != std_res)
  {
    return -1;
  } else
  {
    return 0;
  }

}






int main(void)
{
  cpucycles_init();
  int test_fail = run_32keccak();
  load_into_regs(&three_xor_avg_cyc, &rol64_avg_cyc, &bcop_avg_cyc);
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
