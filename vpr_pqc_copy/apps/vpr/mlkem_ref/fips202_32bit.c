#include <stddef.h>
#include <stdint.h>
#include "fips202.h"
#include "cpucycles.h"



#define ROL(a, offset) ((a << offset) ^ (a >> (64-offset)))


static inline void rol64_concat(uint32_t lo, uint32_t hi, uint32_t offset, uint32_t *out_lo, uint32_t *out_hi)
{
  uint64_t concat_val = ((uint64_t)hi << 32) | lo;
  uint64_t rot_val = (concat_val << offset) ^ (concat_vcal >> (64-offset));

  *out_hi = (uint32_t)(rot_val >> 32);
  *out_lo = (uint32_t)rot_val;
}

#ifdef CUSTOM_BCOP
static inline void rv_bcop(uint32_t rs1, uint32_t rs2, uint32_t rs3, uint32_t *rd);
{
  //rs1 ^ ((~rs2) & rs3)
  asm volatile (
      ".insn r CUSTOM_0, 0x1, 0x1 , %0, %1, %2"
      : "=r"(rd);
      : "r"(rs1), "r"(rs2), "r"(rs3)
      : /* no clobbers */
  );
}
#endif

void rv_bcop(uint32_t rs1_lo, uint32_t rs1_hi, uint32_t rs2_lo, uint32_t rs2_hi, uint32_t rs3_lo, uint32_t rs3_hi, uint32_t *rd_lo, uint32_t *rd_hi)
{
  uint32_t out_lo, out_hi;
    asm volatile(
  ".insn r CUSTOM_0, 0x1, 0x0, %0, %2, %3, %4\n\t"
  ".insn r CUSTOM_0, 0x1, 0x0, %1, %5, %6, %7\n\t"
  : "=&r"(out_lo), "=&r"(out_hi)
  : "r"(rs1_lo), "r"(rs2_lo), "r"(rs3_lo),
    "r"(rs1_hi), "r"(rs2_hi), "r"(rs3_hi)
  : "cc"
  );

  *rd_lo = out_lo; 
  *rd_hi = out_hi;
}

 /* Keccak round constants */
 /* even index = upper half */
 /* odd index = lower half */
static const uint32_t KeccakF_RoundConstants32[2 * 24] = {
    0x00000000, 0x00000001,
    0x00000000, 0x00008082,
    0x80000000, 0x0000808a,
    0x80000000, 0x80008000,
    0x00000000, 0x0000808b,
    0x00000000, 0x80000001,
    0x80000000, 0x80008081,
    0x80000000, 0x00008009,
    0x00000000, 0x0000008a,
    0x00000000, 0x00000088,
    0x00000000, 0x80008009,
    0x00000000, 0x8000000a,
    0x00000000, 0x8000808b,
    0x80000000, 0x0000008b,
    0x80000000, 0x00008089,
    0x80000000, 0x00008003,
    0x80000000, 0x00008002,
    0x80000000, 0x00000080,
    0x00000000, 0x0000800a,
    0x80000000, 0x8000000a,
    0x80000000, 0x80008081,
    0x80000000, 0x00008080,
    0x00000000, 0x80000001,
    0x80000000, 0x80008008
}; 

