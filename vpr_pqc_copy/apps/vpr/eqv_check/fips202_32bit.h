void KeccakF1600_StatePermute_32bit(uint32_t *state);

//void rv_bcop(uint32_t rs1_lo, uint32_t rs1_hi, uint32_t rs2_lo, uint32_t rs2_hi, uint32_t rs3_lo, uint32_t rs3_hi, uint32_t *rd_lo, uint32_t *rd_hi);

extern uint32_t three_xor_count;
extern uint32_t rol64_count;
extern uint32_t bcop_count;


extern uint32_t three_xor_avg_cyc;
extern uint32_t three_xor_tot_cyc;
extern uint32_t rol64_avg_cyc; 
extern uint32_t rol64_tot_cyc; 
extern uint32_t bcop_avg_cyc;
extern uint32_t bcop_tot_cyc;


