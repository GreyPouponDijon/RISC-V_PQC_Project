#include <stdint.h>
#include <stdio.h>
#include <stddef.h>
#include "nrf_config.h"
#include "nrf.h"
#include "../sign.h"
#include "../poly.h"
#include "../polyvec.h"
#include "../params.h"
#include "cpucycles.h"
#include "speed_print.h"
#include "stack_usage.h"

#define NTESTS 10

extern int n_statepermute = 0;
extern int n_ntt = 0;
extern int n_invntt = 0;
extern int statepermute_cyc = 0;
extern int ntt_cyc = 0;
extern int inv_ntt_cyc = 0;
size_t stack_used = 0;

uint64_t t[NTESTS];

void print_stuff(void)
{
  print_calls("State Permute calls: ", n_statepermute, NTESTS);
  print_calls("NTT calls: ", n_ntt, NTESTS);
  print_calls("INVNTT calls: ", n_invntt, NTESTS);
  n_statepermute = 0; 
  n_ntt = 0;
  n_invntt = 0;
  print_cycles("State Permute Cycles: ", statepermute_cyc, NTESTS);
  print_cycles("NTT Cycles: ", ntt_cyc, NTESTS);
  print_cycles("INVNTT Cycles: ", inv_ntt_cyc, NTESTS);
  DWT->CYCCNT = 0;
  stack_used = check_stack();
  printf("Stack Used: %d\n", (int)stack_used);
}

int main(void)
{
  cpucycles_init();
  nrf_config_init();
  printf("CYCCNT initalized and Cache Enabled\n");
  unsigned int i;
  size_t siglen;
  uint8_t pk[CRYPTO_PUBLICKEYBYTES];
  uint8_t sk[CRYPTO_SECRETKEYBYTES];
  uint8_t sig[CRYPTO_BYTES];
  uint8_t seed[CRHBYTES];
  polyvecl mat[DILITHIUM_K];
  poly *a = &mat[0].vec[0];
  poly *b = &mat[0].vec[1];
  poly *c = &mat[0].vec[2];
  
  /*
  DWT->CYCCNT = 0;
  for(i = 0; i < NTESTS; ++i) {
    t[i] = cpucycles();
    polyvec_matrix_expand(mat, seed);
  }
  print_results("polyvec_matrix_expand:", t, NTESTS);
  print_stuff();
  for(i = 0; i < NTESTS; ++i) {
    t[i] = cpucycles();
    poly_uniform_eta(a, seed, 0);
  }
  print_results("poly_uniform_eta:", t, NTESTS);
  print_stuff();
  for(i = 0; i < NTESTS; ++i) {
    t[i] = cpucycles();
    poly_uniform_gamma1(a, seed, 0);
  }
  print_results("poly_uniform_gamma1:", t, NTESTS);
  print_stuff();
  for(i = 0; i < NTESTS; ++i) {
    t[i] = cpucycles();
    poly_ntt(a);
  }
  print_results("poly_ntt:", t, NTESTS);
  print_stuff();
  for(i = 0; i < NTESTS; ++i) {
    t[i] = cpucycles();
    poly_invntt_tomont(a);
  }
  print_results("poly_invntt_tomont:", t, NTESTS);
  print_stuff();
  for(i = 0; i < NTESTS; ++i) {
    t[i] = cpucycles();
    poly_pointwise_montgomery(c, a, b);
  }
  print_results("poly_pointwise_montgomery:", t, NTESTS);
  print_stuff();
  for(i = 0; i < NTESTS; ++i) {
    t[i] = cpucycles();
    poly_challenge(c, seed);
  }
  print_results("poly_challenge:", t, NTESTS);
  print_stuff();
  */

  fill_stack();
  
  for(i = 0; i < NTESTS; ++i) {
    t[i] = cpucycles();
    crypto_sign_keypair(pk, sk);
  }  
  print_results("Keypair:", t, NTESTS);
  print_stuff();

  fill_stack();

  for(i = 0; i < NTESTS; ++i) {
    t[i] = cpucycles();
    crypto_sign_signature(sig, &siglen, sig, CRHBYTES, NULL, 0, sk);
  }
  print_results("Sign:", t, NTESTS);
  print_stuff();

  fill_stack();

  for(i = 0; i < NTESTS; ++i) {
    t[i] = cpucycles();
    crypto_sign_verify(sig, CRYPTO_BYTES, sig, CRHBYTES, NULL, 0, pk);
  }
  print_results("Verify:", t, NTESTS);
  print_stuff();
  return 0;
}
