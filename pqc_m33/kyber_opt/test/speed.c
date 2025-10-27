#include "api.h"
#include "nrf.h"
#include "speed_print.h"

#include "cpucycles.h"

#include <stdio.h>
#include <stdint.h>
#include <string.h>


int main(void)
{
  unsigned char key_a[CRYPTO_BYTES], key_b[CRYPTO_BYTES];
  unsigned char sk[CRYPTO_SECRETKEYBYTES];
  unsigned char pk[CRYPTO_PUBLICKEYBYTES];
  unsigned char ct[CRYPTO_CIPHERTEXTBYTES];
  unsigned long long t0, t1;

  //hal_setup(CLOCK_BENCHMARK);

  //printf("==========================");

  // Key-pair generatio//n
  t0 = cpucycles();
  crypto_kem_keypair(pk, sk);
  t1 = cpucycles();
  printf("keypair cycles: %u", t1-t0);

  // Encapsulation
  t0 = cpucycles();
  crypto_kem_enc(ct, key_a, pk);
  t1 = cpucycles();
  printf("encaps cycles: %u", t1-t0);

  // Decapsulation
  t0 = cpucycles();
  crypto_kem_dec(key_b, ct, sk);
  t1 = cpucycles();
  printf("decaps cycles: %u", t1-t0);

  if (memcmp(key_a, key_b, CRYPTO_BYTES)) {
    printf("ERROR KEYS\n");
  }
  else {
    printf("OK KEYS\n");
  }

#include "poly.h"

  // ntt
  poly a,b;
  t0 = cpucycles();
  poly_ntt(&a);
  t1 = cpucycles();
  printf("\npoly ntt cycles: %u", t1-t0);

  // inv ntt
  t0 = cpucycles();
  poly_invntt(&a);
  t1 = cpucycles();
  printf("poly invntt cycles: %u", t1-t0);

  // basemul
  t0 = cpucycles();
#ifdef NEWHOPE_Q
#if NEWHOPE_Q == 12289
  poly_mul_pointwise(&a, &b);
#else
  poly_basemul(&a, &b);
#endif
#else
  poly c;
  poly_basemul(&a, &b, &c);
#endif
  t1 = cpucycles();
  printf("poly basemul cycles: %u", t1-t0);

  printf("#");
  while(1);
  return 0;
}
