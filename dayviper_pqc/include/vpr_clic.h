#include <stdint.h>
#include <stdbool.h>

#ifndef CLIC_H__
#define CLIC_H__

#if __has_include("nrfx.h")
#include "nrfx.h"
#else
#define __STATIC_INLINE static inline
#endif

__STATIC_INLINE void CLIC_EnableIRQ(IRQn_Type irq_num) {
    NRF_VPRCLIC->CLIC.CLICINT[irq_num] =
        ((NRF_VPRCLIC->CLIC.CLICINT[irq_num] & ~CLIC_CLIC_CLICINT_IE_Msk) |
         (CLIC_CLIC_CLICINT_IE_Enabled << CLIC_CLIC_CLICINT_IE_Pos));
}

__STATIC_INLINE bool CLIC_IsEnabledIRQ(IRQn_Type irq_num) {
        return ((NRF_VPRCLIC->CLIC.CLICINT[irq_num] & CLIC_CLIC_CLICINT_IE_Msk) &
                 CLIC_CLIC_CLICINT_IE_Pos);
}

__STATIC_INLINE void CLIC_DisableIRQ(IRQn_Type irq_num) {
    NRF_VPRCLIC->CLIC.CLICINT[irq_num] =
        ((NRF_VPRCLIC->CLIC.CLICINT[irq_num] & ~CLIC_CLIC_CLICINT_IE_Msk) |
         (CLIC_CLIC_CLICINT_IE_Disabled << CLIC_CLIC_CLICINT_IE_Pos));
}

__STATIC_INLINE void CLIC_SetPriority(IRQn_Type irq_num, uint32_t priority) {
    NRF_VPRCLIC->CLIC.CLICINT[irq_num] =
        ((NRF_VPRCLIC->CLIC.CLICINT[irq_num] & ~CLIC_CLIC_CLICINT_PRIORITY_Msk) |
         ((priority << CLIC_CLIC_CLICINT_PRIORITY_Pos) & CLIC_CLIC_CLICINT_PRIORITY_Msk));
}

__STATIC_INLINE void CLIC_SetPendingIRQ(IRQn_Type irq_num) {
    NRF_VPRCLIC->CLIC.CLICINT[irq_num] =
        ((NRF_VPRCLIC->CLIC.CLICINT[irq_num] & ~CLIC_CLIC_CLICINT_IP_Msk) |
         (CLIC_CLIC_CLICINT_IP_Pending << CLIC_CLIC_CLICINT_IP_Pos));
}

__STATIC_INLINE void CLIC_ClearPendingIRQ(IRQn_Type irq_num) {
    NRF_VPRCLIC->CLIC.CLICINT[irq_num] =
        ((NRF_VPRCLIC->CLIC.CLICINT[irq_num] & ~CLIC_CLIC_CLICINT_IP_Msk) |
         (CLIC_CLIC_CLICINT_IP_NotPending << CLIC_CLIC_CLICINT_IP_Pos));
}

__STATIC_INLINE uint32_t CLIC_GetPendingIRQ(IRQn_Type irq_num) {
    return ((NRF_VPRCLIC->CLIC.CLICINT[irq_num] & CLIC_CLIC_CLICINT_IP_Msk) >> CLIC_CLIC_CLICINT_IP_Pos);
}

#endif // CLIC_H__