static void KeccakF1600_StatePermute(uint32_t *state) {
    uint32_t Aba_lo, Aba_hi, Abe_lo, Abe_hi, Abi_lo, Abi_hi, Abo_lo, Abo_hi, Abu_lo, Abu_hi;
    uint32_t Aga_lo, Aga_hi, Age_lo, Age_hi, Agi_lo, Agi_hi, Ago_lo, Ago_hi, Agu_lo, Agu_hi;
    uint32_t Aka_lo, Aka_hi, Ake_lo, Ake_hi, Aki_lo, Aki_hi, Ako_lo, Ako_hi, Aku_lo, Aku_hi;
    uint32_t Ama_lo, Ama_hi, Ame_lo, Ame_hi, Ami_lo, Ami_hi, Amo_lo, Amo_hi, Amu_lo, Amu_hi;
    uint32_t Asa_lo, Asa_hi, Ase_lo, Ase_hi, Asi_lo, Asi_hi, Aso_lo, Aso_hi, Asu_lo, Asu_hi;
    uint32_t BCa_lo, BCa_hi, BCe_lo, BCe_hi, BCi_lo, BCi_hi, BCo_lo, BCo_hi, BCu_lo, BCu_hi;
    uint32_t Da_lo, Da_hi, De_lo, De_hi, Di_lo, Di_hi, Do_lo, Do_hi, Du_lo, Du_hi;
    uint32_t Eba_lo, Eba_hi, Ebe_lo, Ebe_hi, Ebi_lo, Ebi_hi, Ebo_lo, Ebo_hi, Ebu_lo, Ebu_hi;
    uint32_t Ega_lo, Ega_hi, Ege_lo, Ege_hi, Egi_lo, Egi_hi, Ego_lo, Ego_hi, Egu_lo, Egu_hi;                             
    uint32_t Eka_lo, Eka_hi, Eke_lo, Eke_hi, Eki_lo, Eki_hi, Eko_lo, Eko_hi, Eku_lo, Eku_hi; 
    uint32_t Ema_lo, Ema_hi, Eme_lo, Eme_hi, Emi_lo, Emi_hi, Emo_lo, Emo_hi, Emu_lo, Emu_hi;
    uint32_t Esa_lo, Esa_hi, Ese_lo, Ese_hi, Esi_lo, Esi_hi,Eso_lo, Eso_hi, Esu_lo, Esu_hi;

    Aba_lo = state[ 0];  Aba_hi = state[ 1];
    Abe_lo = state[ 2];  Abe_hi = state[ 3];
    Abi_lo = state[ 4];  Abi_hi = state[ 5];
    Abo_lo = state[ 6];  Abo_hi = state[ 7];
    Abu_lo = state[ 8];  Abu_hi = state[ 9];

    Aga_lo = state[10];  Aga_hi = state[11];
    Age_lo = state[12];  Age_hi = state[13];
    Agi_lo = state[14];  Agi_hi = state[15];
    Ago_lo = state[16];  Ago_hi = state[17];
    Agu_lo = state[18];  Agu_hi = state[19];

    Aka_lo = state[20];  Aka_hi = state[21];
    Ake_lo = state[22];  Ake_hi = state[23];
    Aki_lo = state[24];  Aki_hi = state[25];
    Ako_lo = state[26];  Ako_hi = state[27];
    Aku_lo = state[28];  Aku_hi = state[29];

    Ama_lo = state[30];  Ama_hi = state[31];
    Ame_lo = state[32];  Ame_hi = state[33];
    Ami_lo = state[34];  Ami_hi = state[35];
    Amo_lo = state[36];  Amo_hi = state[37];
    Amu_lo = state[38];  Amu_hi = state[39];

    Asa_lo = state[40];  Asa_hi = state[41];
    Ase_lo = state[42];  Ase_hi = state[43];
    Asi_lo = state[44];  Asi_hi = state[45];
    Aso_lo = state[46];  Aso_hi = state[47];
    Asu_lo = state[48];  Asu_hi = state[49];


    uint32_t Da_lo_tmp, Da_hi_tmp;
    uint32_t De_lo_tmp, De_hi_tmp;
    uint32_t Di_lo_tmp, Di_hi_tmp;
    uint32_t Do_lo_tmp, Di_hi_tmp;
    uint32_t Du_lo_tmp, Du_hi_tmp;
    uint32_t BCe_lo_tmp, BCe_hi_tmp;
    uint32_t BCi_lo_tmp, BCi_hi_tmp;
    uint32_t BCo_lo_tmp, BCo_hi_tmp;
    uint32_t BCu_lo_tmp, BCu_hi_tmp;
    uint32_t Eba_lo_tmp, Eba_hi_tmp;

    for(round = 0; round < NROUNDS; round += 2) {
      BCa_lo = Aba_lo ^ Aga_lo ^ Aka_lo ^ Ama_lo ^ Asa_lo
      BCa_hi = Aba_hi ^ Aga_hi ^ Aka_hi ^ Ama_hi ^ Asa_hi;

      BCe_lo = Abe_lo ^ Age_lo ^ Ake_lo ^ Ame_lo ^ Ase_lo;
      BCe_hi = Abe_hi ^ Age_hi ^ Ake_hi ^ Ame_hi ^ Ase_hi;

      BCi_lo = Abi_lo ^ Agi_lo ^ Aki_lo ^ Ami_lo ^ Asi_lo;
      BCi_hi = Abi_hi ^ Agi_hi ^ Aki_hi ^ Ami_hi ^ Asi_hi;

      BCo_lo = Abo_lo ^ Ago_lo ^ Ako_lo ^ Amo_lo ^ Aso_lo;
      BCo_hi = Abo_hi ^ Ago_hi ^ Ako_hi ^ Amo_hi ^ Aso_hi;

      BCu_lo = Abu_lo ^ Agu_lo ^ Aku_lo ^ Amu_lo ^ Asu_lo;
      BCu_hi = Abu_hi ^ Agu_hi ^ Aku_hi ^ Amu_hi ^ Asu_hi;
 

      rol64_concat(BCe_lo, BCe_hi, 1, &BCe_lo_tmp, &BCe_hi_tmp);
      Da_lo = BCu_lo ^ BCe_lo_tmp;
      Da_hi = BCu_hi ^ BCe_hi_tmp;

      rol64_concat(BCi_hi, BCi_lo, 1, &BCi_lo_tmp, &BCi_hi_tmp);
      De_lo = BCa_lo ^ BCi_lo_tmp;
      De_hi = BCa_hi ^ BCi_hi_tmp;

      rol64_concat(BCo_hi, BCo_lo, 1, &BCo_lo_tmp, &BCo_hi_tmp);
      Di_lo = BCe_lo ^ BCo_lo_tmp;
      Di_hi = BCe_hi ^ BCo_hi_tmp;

      rol64_concat(BCu_hi, BCu_lo, 1, &BCu_lo_tmp, &BCu_hi_tmp);
      Do_lo = BCi_lo ^ BCu_lo_tmp;
      Do_hi = BCi_hi ^ BCu_hi_tmp;

      rol64_concat(BCa_hi, BCa_lo, 1, &BCa_lo_tmp, &BCa_hi_tmp);
      Du_lo = BCo_lo ^ BCa_lo_tmp;
      Du_hi = BCo_hi ^ BCa_hi_tmp;

      Aba_lo ^= Da_lo;
      Aba_hi ^= Da_hi;

      BCa_lo = Aba_lo;
      BCa_hi = Aba_hi;

      Age_lo ^= De_lo;
      Age_hi ^= De_hi;

      rol64_concat(Age_lo, Age_hi, 44, &BCe_lo_tmp, &BCe_hi_tmp);
      BCe_hi = BCe_hi_tmp;
      BCe_lo = BCe_lo_tmp;

      Aki_lo ^= Di_lo;
      Aki_hi ^= Di_hi;

      rol64_concat(Aki_lo, Aki_hi, 43, &BCi_lo_tmp, BCi_hi_tmp);
      BCi_hi = BCi_hi_tmp;
      BCi_lo = BCi_lo_tmp;

      Amo_lo ^= Do_lo;
      Amo_hi ^= Do_hi;

      rol64_concat(Amo_lo, Amo_hi, 21, &BCo_lo_tmp, BCo_hi_tmp);
      BCo_hi = BCo_hi_tmp;
      BCo_lo = BCo_lo_tmp;

      Asu_lo ^= Du_lo;
      Asu_hi ^= Du_hi;
      
      rol64_concat(Asu_lo, Asu_hi, 14, &BCu_lo_tmp, &BCu_hi_tmp);
      BCu_hi = BCu_hi_tmp;
      BCu_lo = BCu_lo_tmp;

      #ifdef CUSTOM_BCOP
        asm volatile(
        ".insn r CUSTOM_0, 0x1, 0x0, a3, %[rs1_lo], %[rs2_lo], %[rs3_lo]\n\t"
        "xor %[rd_lo], a3, %[keccak_lo]\n\t" 
        ".insn r CUSTOM_0, 0x1, 0x0, a5, %[rs1_hi], %[rs2_hi], %[rs3_hi]\n\t"
        "xor %[rd_hi], a3, %[keccak_hi]\n\t"
        : [rd_lo] "=r" (Eba_lo), [rd_hi] "=r" (Eba_hi)
        : [rs1_lo] "r" (BCa_lo), [rs2_lo] "r" (BCe_lo), [rs3_lo] "r" (BCi_lo),
          [keccak_lo] "r" (KeccakF_RoundConstants32[rounds * 2 + 1]),
          [rs1_hi] "r" (BCa_hi), [rs2_hi] "r" (BCe_hi), [rs3_hi] "r" (BCi_hi),
          [keccak_hi] "r" (KeccakF_RoundConstants32[rounds * 2])
          : "a3","a5", "cc"
        );
      #else if defined(CUSTOM_BCOP_XOR_LMW)
        asm volatile(
        ".insn r CUSTOM_0, 0x2, 0x0, a0, a1, %[rs1_addr]\n\t" //load multiple, exploits 64-bit axi bus
        ".insn r CUSTOM_0, 0x2, 0x0, a2, a3, %[rs2_addr]\n\t"
        ".insn r CUSTOM_0, 0x2, 0x0, a4, a5, %[rs3_addr]\n\t"
        ".insn r CUSTOM_0, 0x1, 0x0, t1, a1, a3, a5\n\t"
        ".insn r CUSTOM_0, 0x2, 0x0, a1, a3 %[keccak_addr]\n\t"
        "xor %[rd_lo], t1, a3\n\t" 
        ".insn r CUSTOM_0, 0x1, 0x0, t0, a0, a2, a4\n\t"
        "xor %[rd_hi], t0, a1\n\t"
        : [rd_lo] "=r" (Eba_lo), [rd_hi] "=r" (Eba_hi i)
        : [rs1_addr] "r" (&BCa_hi), [rs2_addr] "r" (&BCe_hi), [rs3_addr] "r" (&Bci_hi),
          [keccak_addr] "r" (KeccakF_RoundConstants32[rounds * 2]
          :"t0", "t2", "a0", "a1", "a2","a3","a4","a5", "cc"
        );

      #else
        Eba_lo = Bca_lo ^ ((~BCe_lo)& BCi_lo);
        Eba_hi = Bca_hi ^ ((~BCe_hi)& BCi_hi);
        Eba_lo ^= KeccakF_RoundConstants[rounds * 2 + 1];
        Eba_hi ^= KeccakF_RoundConstants[rounds * 2];
      #endif

      rv_bcop(BCe_lo, BCe_hi, BCi_lo, BCi_hi, BCo_lo, BCo_hi, &Ebe_lo, &Ebe_hi);
      rv_bcop(BCi_lo, BCi_hi, BCo_lo, BCo_hi, BCu_lo, BCu_hi, &Ebi_lo, &Ebi_hi);
      rv_bcop(BCo_lo, BCo_hi, BCu_lo, BCu_hi, BCa_lo, BCa_hi, &Ebo_lo, &Ebo_hi);
      rv_bcop(BCu_lo, BCu_hi, BCa_lo, BCa_hi, BCe_lo, BCe_hi, &Ebu_lo, &Ebu_lo);
      
      Abo_lo ^= Do_lo;
      Abo_hi ^= Do_hi;
      rol64_concat(Abo_lo, Abo_hi, 28, &BCa_lo, &BCa_hi);
      
      Agu_lo ^= Du_lo;
      Agu_hi ^= Du_hi;  
      rol64_concat(Agu_lo, Agu_hi, 20, &BCe_lo, &BCe_hi);

      Aka_lo ^= Da_lo;
      Aka_hi ^= Da_hi;  
      rol64_concat(Aka_lo, Aka_hi, 3, &BCi_lo, &BCi_hi);

      Ame_lo ^= De_lo;
      Ame_hi ^= De_hi;  
      rol64_concat(Ame_lo, Ame_hi, 45, &BCo_lo, &BCo_hi);

      Asi_lo ^= Di_lo;
      Asi_hi ^= Di_hi;  
      rol64_concat(Asi_lo, Asi_hi, 61, &BCu_lo, &BCu_hi);

      rv_bcop(BCa_lo, BCa_hi, BCe_lo, BCe_hi, BCi_lo, BCi_hi, &Ega_lo, &Ega_hi);
      rv_bcop(BCe_lo, BCe_hi, BCi_lo, BCi_hi, BCo_lo, BCo_hi, &Ege_lo, &Ege_hi);
      rv_bcop(BCi_lo, BCi_hi, BCo_lo, BCo_hi, BCu_lo, BCu_hi, &Egi_lo, &Egi_hi);
      rv_bcop(BCo_lo, BCo_hi, BCu_lo, BCu_hi, BCa_lo, BCa_hi, &Ego_lo, &Ego_hi);
      rv_bcop(BCu_lo, BCu_hi, BCa_lo, BCa_hi, BCe_lo, BCe_hi, &Egu_lo, &Egu_hi);

      Abe_lo ^= De_lo;
      Abe_hi ^= De_hi;
      rol64_concat(Abe_lo, Abe_hi, 1, &BCa_lo, &BCa_hi);

      Agi_lo ^= Di_lo;
      Agi_hi ^= Di_hi;
      rol64_concat(Agi_lo, Agi_hi, 6, &BCe_lo, &BCe_hi);

      Ako_lo ^= Do_lo;
      Ako_hi ^= Do_hi;
      rol64_concat(Ako_lo, Ako_hi, 25, &BCi_lo, &BCi_hi);

      Amu_lo ^= Du_lo;
      Amu_hi ^= Du_hi;
      rol64_concat(Amu_lo, Amu_hi, 8, &BCo_lo, &BCo_hi);

      Asa_lo ^= Da_lo;
      Asa_hi ^= Da_hi;
      rol64_concat(Asa_lo, Asa_hi, 18, &BCu_lo, &BCu_hi);

      rv_bcop(BCa_lo, BCa_hi, BCe_lo, BCe_hi, BCi_lo, BCi_hi, &Eka_lo, &Eka_hi);
      rv_bcop(BCe_lo, BCe_hi, BCi_lo, BCi_hi, BCo_lo, BCo_hi, &Eke_lo, &Eke_hi);
      rv_bcop(BCi_lo, BCi_hi, BCo_lo, BCo_hi, BCu_lo, BCu_hi, &Eki_lo, &Eki_hi);
      rv_bcop(BCo_lo, BCo_hi, BCu_lo, BCu_hi, BCa_lo, BCa_hi, &Eko_lo, &Eko_hi);
      rv_bcop(BCu_lo, BCu_hi, BCa_lo, BCa_hi, BCe_lo, BCe_hi, &Eku_lo, &Eku_hi);

      Abu_lo ^= Du_lo;
      Abu_hi ^= Du_hi;
      rol64_concat(Abu_lo, Abu_hi, 27, &BCa_lo, &BCa_hi);

      Aga_lo ^= Da_lo;
      Aga_hi ^= Da_hi;
      rol64_concat(Aga_lo, Aga_hi, 36, &BCe_lo, &BCe_hi);

      Ake_lo ^= De_lo;
      Ake_hi ^= De_hi;
      rol64_concat(Ake_lo, Ake_hi, 10, &BCi_lo, &BCi_hi);

      Ami_lo ^= Di_lo;
      Ami_hi ^= Di_hi;
      rol64_concat(Ami_lo, Ami_hi, 15, &BCo_lo, &BCo_hi);

      Aso_lo ^= Do_lo;
      Aso_hi ^= Do_hi;
      rol64_concat(Aso_lo, Aso_hi, 56, &BCu_lo, &BCu_hi);

      rv_bcop(BCa_lo, BCa_hi, BCe_lo, BCe_hi, BCi_lo, BCi_hi, &Ema_lo, &Ema_hi);
      rv_bcop(BCe_lo, BCe_hi, BCi_lo, BCi_hi, BCo_lo, BCo_hi, &Eme_lo, &Eme_hi);
      rv_bcop(BCi_lo, BCi_hi, BCo_lo, BCo_hi, BCu_lo, BCu_hi, &Emi_lo, &Emi_hi);
      rv_bcop(BCo_lo, BCo_hi, BCu_lo, BCu_hi, BCa_lo, BCa_hi, &Emo_lo, &Emo_hi);
      rv_bcop(BCu_lo, BCu_hi, BCa_lo, BCa_hi, BCe_lo, BCe_hi, &Emu_lo, &Emu_hi);

      Abi_lo ^= Di_lo;
      Abi_hi ^= Di_hi;
      rol64_concat(Abi_lo, Abi_hi, 62, &BCa_lo, &BCa_hi);

      Ago_lo ^= Do_lo;
      Ago_hi ^= Do_hi;
      rol64_concat(Ago_lo, Ago_hi, 55, &BCe_lo, &BCe_hi);

      Aku_lo ^= Du_lo;
      Aku_hi ^= Du_hi;
      rol64_concat(Aku_lo, Aku_hi, 39, &BCi_lo, &BCi_hi);

      Ama_lo ^= Da_lo;
      Ama_hi ^= Da_hi;
      rol64_concat(Ama_lo, Ama_hi, 41, &BCo_lo, &BCo_hi);

      Ase_lo ^= De_lo;
      Ase_hi ^= De_hi;
      rol64_concat(Ase_lo, Ase_hi, 2, &BCu_lo, &BCu_hi);

      rv_bcop(BCa_lo, BCa_hi, BCe_lo, BCe_hi, BCi_lo, BCi_hi, &Esa_lo, &Esa_hi);
      rv_bcop(BCe_lo, BCe_hi, BCi_lo, BCi_hi, BCo_lo, BCo_hi, &Ese_lo, &Ese_hi);
      rv_bcop(BCi_lo, BCi_hi, BCo_lo, BCo_hi, BCu_lo, BCu_hi, &Esi_lo, &Esi_hi);
      rv_bcop(BCo_lo, BCo_hi, BCu_lo, BCu_hi, BCa_lo, BCa_hi, &Eso_lo, &Eso_hi);
      rv_bcop(BCu_lo, BCu_hi, BCa_lo, BCa_hi, BCe_lo, BCe_hi, &Esu_lo, &Esu_hi);

      BCa_lo = Eba_lo ^ Ega_lo ^ Eka_lo ^ Ema_lo ^ Esa_lo;
      BCa_hi = Eba_hi ^ Ega_hi ^ Eka_hi ^ Ema_hi ^ Esa_hi;

      BCe_lo = Ebe_lo ^ Ege_lo ^ Eke_lo ^ Eme_lo ^ Ese_lo;
      BCe_hi = Ebe_hi ^ Ege_hi ^ Eke_hi ^ Eme_hi ^ Ese_hi;

      BCi_lo = Ebi_lo ^ Egi_lo ^ Eki_lo ^ Emi_lo ^ Esi_lo;
      BCi_hi = Ebi_hi ^ Egi_hi ^ Eki_hi ^ Emi_hi ^ Esi_hi;

      BCo_lo = Ebo_lo ^ Ego_lo ^ Eko_lo ^ Emo_lo ^ Eso_lo;
      BCo_hi = Ebo_hi ^ Ego_hi ^ Eko_hi ^ Emo_hi ^ Eso_hi;

      BCu_lo = Ebu_lo ^ Egu_lo ^ Eku_lo ^ Emu_lo ^ Esu_lo;
      BCu_hi = Ebu_hi ^ Egu_hi ^ Eku_hi ^ Emu_hi ^ Esu_hi;

      rol64_concat(BCe_lo, BCe_hi, 1, &BCe_lo_tmp, &BCe_hi_tmp);
      Da_lo = BCu_lo ^ BCe_lo_tmp;
      Da_hi = BCu_hi ^ BCe_hi_tmp;

      rol64_concat(BCi_hi, BCi_lo, 1, &BCi_lo_tmp, &BCi_hi_tmp);
      De_lo = BCa_lo ^ BCi_lo_tmp;
      De_hi = BCa_hi ^ BCi_hi_tmp;

      rol64_concat(BCo_hi, BCo_lo, 1, &BCo_lo_tmp, &BCo_hi_tmp);
      Di_lo = BCe_lo ^ BCo_lo_tmp;
      Di_hi = BCe_hi ^ BCo_hi_tmp;

      rol64_concat(BCu_hi, BCu_lo, 1, &BCu_lo_tmp, &BCu_hi_tmp);
      Do_lo = BCi_lo ^ BCu_lo_tmp;
      Do_hi = BCi_hi ^ BCu_hi_tmp;

      rol64_concat(BCa_hi, BCa_lo, 1, &BCa_lo_tmp, &BCa_hi_tmp);
      Du_lo = BCo_lo ^ BCa_lo_tmp;
      Du_hi = BCo_hi ^ BCa_hi_tmp;

      Eba_lo ^= Da_lo;
      Eba_hi ^= Da_hi;

      BCa_lo = Eba_lo;
      BCa_hi = Eba_hi;

      Ege_lo ^= De_lo;
      Ege_hi ^= De_hi;
      rol64_concat(Ege_lo, Ege_hi, 44, &BCe_lo, &BCe_hi);

      Eki_lo ^= Di_lo;
      Eki_hi ^= Di_hi;
      rol64_concat(Eki_lo, Eki_hi, 43, &BCi_lo, &BCi_hi);

      Emo_lo ^= Do_lo;
      Emo_hi ^= Do_hi;
      rol64_concat(Emo_lo, Emo_hi, 21, &BCo_lo, &BCo_hi);

      Esu_lo ^= Du_lo;
      Esu_hi ^= Du_hi;
      rol64_concat(Esu_lo, Esu_hi, 14, &BCu_lo, &BCu_hi);

      rv_bcop(BCa_lo, BCa_hi, BCe_lo, BCe_hi, BCi_lo, BCi_hi, &Aba_lo, &Aba_hi);
      Aba_lo ^= KeccakF_RoundConstants[round * 2 + 1];
      Aba_hi ^= KeccakF_RoundConstants[round * 2];

      rv_bcop(BCe_lo, BCe_hi, BCi_lo, BCi_hi, BCo_lo, BCo_hi, &Abe_lo, &Abe_hi);
      rv_bcop(BCi_lo, BCi_hi, BCo_lo, BCo_hi, BCu_lo, BCu_hi, &Abi_lo, &Abi_hi);
      rv_bcop(BCo_lo, BCo_hi, BCu_lo, BCu_hi, BCa_lo, BCa_hi, &Abo_lo, &Abo_hi);
      rv_bcop(BCu_lo, BCu_hi, BCa_lo, BCa_hi, BCe_lo, BCe_hi, &Abu_lo, &Abu_hi);

      Ebo_lo ^= Do_lo;
      Ebo_hi ^= Do_hi;
      rol64_concat(Ebo_lo, Ebo_hi, 28, &BCa_lo, &BCa_hi);

      Egu_lo ^= Du_lo;
      Egu_hi ^= Du_hi;
      rol64_concat(Egu_lo, Egu_hi, 20, &BCe_lo, &BCe_hi);

      Eka_lo ^= Da_lo;
      Eka_hi ^= Da_hi;
      rol64_concat(Eka_lo, Eka_hi, 3, &BCi_lo, &BCi_hi);

      Eme_lo ^= De_lo;
      Eme_hi ^= De_hi;
      rol64_concat(Eme_lo, Eme_hi, 45, &BCo_lo, &BCo_hi);

      Esi_lo ^= Di_lo;
      Esi_hi ^= Di_hi;
      rol64_concat(Esi_lo, Esi_hi, 61, &BCu_lo, &BCu_hi);

      rv_bcop(BCa_lo, BCa_hi, BCe_lo, BCe_hi, BCi_lo, BCi_hi, &Aga_lo, &Aga_hi);
      rv_bcop(BCe_lo, BCe_hi, BCi_lo, BCi_hi, BCo_lo, BCo_hi, &Age_lo, &Age_hi);
      rv_bcop(BCi_lo, BCi_hi, BCo_lo, BCo_hi, BCu_lo, BCu_hi, &Agi_lo, &Agi_hi);
      rv_bcop(BCo_lo, BCo_hi, BCu_lo, BCu_hi, BCa_lo, BCa_hi, &Ago_lo, &Ago_hi);
      rv_bcop(BCu_lo, BCu_hi, BCa_lo, BCa_hi, BCe_lo, BCe_hi, &Agu_lo, &Agu_hi);

      Ebe_lo ^= De_lo;
      Ebe_hi ^= De_hi;
      rol64_concat(Ebe_lo, Ebe_hi, 1, &BCa_lo, &BCa_hi);

      Egi_lo ^= Di_lo;
      Egi_hi ^= Di_hi;
      rol64_concat(Egi_lo, Egi_hi, 6, &BCe_lo, &BCe_hi);

      Eko_lo ^= Do_lo;
      Eko_hi ^= Do_hi;
      rol64_concat(Eko_lo, Eko_hi, 25, &BCi_lo, &BCi_hi);

      Emu_lo ^= Du_lo;
      Emu_hi ^= Du_hi;
      rol64_concat(Emu_lo, Emu_hi, 8, &BCo_lo, &BCo_hi);

      Esa_lo ^= Da_lo;
      Esa_hi ^= Da_hi;
      rol64_concat(Esa_lo, Esa_hi, 18, &BCu_lo, &BCu_hi);

      rv_bcop(BCa_lo, BCa_hi, BCe_lo, BCe_hi, BCi_lo, BCi_hi, &Aka_lo, &Aka_hi);
      rv_bcop(BCe_lo, BCe_hi, BCi_lo, BCi_hi, BCo_lo, BCo_hi, &Ake_lo, &Ake_hi);
      rv_bcop(BCi_lo, BCi_hi, BCo_lo, BCo_hi, BCu_lo, BCu_hi, &Aki_lo, &Aki_hi);
      rv_bcop(BCo_lo, BCo_hi, BCu_lo, BCu_hi, BCa_lo, BCa_hi, &Ako_lo, &Ako_hi);
      rv_bcop(BCu_lo, BCu_hi, BCa_lo, BCa_hi, BCe_lo, BCe_hi, &Aku_lo, &Aku_hi);

      Ebu_lo ^= Du_lo;
      Ebu_hi ^= Du_hi;
      rol64_concat(Ebu_lo, Ebu_hi, 27, &BCa_lo, &BCa_hi);

      Ega_lo ^= Da_lo;
      Ega_hi ^= Da_hi;
      rol64_concat(Ega_lo, Ega_hi, 36, &BCe_lo, &BCe_hi);

      Eke_lo ^= De_lo;
      Eke_hi ^= De_hi;
      rol64_concat(Eke_lo, Eke_hi, 10, &BCi_lo, &BCi_hi);

      Emi_lo ^= Di_lo;
      Emi_hi ^= Di_hi;
      rol64_concat(Emi_lo, Emi_hi, 15, &BCo_lo, &BCo_hi);

      Eso_lo ^= Do_lo;
      Eso_hi ^= Do_hi;
      rol64_concat(Eso_lo, Eso_hi, 56, &BCu_lo, &BCu_hi);

      rv_bcop(BCa_lo, BCa_hi, BCe_lo, BCe_hi, BCi_lo, BCi_hi, &Ama_lo, &Ama_hi);
      rv_bcop(BCe_lo, BCe_hi, BCi_lo, BCi_hi, BCo_lo, BCo_hi, &Ame_lo, &Ame_hi);
      rv_bcop(BCi_lo, BCi_hi, BCo_lo, BCo_hi, BCu_lo, BCu_hi, &Ami_lo, &Ami_hi);
      rv_bcop(BCo_lo, BCo_hi, BCu_lo, BCu_hi, BCa_lo, BCa_hi, &Amo_lo, &Amo_hi);
      rv_bcop(BCu_lo, BCu_hi, BCa_lo, BCa_hi, BCe_lo, BCe_hi, &Amu_lo, &Amu_hi);

      Ebi_lo ^= Di_lo;
      Ebi_hi ^= Di_hi;
      rol64_concat(Ebi_lo, Ebi_hi, 62, &BCa_lo, &BCa_hi);

      Ego_lo ^= Do_lo;
      Ego_hi ^= Do_hi;
      rol64_concat(Ego_lo, Ego_hi, 55, &BCe_lo, &BCe_hi);

      Eku_lo ^= Du_lo;
      Eku_hi ^= Du_hi;
      rol64_concat(Eku_lo, Eku_hi, 39, &BCi_lo, &BCi_hi);

      Ema_lo ^= Da_lo;
      Ema_hi ^= Da_hi;
      rol64_concat(Ema_lo, Ema_hi, 41, &BCo_lo, &BCo_hi);

      Ese_lo ^= De_lo;
      Ese_hi ^= De_hi;
      rol64_concat(Ese_lo, Ese_hi, 2, &BCu_lo, &BCu_hi);

      rv_bcop(BCa_lo, BCa_hi, BCe_lo, BCe_hi, BCi_lo, BCi_hi, &Asa_lo, &Asa_hi);
      rv_bcop(BCe_lo, BCe_hi, BCi_lo, BCi_hi, BCo_lo, BCo_hi, &Ase_lo, &Ase_hi);
      rv_bcop(BCi_lo, BCi_hi, BCo_lo, BCo_hi, BCu_lo, BCu_hi, &Asi_lo, &Asi_hi);
      rv_bcop(BCo_lo, BCo_hi, BCu_lo, BCu_hi, BCa_lo, BCa_hi, &Aso_lo, &Aso_hi);
      rv_bcop(BCu_lo, BCu_hi, BCa_lo, BCa_hi, BCe_lo, BCe_hi, &Asu_lo, &Asu_hi);

  }


  state[ 0] = Aba_lo;  state[ 1] = Aba_hi;
  state[ 2] = Abe_lo;  state[ 3] = Abe_hi;
  state[ 4] = Abi_lo;  state[ 5] = Abi_hi;
  state[ 6] = Abo_lo;  state[ 7] = Abo_hi;
  state[ 8] = Abu_lo;  state[ 9] = Abu_hi;

  state[10] = Aga_lo;  state[11] = Aga_hi;
  state[12] = Age_lo;  state[13] = Age_hi;
  state[14] = Agi_lo;  state[15] = Agi_hi;
  state[16] = Ago_lo;  state[17] = Ago_hi;
  state[18] = Agu_lo;  state[19] = Agu_hi;

  state[20] = Aka_lo;  state[21] = Aka_hi;
  state[22] = Ake_lo;  state[23] = Ake_hi;
  state[24] = Aki_lo;  state[25] = Aki_hi;
  state[26] = Ako_lo;  state[27] = Ako_hi;
  state[28] = Aku_lo;  state[29] = Aku_hi;

  state[30] = Ama_lo;  state[31] = Ama_hi;
  state[32] = Ame_lo;  state[33] = Ame_hi;
  state[34] = Ami_lo;  state[35] = Ami_hi;
  state[36] = Amo_lo;  state[37] = Amo_hi;
  state[38] = Amu_lo;  state[39] = Amu_hi;

  state[40] = Asa_lo;  state[41] = Asa_hi;
  state[42] = Ase_lo;  state[43] = Ase_hi;
  state[44] = Asi_lo;  state[45] = Asi_hi;
  state[46] = Aso_lo;  state[47] = Aso_hi;
  state[48] = Asu_lo;  state[49] = Asu_hi;

    
}


