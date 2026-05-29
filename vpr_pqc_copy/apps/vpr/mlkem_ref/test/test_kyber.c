#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "../kem.h"
#include "../randombytes.h"
#include "cpucycles.h"
#include "speed_print.h"
#include "nrf.h"
#include "nrf_vpr_csr.h"
#include "globals.h"

#define SIM_EXIT_ADDR 0x20008000



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


#define NTESTS 10

static int test_keys(void)
{
  uint8_t pk[CRYPTO_PUBLICKEYBYTES];
  uint8_t sk[CRYPTO_SECRETKEYBYTES];
  uint8_t ct[CRYPTO_CIPHERTEXTBYTES];
  uint8_t key_a[CRYPTO_BYTES];
  uint8_t key_b[CRYPTO_BYTES];

  //Alice generates a public key
  crypto_kem_keypair(pk, sk);

  //Bob derives a secret key and creates a response
  crypto_kem_enc(ct, key_b, pk);

  //Alice uses Bobs response to get her shared key
  crypto_kem_dec(key_a, ct, sk);

  if(memcmp(key_a, key_b, CRYPTO_BYTES)) {
    printf("ERROR keys\n");
    return 1;
  }

  return 0;
}

static int test_invalid_sk_a(void)
{
  uint8_t pk[CRYPTO_PUBLICKEYBYTES];
  uint8_t sk[CRYPTO_SECRETKEYBYTES];
  uint8_t ct[CRYPTO_CIPHERTEXTBYTES];
  uint8_t key_a[CRYPTO_BYTES];
  uint8_t key_b[CRYPTO_BYTES];

  //Alice generates a public key
  crypto_kem_keypair(pk, sk);

  //Bob derives a secret key and creates a response
  crypto_kem_enc(ct, key_b, pk);

  //Replace secret key with random values
  randombytes(sk, CRYPTO_SECRETKEYBYTES);

  //Alice uses Bobs response to get her shared key
  crypto_kem_dec(key_a, ct, sk);

  if(!memcmp(key_a, key_b, CRYPTO_BYTES)) {
    printf("ERROR invalid sk\n");
    return 1;
  }

  return 0;
}

static int test_invalid_ciphertext(void)
{
  uint8_t pk[CRYPTO_PUBLICKEYBYTES];
  uint8_t sk[CRYPTO_SECRETKEYBYTES];
  uint8_t ct[CRYPTO_CIPHERTEXTBYTES];
  uint8_t key_a[CRYPTO_BYTES];
  uint8_t key_b[CRYPTO_BYTES];
  uint8_t b;
  size_t pos;

  do {
    randombytes(&b, sizeof(uint8_t));
  } while(!b);
  randombytes((uint8_t *)&pos, sizeof(size_t));

  //Alice generates a public key
  crypto_kem_keypair(pk, sk);

  //Bob derives a secret key and creates a response
  crypto_kem_enc(ct, key_b, pk);

  //Change some byte in the ciphertext (i.e., encapsulated key)
  ct[pos % CRYPTO_CIPHERTEXTBYTES] ^= b;

  //Alice uses Bobs response to get her shared key
  crypto_kem_dec(key_a, ct, sk);

  if(!memcmp(key_a, key_b, CRYPTO_BYTES)) {
    printf("ERROR invalid ciphertext\n");
    return 1;
  }

  return 0;
}

int main(void)
{
  //printf("test_kyber main");
  unsigned int i;
  int r;

  for(i=0;i<NTESTS;i++) {
    r  = test_keys();
    r |= test_invalid_sk_a();
    r |= test_invalid_ciphertext();
    if(r)
      return 1;
  }

  //printf("CRYPTO_SECRETKEYBYTES:  %d\n",CRYPTO_SECRETKEYBYTES);
  //printf("CRYPTO_PUBLICKEYBYTES:  %d\n",CRYPTO_PUBLICKEYBYTES);
  //printf("CRYPTO_CIPHERTEXTBYTES: %d\n",CRYPTO_CIPHERTEXTBYTES);

  return 0;
}

void _start(void){
  main();
  asm volatile(
      "li t0, %0\n"
      "jr t0"
      :
      : "i"(SIM_EXIT_ADDR)
  );
}
