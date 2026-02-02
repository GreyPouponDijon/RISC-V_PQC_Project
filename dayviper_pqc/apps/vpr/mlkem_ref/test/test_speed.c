#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "../kem.h"
#include "../params.h"
#include "../indcpa.h"
#include "../polyvec.h"
#include "../poly.h"
#include "../randombytes.h"
#include "cpucycles.h"
#include "speed_print.h"
#include "nrf.h"
#include "nrf_vpr_csr.h"
#include "globals.h"

#define NTESTS 10

int n_statepermute = 0;
int n_ntt = 0;
int n_invntt = 0;
int statepermute_cyc = 0;
int ntt_cyc = 0;
int inv_ntt_cyc = 0;
int n_poly_compress = 0;
int n_poly_decompress = 0;
int poly_compress_cyc = 0;
int poly_decompress_cyc = 0;
int n_poly_add = 0;
int n_poly_sub = 0;
int n_basemul = 0;
int basemul_cyc = 0;
int poly_sub_cyc = 0;
int poly_add_cyc = 0;
int n_poly_cbd_eta2 = 0;
int poly_cbd_eta2_cyc = 0;
int n_poly_cbd_eta1 = 0;
int poly_cbd_eta1_cyc = 0;
int n_barrett = 0;
int n_montgomery = 0;
int barrett_cyc = 0;
int montgomery_cyc = 0;
int n_polyvec_compress = 0;
int n_polyvec_decompress = 0;
int polyvec_compress_cyc = 0;
int polyvec_decompress_cyc = 0;
int n_shake256 = 0;
int n_shake128 = 0;
int shake256_cyc = 0;
int shake128_cyc = 0;
int sha3_256_cyc = 0;
int n_sha3_256 = 0;
int n_sha3_512 = 0;
int sha3_512_cyc = 0;
int n_gen_matrix = 0;
int gen_matrix_cyc = 0;
int rkprf_cyc = 0;
int n_rkprf = 0;
int n_rej_uniform = 0;
int rej_uniform_cyc = 0;


uint64_t t[NTESTS];
uint8_t seed[KYBER_SYMBYTES] = {0};


static inline int calc_percentage(uint32_t n,
                                       uint32_t cyc,
                                       uint32_t total,
                                       uint32_t n_tests)
{
    uint64_t num, den;
    uint32_t benchmark_cyc = 65;

    if (total == 0 || n_tests == 0) return 0;
    //uint32_t norm_cyc = cyc - (benchmark_cyc * n);

    num = (uint64_t)n * (uint64_t)cyc * 100ULL;
    den = (uint64_t)total * (uint64_t)n_tests;

    return (int)((num + den / 2) / den);
}

void reset_vals()
{
/* ---- Reset all counters ---- */
    n_statepermute = 0;
    n_ntt = 0;
    n_invntt = 0;
    statepermute_cyc = 0;
    ntt_cyc = 0;
    inv_ntt_cyc = 0;

    n_poly_compress = 0;
    n_poly_decompress = 0;
    poly_compress_cyc = 0;
    poly_decompress_cyc = 0;

    n_poly_add = 0;
    n_poly_sub = 0;

    n_poly_cbd_eta1 = 0;
    n_poly_cbd_eta2 = 0;
    n_basemul = 0;
    poly_cbd_eta1_cyc = 0;
    poly_cbd_eta2_cyc = 0;
    basemul_cyc = 0;

    n_barrett = 0;
    n_montgomery = 0;
    barrett_cyc = 0;
    montgomery_cyc = 0;

    n_polyvec_compress = 0;
    n_polyvec_decompress = 0;
    polyvec_compress_cyc = 0;
    polyvec_decompress_cyc = 0;

    n_shake256 = 0;
    n_shake128 = 0;
    shake256_cyc = 0;
    shake128_cyc = 0;
    sha3_256_cyc = 0;
    n_sha3_256 = 0;
    n_sha3_512 = 0;
    sha3_512_cyc = 0;
    n_gen_matrix = 0;
    gen_matrix_cyc = 0;
    rej_uniform_cyc = 0;
    n_rej_uniform = 0;
}


