#ifndef VPR_UTIL_H
#define VPR_UTIL_H

#include "riscv_encoding.h"

static inline void enableVprRT(void) {
    csr_read_and_set_bits(VPRCSR_NORDIC_VPRNORDICCTRL,
                          (VPRCSR_NORDIC_VPRNORDICCTRL_NORDICKEY_Enabled << VPRCSR_NORDIC_VPRNORDICCTRL_NORDICKEY_Pos) |
                          (VPRCSR_NORDIC_VPRNORDICCTRL_ENABLERTPERIPH_Enabled << VPRCSR_NORDIC_VPRNORDICCTRL_ENABLERTPERIPH_Pos));
}

static inline void enableVprRTandVTIM(void) {
    csr_read_and_set_bits(VPRCSR_NORDIC_VPRNORDICCTRL,
                          (VPRCSR_NORDIC_VPRNORDICCTRL_NORDICKEY_Enabled << VPRCSR_NORDIC_VPRNORDICCTRL_NORDICKEY_Pos) |
                          (VPRCSR_NORDIC_VPRNORDICCTRL_ENABLERTPERIPH_Enabled << VPRCSR_NORDIC_VPRNORDICCTRL_ENABLERTPERIPH_Pos) |
                          (VPRCSR_NORDIC_VPRNORDICCTRL_CNTIRQENABLE_Enabled << VPRCSR_NORDIC_VPRNORDICCTRL_CNTIRQENABLE_Pos));
}

static inline void enableVprInterrupts(void) {
    /*
    csr_read_and_set_bits(VPRCSR_MSTATUS,
                          (VPRCSR_MSTATUS_MIE_Enabled << VPRCSR_MSTATUS_MIE_Pos));
    */
    __asm__ __volatile__("csrsi mstatus, 0x8");
}

static inline void disableVprInterrupts(void) {
    __asm__ __volatile__("csrci mstatus, 0x8");
    /*
    csr_read_and_clear_bits(VPRCSR_MSTATUS,
                          (VPRCSR_MSTATUS_MIE_Enabled << VPRCSR_MSTATUS_MIE_Pos));
    */
}
/*
static inline void enableVprIntAutoStacking(void) {
    csr_write(VPRCSR_NORDIC_VPRNORDICFEATURESDISABLE,
              ((VPRCSR_NORDIC_VPRNORDICFEATURESDISABLE_NORDICKEY_Enabled << VPRCSR_NORDIC_VPRNORDICFEATURESDISABLE_NORDICKEY_Pos)
                | (VPRCSR_NORDIC_VPRNORDICFEATURESDISABLE_ResetValue)
                | (VPRCSR_NORDIC_VPRNORDICFEATURESDISABLE_INTHWSTACKING_AUTOSTACK1F0 << VPRCSR_NORDIC_VPRNORDICFEATURESDISABLE_INTHWSTACKING_Pos)
              )
             );
}

static inline void disableVprIntAutoStacking(void) {
    csr_write(VPRCSR_NORDIC_VPRNORDICFEATURESDISABLE,
              ((VPRCSR_NORDIC_VPRNORDICFEATURESDISABLE_NORDICKEY_Enabled << VPRCSR_NORDIC_VPRNORDICFEATURESDISABLE_NORDICKEY_Pos)
                | (VPRCSR_NORDIC_VPRNORDICFEATURESDISABLE_ResetValue)
                | (VPRCSR_NORDIC_VPRNORDICFEATURESDISABLE_INTHWSTACKING_NOAUTOSTACK << VPRCSR_NORDIC_VPRNORDICFEATURESDISABLE_INTHWSTACKING_Pos)
              )
             );
}
*/


static __attribute__((always_inline)) inline uint32_t __get_MSP(void)
{
    uint32_t result;

    __asm__ __volatile__("mv %0, sp" : "=r" (result) );
    return(result);
}

static __attribute__((always_inline)) inline void __set_MSP(uint32_t stack_pointer)
{
    __asm__ __volatile__("mv sp, %0" : : "r" (stack_pointer) );
}

#endif
