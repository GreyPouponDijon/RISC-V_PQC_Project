#include "fips202.h"
#include "cpucycles.h"
#include "speed_print.h"
#include "nrf.h"
#include "nrf_vpr_csr.h"
#include "globals.h"

#define SIM_EXIT_ADDR 0x20008000
#define NROUNDS 24



#define ROL(a, offset) ((a << offset) ^ (a >> (64-offset)))

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



int main(void)
{
  uint64_t A, B, C;
  A = KeccakF_RoundConstantsh
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