void print_stuff(int total, uint32_t n_tests)
{

    print_calls("SHAKE128 calls: ", n_shake128, n_tests);
    print_cycles("SHAKE128 cycles: ", shake128_cyc, n_tests);
    printf("SHAKE128 %%: %d\n",
           calc_percentage(n_shake128, shake128_cyc, total, n_tests));

    print_calls("SHAKE256 calls: ", n_shake256, n_tests);
    print_cycles("SHAKE256 cycles: ", shake256_cyc, n_tests);
    printf("SHAKE256 %%: %d\n",
           calc_percentage(n_shake256, shake256_cyc, total, n_tests));

    print_calls("sha3_256 calls: ", n_sha3_256, n_tests);
    print_cycles("sha3_256 cycles: ", sha3_256_cyc, n_tests);
    printf("sha3_256 %%: %d\n",
           calc_percentage(n_sha3_256, sha3_256_cyc, total, n_tests));

    print_calls("sha3_512 calls: ", n_sha3_512, n_tests);
    print_cycles("sha3_512 cycles: ", sha3_512_cyc, n_tests);
    printf("sha3_512 %%: %d\n",
           calc_percentage(n_sha3_512, sha3_512_cyc, total, n_tests));

    print_calls("gen_matrix calls: ", n_gen_matrix, n_tests);
    print_cycles("gen_matrix cycles: ", gen_matrix_cyc, n_tests);
    printf("gen_matrix %%: %d\n",
           calc_percentage(n_gen_matrix, gen_matrix_cyc, total, n_tests));

    



    /* ---- State permute / NTT ---- */
    print_calls("State Permute calls: ", n_statepermute, n_tests);
    print_cycles("State Permute cycles: ", statepermute_cyc, n_tests);
    printf("State Permute %%: %d\n",
           calc_percentage(n_statepermute, statepermute_cyc, total, n_tests));

    print_calls("NTT calls: ", n_ntt, n_tests);
    print_cycles("NTT cycles: ", ntt_cyc, n_tests);
    printf("NTT %%: %d\n",
           calc_percentage(n_ntt, ntt_cyc, total, n_tests));

    print_calls("INVNTT calls: ", n_invntt, n_tests);
    print_cycles("INVNTT cycles: ", inv_ntt_cyc, n_tests);
    printf("INVNTT %%: %d\n",
           calc_percentage(n_invntt, inv_ntt_cyc, total, n_tests));

    /* ---- Polynomial ops ---- */
    print_calls("Poly compress calls: ", n_poly_compress, n_tests);
    print_cycles("Poly compress cycles: ", poly_compress_cyc, n_tests);
    printf("Poly compress %%: %d\n",
           calc_percentage(n_poly_compress, poly_compress_cyc, total, n_tests));

    print_calls("Poly decompress calls: ", n_poly_decompress, n_tests);
    print_cycles("Poly decompress cycles: ", poly_decompress_cyc, n_tests);
    printf("Poly decompress %%: %d\n",
           calc_percentage(n_poly_decompress, poly_decompress_cyc, total, n_tests));

    print_calls("Poly add calls: ", n_poly_add, n_tests);
    print_cycles("Poly add cycles: ", poly_add_cyc, n_tests);
    printf("Poly add %%: %d\n",
           calc_percentage(n_poly_add, poly_add_cyc, total, n_tests));

    print_calls("Poly sub calls: ", n_poly_sub, n_tests);
    print_calls("Poly sub calls: ", n_poly_sub, n_tests);
    print_cycles("Poly sub cycles: ", poly_sub_cyc, n_tests);
    printf("Poly sub %%: %d\n",
           calc_percentage(n_poly_sub, poly_sub_cyc, total, n_tests));

    /* ---- Base multiplication ---- */
    print_calls("Basemul calls: ", n_basemul, n_tests);
    print_cycles("Basemul cycles: ", basemul_cyc, n_tests);
    printf("Basemul %%: %d\n",
           calc_percentage(n_basemul, basemul_cyc, total, n_tests));

    /* ---- CBD sampling ---- */
    print_calls("CBD eta1 calls: ", n_poly_cbd_eta1, n_tests);
    print_cycles("CBD eta1 cycles: ", poly_cbd_eta1_cyc, n_tests);
    printf("CBD eta1 %%: %d\n",
           calc_percentage(n_poly_cbd_eta1, poly_cbd_eta1_cyc, total, n_tests));

    print_calls("CBD eta2 calls: ", n_poly_cbd_eta2, n_tests);
    print_cycles("CBD eta2 cycles: ", poly_cbd_eta2_cyc, n_tests);
    printf("CBD eta2 %%: %d\n",
           calc_percentage(n_poly_cbd_eta2, poly_cbd_eta2_cyc, total, n_tests));

    /* ---- Modular arithmetic ---- */
    print_calls("Barrett calls: ", n_barrett, n_tests);
    print_cycles("Barrett cycles: ", barrett_cyc, n_tests);
    printf("Barrett %%: %d\n",
           calc_percentage(n_barrett, barrett_cyc, total, n_tests));

    print_calls("Montgomery calls: ", n_montgomery, n_tests);
    print_cycles("Montgomery cycles: ", montgomery_cyc, n_tests);
    printf("Montgomery %%: %d\n",
           calc_percentage(n_montgomery, montgomery_cyc, total, n_tests));

    /* ---- Polyvec ---- */
    print_calls("Polyvec compress calls: ", n_polyvec_compress, n_tests);
    print_cycles("Polyvec compress cycles: ", polyvec_compress_cyc, n_tests);
    printf("Polyvec compress %%: %d\n",
           calc_percentage(n_polyvec_compress, polyvec_compress_cyc, total, n_tests));

    print_calls("Polyvec decompress calls: ", n_polyvec_decompress, n_tests);
    print_cycles("Polyvec decompress cycles: ", polyvec_decompress_cyc, n_tests);
    printf("Polyvec decompress %%: %d\n",
           calc_percentage(n_polyvec_decompress, polyvec_decompress_cyc, total, n_tests));


    print_calls("rkprf calls: ", n_rkprf, n_tests);
    print_cycles("rkprf cycles: ", rkprf_cyc, n_tests);
    printf("rkprf %%: %d\n",
           calc_percentage(n_rkprf, rkprf_cyc, total, n_tests));


    print_calls("rej_uniform calls: ", n_rej_uniform, n_tests);
    print_cycles("rej_uniform cycles: ", rej_uniform_cyc, n_tests);
    printf("rej_uniform %%: %d\n",
           calc_percentage(n_rej_uniform, rej_uniform_cyc, total, n_tests));
    
    reset_vals();
}


int main(void)
{
  cpucycles_init();
 
  printf("Cpu Cycles Initalized and Cache Enabled\n");
  int result = 0;
  unsigned int i;
  uint8_t pk[CRYPTO_PUBLICKEYBYTES];
  uint8_t sk[CRYPTO_SECRETKEYBYTES];
  uint8_t ct[CRYPTO_CIPHERTEXTBYTES];
  uint8_t key[CRYPTO_BYTES];
  uint8_t coins32[KYBER_SYMBYTES];
  uint8_t coins64[2*KYBER_SYMBYTES];
  polyvec matrix[KYBER_K];
  poly ap;

  randombytes(coins32, KYBER_SYMBYTES);
  randombytes(coins64, 2*KYBER_SYMBYTES);
  for(i=0;i<NTESTS;i++) {
    t[i] = cpucycles();
    gen_matrix(matrix, seed, 0);
  }
  print_results("gen_a: ", t, NTESTS);

  for(i=0;i<NTESTS;i++) {
    t[i] = cpucycles();
    poly_getnoise_eta1(&ap, seed, 0);
  }
  print_results("poly_getnoise_eta1: ", t, NTESTS);

  for(i=0;i<NTESTS;i++) {
    t[i] = cpucycles();
    poly_getnoise_eta2(&ap, seed, 0);
  }
  print_results("poly_getnoise_eta2: ", t, NTESTS);

  for(i=0;i<NTESTS;i++) {
    t[i] = cpucycles();
    poly_ntt(&ap);
  }
  print_results("NTT: ", t, NTESTS);

  for(i=0;i<NTESTS;i++) {
    t[i] = cpucycles();
    poly_invntt_tomont(&ap);
  }
  print_results("INVNTT: ", t, NTESTS);

  for(i=0;i<NTESTS;i++) {
    t[i] = cpucycles();
    polyvec_basemul_acc_montgomery(&ap, &matrix[0], &matrix[1]);
  }
  print_results("polyvec_basemul_acc_montgomery: ", t, NTESTS);

  for(i=0;i<NTESTS;i++) {
    t[i] = cpucycles();
    poly_tomsg(ct,&ap);
  }
  print_results("poly_tomsg: ", t, NTESTS);

  for(i=0;i<NTESTS;i++) {
    t[i] = cpucycles();
    poly_frommsg(&ap,ct);
  }
  print_results("poly_frommsg: ", t, NTESTS);

  for(i=0;i<NTESTS;i++) {
    t[i] = cpucycles();
    poly_compress(ct,&ap);
  }
  print_results("poly_compress: ", t, NTESTS);

  for(i=0;i<NTESTS;i++) {
    t[i] = cpucycles();
    poly_decompress(&ap,ct);
  }
  print_results("poly_decompress: ", t, NTESTS);

  for(i=0;i<NTESTS;i++) {
    t[i] = cpucycles();
    polyvec_compress(ct,&matrix[0]);
  }
  print_results("polyvec_compress: ", t, NTESTS);

  for(i=0;i<NTESTS;i++) {
    t[i] = cpucycles();
    polyvec_decompress(&matrix[0],ct);
  }
  print_results("polyvec_decompress: ", t, NTESTS);

  for(i=0;i<NTESTS;i++) {
    t[i] = cpucycles();
    indcpa_keypair_derand(pk, sk, coins32);
  }
  print_results("indcpa_keypair: ", t, NTESTS);

  for(i=0;i<NTESTS;i++) {
    t[i] = cpucycles();
    indcpa_enc(ct, key, pk, seed);
  }
  print_results("indcpa_enc: ", t, NTESTS);

  for(i=0;i<NTESTS;i++) {
    t[i] = cpucycles();
    indcpa_dec(key, ct, sk);
  }
  print_results("indcpa_dec: ", t, NTESTS);
  nrf_csr_write(VPRCSR_MCYCLE, 0);
  reset_vals();

  for(i=0;i<NTESTS;i++) {
    t[i] = cpucycles();
    crypto_kem_keypair_derand(pk, sk, coins64);
  }
  result = print_results("kyber_keypair_derand: ", t, NTESTS);
   /*
  print_calls("State Permute calls: ", n_statepermute, NTESTS);
  print_calls("NTT calls: ", n_ntt, NTESTS);
  print_calls("INVNTT calls: ", n_invntt, NTESTS);
  n_statepermute = 0; 
  n_ntt = 0;
  n_invntt = 0;
  print_cycles("State Permute Cycles: ", statepermute_cyc, NTESTS);
  print_cycles("NTT Cycles: ", ntt_cyc, NTESTS);
  print_cycles("INVNTT Cycles: ", inv_ntt_cyc, NTESTS);
  */
  print_stuff(result, NTESTS);

  nrf_csr_write(VPRCSR_MCYCLE, 0);
  for(i=0;i<NTESTS;i++) {
    t[i] = cpucycles();
    crypto_kem_keypair(pk, sk);
  }
  result = print_results("kyber_keypair: ", t, NTESTS);
  /*
  print_calls("State Permute calls: ", n_statepermute, NTESTS);
  print_calls("NTT calls: ", n_ntt, NTESTS);
  print_calls("INVNTT calls: ", n_invntt, NTESTS);
  n_statepermute = 0; 
  n_ntt = 0;
  n_invntt = 0;
  */
  print_stuff(result, NTESTS);

  nrf_csr_write(VPRCSR_MCYCLE, 0);  /*
  print_cycles("State Permute Cycles: ", statepermute_cyc, NTESTS);
  print_cycles("NTT Cycles: ", ntt_cyc, NTESTS);
  print_cycles("INVNTT Cycles: ", inv_ntt_cyc, NTESTS);
  */
  for(i=0;i<NTESTS;i++) {
    t[i] = cpucycles();
    crypto_kem_enc_derand(ct, key, pk, coins32);
  }
  result = print_results("kyber_encaps_derand: ", t, NTESTS);
  /*
  print_calls("State Permute calls: ", n_statepermute, NTESTS);
  print_calls("NTT calls: ", n_ntt, NTESTS);
  print_calls("INVNTT calls: ", n_invntt, NTESTS);
  n_statepermute = 0; 
  n_ntt = 0;
  n_invntt = 0;
  */
  print_stuff(result, NTESTS);
  nrf_csr_write(VPRCSR_MCYCLE, 0);   
  /*
  print_cycles("State Permute Cycles: ", statepermute_cyc, NTESTS);
  print_cycles("NTT Cycles: ", ntt_cyc, NTESTS);
  print_cycles("INVNTT Cycles: ", inv_ntt_cyc, NTESTS);
  */
  for(i=0;i<NTESTS;i++) {
    t[i] = cpucycles();
    crypto_kem_enc(ct, key, pk);
  }
  result = print_results("kyber_encaps: ", t, NTESTS);
  /*
  print_calls("State Permute calls: ", n_statepermute, NTESTS);
  print_calls("NTT calls: ", n_ntt, NTESTS);
  print_calls("INVNTT calls: ", n_invntt, NTESTS);
  n_statepermute = 0; 
  n_ntt = 0;
  n_invntt = 0;
  */
  print_stuff(result, NTESTS);
  nrf_csr_write(VPRCSR_MCYCLE, 0);
  
  /*
  print_cycles("State Permute Cycles: ", statepermute_cyc, NTESTS);
  print_cycles("NTT Cycles: ", ntt_cyc, NTESTS);
  print_cycles("INVNTT Cycles: ", inv_ntt_cyc, NTESTS); 
  */  
  for(i=0;i<NTESTS;i++) {
    t[i] = cpucycles();
    //printf("%d\n", (int)t[i]);
    crypto_kem_dec(key, ct, sk);
  }
  result = print_results("kyber_decaps: ", t, NTESTS);
  /*
  print_calls("State Permute calls: ", n_statepermute, NTESTS);
  print_calls("NTT calls: ", n_ntt, NTESTS);
  print_calls("INVNTT calls: ", n_invntt, NTESTS);
  n_statepermute = 0; 
  n_ntt = 0;
  n_invntt = 0;
  */
  print_stuff(result, NTESTS);
  nrf_csr_write(VPRCSR_MCYCLE, 0);
  
  /*
  print_cycles("State Permute Cycles: ", statepermute_cyc, NTESTS);
  print_cycles("NTT Cycles: ", ntt_cyc, NTESTS);
  print_cycles("INVNTT Cycles: ", inv_ntt_cyc, NTESTS); 
  */  
  return 0;
}

void _start(void){
  main();
}
