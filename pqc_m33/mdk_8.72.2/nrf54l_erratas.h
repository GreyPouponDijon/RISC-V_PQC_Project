#ifndef NRF54L_ERRATAS_H
#define NRF54L_ERRATAS_H

/*

Copyright (c) 2010 - 2025, Nordic Semiconductor ASA

All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.

2. Redistributions in binary form, except as embedded into a Nordic
   Semiconductor ASA integrated circuit in a product or a software update for
   such product, must reproduce the above copyright notice, this list of
   conditions and the following disclaimer in the documentation and/or other
   materials provided with the distribution.

3. Neither the name of Nordic Semiconductor ASA nor the names of its
   contributors may be used to endorse or promote products derived from this
   software without specific prior written permission.

4. This software, with or without modification, must only be used with a
   Nordic Semiconductor ASA integrated circuit.

5. Any software provided in binary form under this license must not be reverse
   engineered, decompiled, modified and/or disassembled.

THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/

#include <stdint.h>
#include <stdbool.h>
#include "compiler_abstraction.h"

static bool nrf54l_errata_1(void) __UNUSED;
static bool nrf54l_errata_2(void) __UNUSED;
static bool nrf54l_errata_3(void) __UNUSED;
static bool nrf54l_errata_4(void) __UNUSED;
static bool nrf54l_errata_6(void) __UNUSED;
static bool nrf54l_errata_7(void) __UNUSED;
static bool nrf54l_errata_8(void) __UNUSED;
static bool nrf54l_errata_9(void) __UNUSED;
static bool nrf54l_errata_10(void) __UNUSED;
static bool nrf54l_errata_13(void) __UNUSED;
static bool nrf54l_errata_16(void) __UNUSED;
static bool nrf54l_errata_17(void) __UNUSED;
static bool nrf54l_errata_18(void) __UNUSED;
static bool nrf54l_errata_19(void) __UNUSED;
static bool nrf54l_errata_20(void) __UNUSED;
static bool nrf54l_errata_21(void) __UNUSED;
static bool nrf54l_errata_22(void) __UNUSED;
static bool nrf54l_errata_23(void) __UNUSED;
static bool nrf54l_errata_24(void) __UNUSED;
static bool nrf54l_errata_25(void) __UNUSED;
static bool nrf54l_errata_26(void) __UNUSED;
static bool nrf54l_errata_27(void) __UNUSED;
static bool nrf54l_errata_30(void) __UNUSED;
static bool nrf54l_errata_31(void) __UNUSED;
static bool nrf54l_errata_32(void) __UNUSED;
static bool nrf54l_errata_33(void) __UNUSED;
static bool nrf54l_errata_35(void) __UNUSED;
static bool nrf54l_errata_37(void) __UNUSED;
static bool nrf54l_errata_38(void) __UNUSED;
static bool nrf54l_errata_39(void) __UNUSED;
static bool nrf54l_errata_40(void) __UNUSED;
static bool nrf54l_errata_41(void) __UNUSED;
static bool nrf54l_errata_42(void) __UNUSED;
static bool nrf54l_errata_43(void) __UNUSED;
static bool nrf54l_errata_44(void) __UNUSED;
static bool nrf54l_errata_45(void) __UNUSED;
static bool nrf54l_errata_46(void) __UNUSED;
static bool nrf54l_errata_47(void) __UNUSED;
static bool nrf54l_errata_48(void) __UNUSED;
static bool nrf54l_errata_49(void) __UNUSED;
static bool nrf54l_errata_50(void) __UNUSED;
static bool nrf54l_errata_55(void) __UNUSED;
static bool nrf54l_configuration_56(void) __UNUSED;

/* ========= Errata 1 ========= */
#if    defined (NRF54L05_XXAA) || defined (DEVELOP_IN_NRF54L05) \
    || defined (NRF54L10_XXAA) || defined (DEVELOP_IN_NRF54L10) \
    || defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15)
    #define NRF54L_ERRATA_1_PRESENT 1
#else
    #define NRF54L_ERRATA_1_PRESENT 0
#endif

#ifndef NRF54L_ERRATA_1_ENABLE_WORKAROUND
    #define NRF54L_ERRATA_1_ENABLE_WORKAROUND NRF54L_ERRATA_1_PRESENT
#endif

static bool nrf54l_errata_1(void)
{
    #if defined (DISABLE_WORKAROUND_1)
        return false;
    #elif !defined(NRF54L_SERIES)
        return false;
    #else
        #if defined (NRF54L05_XXAA) || defined (DEVELOP_IN_NRF54L05)\
         || defined (NRF54L10_XXAA) || defined (DEVELOP_IN_NRF54L10)\
         || defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15)
            uint32_t var1 = *(uint32_t *)0x00FFC340ul;
            uint32_t var2 = *(uint32_t *)0x00FFC344ul;
        #endif
        #if defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15)
            if (var1 == 0x1C)
            {
                switch(var2)
                {
                    case 0x01ul:
                        return true;
                    case 0x02ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        #if defined (NRF54L10_XXAA) || defined (DEVELOP_IN_NRF54L10)
            if (var1 == 0x2E)
            {
                switch(var2)
                {
                    case 0x01ul:
                        return true;
                    case 0x02ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        #if defined (NRF54L05_XXAA) || defined (DEVELOP_IN_NRF54L05)
            if (var1 == 0x2F)
            {
                switch(var2)
                {
                    case 0x01ul:
                        return true;
                    case 0x02ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        return false;
    #endif
}

/* ========= Errata 2 ========= */
#define NRF54L_ERRATA_2_PRESENT 0

#ifndef NRF54L_ERRATA_2_ENABLE_WORKAROUND
    #define NRF54L_ERRATA_2_ENABLE_WORKAROUND NRF54L_ERRATA_2_PRESENT
#endif

static bool nrf54l_errata_2(void)
{
    #if defined (DISABLE_WORKAROUND_2)
        return false;
    #elif !defined(NRF54L_SERIES)
        return false;
    #else
        return false;
    #endif
}

/* ========= Errata 3 ========= */
#define NRF54L_ERRATA_3_PRESENT 0

#ifndef NRF54L_ERRATA_3_ENABLE_WORKAROUND
    #define NRF54L_ERRATA_3_ENABLE_WORKAROUND NRF54L_ERRATA_3_PRESENT
#endif

static bool nrf54l_errata_3(void)
{
    #if defined (DISABLE_WORKAROUND_3)
        return false;
    #elif !defined(NRF54L_SERIES)
        return false;
    #else
        return false;
    #endif
}

/* ========= Errata 4 ========= */
#define NRF54L_ERRATA_4_PRESENT 0

#ifndef NRF54L_ERRATA_4_ENABLE_WORKAROUND
    #define NRF54L_ERRATA_4_ENABLE_WORKAROUND NRF54L_ERRATA_4_PRESENT
#endif

static bool nrf54l_errata_4(void)
{
    #if defined (DISABLE_WORKAROUND_4)
        return false;
    #elif !defined(NRF54L_SERIES)
        return false;
    #else
        return false;
    #endif
}

/* ========= Errata 6 ========= */
#if    defined (NRF54L05_XXAA) || defined (DEVELOP_IN_NRF54L05) \
    || defined (NRF54L10_XXAA) || defined (DEVELOP_IN_NRF54L10) \
    || defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15) \
    || defined (NRF54LM20A_ENGA_XXAA) || defined (DEVELOP_IN_NRF54LM20A_ENGA)
    #define NRF54L_ERRATA_6_PRESENT 1
#else
    #define NRF54L_ERRATA_6_PRESENT 0
#endif

#ifndef NRF54L_ERRATA_6_ENABLE_WORKAROUND
    #define NRF54L_ERRATA_6_ENABLE_WORKAROUND NRF54L_ERRATA_6_PRESENT
#endif

static bool nrf54l_errata_6(void)
{
    #if defined (DISABLE_WORKAROUND_6)
        return false;
    #elif !defined(NRF54L_SERIES)
        return false;
    #else
        #if defined (NRF54L05_XXAA) || defined (DEVELOP_IN_NRF54L05)\
         || defined (NRF54L10_XXAA) || defined (DEVELOP_IN_NRF54L10)\
         || defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15)\
         || defined (NRF54LM20A_ENGA_XXAA) || defined (DEVELOP_IN_NRF54LM20A_ENGA)
            uint32_t var1 = *(uint32_t *)0x00FFC340ul;
            uint32_t var2 = *(uint32_t *)0x00FFC344ul;
        #endif
        #if defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15)
            if (var1 == 0x1C)
            {
                switch(var2)
                {
                    case 0x01ul:
                        return true;
                    case 0x02ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        #if defined (NRF54LM20A_ENGA_XXAA) || defined (DEVELOP_IN_NRF54LM20A_ENGA)
            if (var1 == 0x29)
            {
                switch(var2)
                {
                    case 0x00ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        #if defined (NRF54L10_XXAA) || defined (DEVELOP_IN_NRF54L10)
            if (var1 == 0x2E)
            {
                switch(var2)
                {
                    case 0x01ul:
                        return true;
                    case 0x02ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        #if defined (NRF54L05_XXAA) || defined (DEVELOP_IN_NRF54L05)
            if (var1 == 0x2F)
            {
                switch(var2)
                {
                    case 0x01ul:
                        return true;
                    case 0x02ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        return false;
    #endif
}

/* ========= Errata 7 ========= */
#if    defined (NRF54L05_XXAA) || defined (DEVELOP_IN_NRF54L05) \
    || defined (NRF54L10_XXAA) || defined (DEVELOP_IN_NRF54L10) \
    || defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15) \
    || defined (NRF54LM20A_ENGA_XXAA) || defined (DEVELOP_IN_NRF54LM20A_ENGA)
    #define NRF54L_ERRATA_7_PRESENT 1
#else
    #define NRF54L_ERRATA_7_PRESENT 0
#endif

#ifndef NRF54L_ERRATA_7_ENABLE_WORKAROUND
    #define NRF54L_ERRATA_7_ENABLE_WORKAROUND NRF54L_ERRATA_7_PRESENT
#endif

static bool nrf54l_errata_7(void)
{
    #if defined (DISABLE_WORKAROUND_7)
        return false;
    #elif !defined(NRF54L_SERIES)
        return false;
    #else
        #if defined (NRF54L05_XXAA) || defined (DEVELOP_IN_NRF54L05)\
         || defined (NRF54L10_XXAA) || defined (DEVELOP_IN_NRF54L10)\
         || defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15)\
         || defined (NRF54LM20A_ENGA_XXAA) || defined (DEVELOP_IN_NRF54LM20A_ENGA)
            uint32_t var1 = *(uint32_t *)0x00FFC340ul;
            uint32_t var2 = *(uint32_t *)0x00FFC344ul;
        #endif
        #if defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15)
            if (var1 == 0x1C)
            {
                switch(var2)
                {
                    case 0x01ul:
                        return true;
                    case 0x02ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        #if defined (NRF54LM20A_ENGA_XXAA) || defined (DEVELOP_IN_NRF54LM20A_ENGA)
            if (var1 == 0x29)
            {
                switch(var2)
                {
                    case 0x00ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        #if defined (NRF54L10_XXAA) || defined (DEVELOP_IN_NRF54L10)
            if (var1 == 0x2E)
            {
                switch(var2)
                {
                    case 0x01ul:
                        return true;
                    case 0x02ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        #if defined (NRF54L05_XXAA) || defined (DEVELOP_IN_NRF54L05)
            if (var1 == 0x2F)
            {
                switch(var2)
                {
                    case 0x01ul:
                        return true;
                    case 0x02ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        return false;
    #endif
}

/* ========= Errata 8 ========= */
#if    defined (NRF54L05_XXAA) || defined (DEVELOP_IN_NRF54L05) \
    || defined (NRF54L10_XXAA) || defined (DEVELOP_IN_NRF54L10) \
    || defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15) \
    || defined (NRF54LM20A_ENGA_XXAA) || defined (DEVELOP_IN_NRF54LM20A_ENGA)
    #define NRF54L_ERRATA_8_PRESENT 1
#else
    #define NRF54L_ERRATA_8_PRESENT 0
#endif

#ifndef NRF54L_ERRATA_8_ENABLE_WORKAROUND
    #define NRF54L_ERRATA_8_ENABLE_WORKAROUND NRF54L_ERRATA_8_PRESENT
#endif

static bool nrf54l_errata_8(void)
{
    #if defined (DISABLE_WORKAROUND_8)
        return false;
    #elif !defined(NRF54L_SERIES)
        return false;
    #else
        #if defined (NRF54L05_XXAA) || defined (DEVELOP_IN_NRF54L05)\
         || defined (NRF54L10_XXAA) || defined (DEVELOP_IN_NRF54L10)\
         || defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15)\
         || defined (NRF54LM20A_ENGA_XXAA) || defined (DEVELOP_IN_NRF54LM20A_ENGA)
            uint32_t var1 = *(uint32_t *)0x00FFC340ul;
            uint32_t var2 = *(uint32_t *)0x00FFC344ul;
        #endif
        #if defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15)
            if (var1 == 0x1C)
            {
                switch(var2)
                {
                    case 0x01ul:
                        return true;
                    case 0x02ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        #if defined (NRF54LM20A_ENGA_XXAA) || defined (DEVELOP_IN_NRF54LM20A_ENGA)
            if (var1 == 0x29)
            {
                switch(var2)
                {
                    case 0x00ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        #if defined (NRF54L10_XXAA) || defined (DEVELOP_IN_NRF54L10)
            if (var1 == 0x2E)
            {
                switch(var2)
                {
                    case 0x01ul:
                        return true;
                    case 0x02ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        #if defined (NRF54L05_XXAA) || defined (DEVELOP_IN_NRF54L05)
            if (var1 == 0x2F)
            {
                switch(var2)
                {
                    case 0x01ul:
                        return true;
                    case 0x02ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        return false;
    #endif
}

/* ========= Errata 9 ========= */
#if    defined (NRF54L05_XXAA) || defined (DEVELOP_IN_NRF54L05) \
    || defined (NRF54L10_XXAA) || defined (DEVELOP_IN_NRF54L10) \
    || defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15)
    #define NRF54L_ERRATA_9_PRESENT 1
#else
    #define NRF54L_ERRATA_9_PRESENT 0
#endif

#ifndef NRF54L_ERRATA_9_ENABLE_WORKAROUND
    #define NRF54L_ERRATA_9_ENABLE_WORKAROUND NRF54L_ERRATA_9_PRESENT
#endif

static bool nrf54l_errata_9(void)
{
    #if defined (DISABLE_WORKAROUND_9)
        return false;
    #elif !defined(NRF54L_SERIES)
        return false;
    #else
        #if defined (NRF54L05_XXAA) || defined (DEVELOP_IN_NRF54L05)\
         || defined (NRF54L10_XXAA) || defined (DEVELOP_IN_NRF54L10)\
         || defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15)
            uint32_t var1 = *(uint32_t *)0x00FFC340ul;
            uint32_t var2 = *(uint32_t *)0x00FFC344ul;
        #endif
        #if defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15)
            if (var1 == 0x1C)
            {
                switch(var2)
                {
                    case 0x01ul:
                        return true;
                    case 0x02ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        #if defined (NRF54L10_XXAA) || defined (DEVELOP_IN_NRF54L10)
            if (var1 == 0x2E)
            {
                switch(var2)
                {
                    case 0x01ul:
                        return true;
                    case 0x02ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        #if defined (NRF54L05_XXAA) || defined (DEVELOP_IN_NRF54L05)
            if (var1 == 0x2F)
            {
                switch(var2)
                {
                    case 0x01ul:
                        return true;
                    case 0x02ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        return false;
    #endif
}

/* ========= Errata 10 ========= */
#if    defined (NRF54L05_XXAA) || defined (DEVELOP_IN_NRF54L05) \
    || defined (NRF54L10_XXAA) || defined (DEVELOP_IN_NRF54L10) \
    || defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15)
    #define NRF54L_ERRATA_10_PRESENT 1
#else
    #define NRF54L_ERRATA_10_PRESENT 0
#endif

#ifndef NRF54L_ERRATA_10_ENABLE_WORKAROUND
    #define NRF54L_ERRATA_10_ENABLE_WORKAROUND NRF54L_ERRATA_10_PRESENT
#endif

static bool nrf54l_errata_10(void)
{
    #if defined (DISABLE_WORKAROUND_10)
        return false;
    #elif !defined(NRF54L_SERIES)
        return false;
    #else
        #if defined (NRF54L05_XXAA) || defined (DEVELOP_IN_NRF54L05)\
         || defined (NRF54L10_XXAA) || defined (DEVELOP_IN_NRF54L10)\
         || defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15)
            uint32_t var1 = *(uint32_t *)0x00FFC340ul;
            uint32_t var2 = *(uint32_t *)0x00FFC344ul;
        #endif
        #if defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15)
            if (var1 == 0x1C)
            {
                switch(var2)
                {
                    case 0x01ul:
                        return true;
                    case 0x02ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        #if defined (NRF54L10_XXAA) || defined (DEVELOP_IN_NRF54L10)
            if (var1 == 0x2E)
            {
                switch(var2)
                {
                    case 0x01ul:
                        return true;
                    case 0x02ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        #if defined (NRF54L05_XXAA) || defined (DEVELOP_IN_NRF54L05)
            if (var1 == 0x2F)
            {
                switch(var2)
                {
                    case 0x01ul:
                        return true;
                    case 0x02ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        return false;
    #endif
}

/* ========= Errata 13 ========= */
#if    defined (NRF54L05_XXAA) || defined (DEVELOP_IN_NRF54L05) \
    || defined (NRF54L10_XXAA) || defined (DEVELOP_IN_NRF54L10) \
    || defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15)
    #define NRF54L_ERRATA_13_PRESENT 1
#else
    #define NRF54L_ERRATA_13_PRESENT 0
#endif

#ifndef NRF54L_ERRATA_13_ENABLE_WORKAROUND
    #define NRF54L_ERRATA_13_ENABLE_WORKAROUND NRF54L_ERRATA_13_PRESENT
#endif

static bool nrf54l_errata_13(void)
{
    #if defined (DISABLE_WORKAROUND_13)
        return false;
    #elif !defined(NRF54L_SERIES)
        return false;
    #else
        #if defined (NRF54L05_XXAA) || defined (DEVELOP_IN_NRF54L05)\
         || defined (NRF54L10_XXAA) || defined (DEVELOP_IN_NRF54L10)\
         || defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15)
            uint32_t var1 = *(uint32_t *)0x00FFC340ul;
            uint32_t var2 = *(uint32_t *)0x00FFC344ul;
        #endif
        #if defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15)
            if (var1 == 0x1C)
            {
                switch(var2)
                {
                    case 0x01ul:
                        return true;
                    case 0x02ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        #if defined (NRF54L10_XXAA) || defined (DEVELOP_IN_NRF54L10)
            if (var1 == 0x2E)
            {
                switch(var2)
                {
                    case 0x01ul:
                        return true;
                    case 0x02ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        #if defined (NRF54L05_XXAA) || defined (DEVELOP_IN_NRF54L05)
            if (var1 == 0x2F)
            {
                switch(var2)
                {
                    case 0x01ul:
                        return true;
                    case 0x02ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        return false;
    #endif
}

/* ========= Errata 16 ========= */
#if    defined (NRF54L05_XXAA) || defined (DEVELOP_IN_NRF54L05) \
    || defined (NRF54L10_XXAA) || defined (DEVELOP_IN_NRF54L10) \
    || defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15)
    #define NRF54L_ERRATA_16_PRESENT 1
#else
    #define NRF54L_ERRATA_16_PRESENT 0
#endif

#ifndef NRF54L_ERRATA_16_ENABLE_WORKAROUND
    #define NRF54L_ERRATA_16_ENABLE_WORKAROUND NRF54L_ERRATA_16_PRESENT
#endif

static bool nrf54l_errata_16(void)
{
    #if defined (DISABLE_WORKAROUND_16)
        return false;
    #elif !defined(NRF54L_SERIES)
        return false;
    #else
        #if defined (NRF54L05_XXAA) || defined (DEVELOP_IN_NRF54L05)\
         || defined (NRF54L10_XXAA) || defined (DEVELOP_IN_NRF54L10)\
         || defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15)
            uint32_t var1 = *(uint32_t *)0x00FFC340ul;
            uint32_t var2 = *(uint32_t *)0x00FFC344ul;
        #endif
        #if defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15)
            if (var1 == 0x1C)
            {
                switch(var2)
                {
                    case 0x01ul:
                        return true;
                    case 0x02ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        #if defined (NRF54L10_XXAA) || defined (DEVELOP_IN_NRF54L10)
            if (var1 == 0x2E)
            {
                switch(var2)
                {
                    case 0x01ul:
                        return true;
                    case 0x02ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        #if defined (NRF54L05_XXAA) || defined (DEVELOP_IN_NRF54L05)
            if (var1 == 0x2F)
            {
                switch(var2)
                {
                    case 0x01ul:
                        return true;
                    case 0x02ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        return false;
    #endif
}

/* ========= Errata 17 ========= */
#if    defined (NRF54L05_XXAA) || defined (DEVELOP_IN_NRF54L05) \
    || defined (NRF54L10_XXAA) || defined (DEVELOP_IN_NRF54L10) \
    || defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15)
    #define NRF54L_ERRATA_17_PRESENT 1
#else
    #define NRF54L_ERRATA_17_PRESENT 0
#endif

#ifndef NRF54L_ERRATA_17_ENABLE_WORKAROUND
    #define NRF54L_ERRATA_17_ENABLE_WORKAROUND NRF54L_ERRATA_17_PRESENT
#endif

static bool nrf54l_errata_17(void)
{
    #if defined (DISABLE_WORKAROUND_17)
        return false;
    #elif !defined(NRF54L_SERIES)
        return false;
    #else
        #if defined (NRF54L05_XXAA) || defined (DEVELOP_IN_NRF54L05)\
         || defined (NRF54L10_XXAA) || defined (DEVELOP_IN_NRF54L10)\
         || defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15)
            uint32_t var1 = *(uint32_t *)0x00FFC340ul;
            uint32_t var2 = *(uint32_t *)0x00FFC344ul;
        #endif
        #if defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15)
            if (var1 == 0x1C)
            {
                switch(var2)
                {
                    case 0x01ul:
                        return true;
                    case 0x02ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        #if defined (NRF54L10_XXAA) || defined (DEVELOP_IN_NRF54L10)
            if (var1 == 0x2E)
            {
                switch(var2)
                {
                    case 0x01ul:
                        return true;
                    case 0x02ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        #if defined (NRF54L05_XXAA) || defined (DEVELOP_IN_NRF54L05)
            if (var1 == 0x2F)
            {
                switch(var2)
                {
                    case 0x01ul:
                        return true;
                    case 0x02ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        return false;
    #endif
}

/* ========= Errata 18 ========= */
#if    defined (NRF54L05_XXAA) || defined (DEVELOP_IN_NRF54L05) \
    || defined (NRF54L10_XXAA) || defined (DEVELOP_IN_NRF54L10) \
    || defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15)
    #define NRF54L_ERRATA_18_PRESENT 1
#else
    #define NRF54L_ERRATA_18_PRESENT 0
#endif

#ifndef NRF54L_ERRATA_18_ENABLE_WORKAROUND
    #define NRF54L_ERRATA_18_ENABLE_WORKAROUND NRF54L_ERRATA_18_PRESENT
#endif

static bool nrf54l_errata_18(void)
{
    #if defined (DISABLE_WORKAROUND_18)
        return false;
    #elif !defined(NRF54L_SERIES)
        return false;
    #else
        #if defined (NRF54L05_XXAA) || defined (DEVELOP_IN_NRF54L05)\
         || defined (NRF54L10_XXAA) || defined (DEVELOP_IN_NRF54L10)\
         || defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15)
            uint32_t var1 = *(uint32_t *)0x00FFC340ul;
            uint32_t var2 = *(uint32_t *)0x00FFC344ul;
        #endif
        #if defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15)
            if (var1 == 0x1C)
            {
                switch(var2)
                {
                    case 0x01ul:
                        return true;
                    case 0x02ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        #if defined (NRF54L10_XXAA) || defined (DEVELOP_IN_NRF54L10)
            if (var1 == 0x2E)
            {
                switch(var2)
                {
                    case 0x01ul:
                        return true;
                    case 0x02ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        #if defined (NRF54L05_XXAA) || defined (DEVELOP_IN_NRF54L05)
            if (var1 == 0x2F)
            {
                switch(var2)
                {
                    case 0x01ul:
                        return true;
                    case 0x02ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        return false;
    #endif
}

/* ========= Errata 19 ========= */
#if    defined (NRF54L05_XXAA) || defined (DEVELOP_IN_NRF54L05) \
    || defined (NRF54L10_XXAA) || defined (DEVELOP_IN_NRF54L10) \
    || defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15)
    #define NRF54L_ERRATA_19_PRESENT 1
#else
    #define NRF54L_ERRATA_19_PRESENT 0
#endif

#ifndef NRF54L_ERRATA_19_ENABLE_WORKAROUND
    #define NRF54L_ERRATA_19_ENABLE_WORKAROUND NRF54L_ERRATA_19_PRESENT
#endif

static bool nrf54l_errata_19(void)
{
    #if defined (DISABLE_WORKAROUND_19)
        return false;
    #elif !defined(NRF54L_SERIES)
        return false;
    #else
        #if defined (NRF54L05_XXAA) || defined (DEVELOP_IN_NRF54L05)\
         || defined (NRF54L10_XXAA) || defined (DEVELOP_IN_NRF54L10)\
         || defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15)
            uint32_t var1 = *(uint32_t *)0x00FFC340ul;
            uint32_t var2 = *(uint32_t *)0x00FFC344ul;
        #endif
        #if defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15)
            if (var1 == 0x1C)
            {
                switch(var2)
                {
                    case 0x01ul:
                        return true;
                    case 0x02ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        #if defined (NRF54L10_XXAA) || defined (DEVELOP_IN_NRF54L10)
            if (var1 == 0x2E)
            {
                switch(var2)
                {
                    case 0x01ul:
                        return true;
                    case 0x02ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        #if defined (NRF54L05_XXAA) || defined (DEVELOP_IN_NRF54L05)
            if (var1 == 0x2F)
            {
                switch(var2)
                {
                    case 0x01ul:
                        return true;
                    case 0x02ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        return false;
    #endif
}

/* ========= Errata 20 ========= */
#if    defined (NRF54L05_XXAA) || defined (DEVELOP_IN_NRF54L05) \
    || defined (NRF54L10_XXAA) || defined (DEVELOP_IN_NRF54L10) \
    || defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15)
    #define NRF54L_ERRATA_20_PRESENT 1
#else
    #define NRF54L_ERRATA_20_PRESENT 0
#endif

#ifndef NRF54L_ERRATA_20_ENABLE_WORKAROUND
    #define NRF54L_ERRATA_20_ENABLE_WORKAROUND NRF54L_ERRATA_20_PRESENT
#endif

static bool nrf54l_errata_20(void)
{
    #if defined (DISABLE_WORKAROUND_20)
        return false;
    #elif !defined(NRF54L_SERIES)
        return false;
    #else
        #if defined (NRF54L05_XXAA) || defined (DEVELOP_IN_NRF54L05)\
         || defined (NRF54L10_XXAA) || defined (DEVELOP_IN_NRF54L10)\
         || defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15)
            uint32_t var1 = *(uint32_t *)0x00FFC340ul;
            uint32_t var2 = *(uint32_t *)0x00FFC344ul;
        #endif
        #if defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15)
            if (var1 == 0x1C)
            {
                switch(var2)
                {
                    case 0x01ul:
                        return true;
                    case 0x02ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        #if defined (NRF54L10_XXAA) || defined (DEVELOP_IN_NRF54L10)
            if (var1 == 0x2E)
            {
                switch(var2)
                {
                    case 0x01ul:
                        return true;
                    case 0x02ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        #if defined (NRF54L05_XXAA) || defined (DEVELOP_IN_NRF54L05)
            if (var1 == 0x2F)
            {
                switch(var2)
                {
                    case 0x01ul:
                        return true;
                    case 0x02ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        return false;
    #endif
}

/* ========= Errata 21 ========= */
#if    defined (NRF54L05_XXAA) || defined (DEVELOP_IN_NRF54L05) \
    || defined (NRF54L10_XXAA) || defined (DEVELOP_IN_NRF54L10) \
    || defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15)
    #define NRF54L_ERRATA_21_PRESENT 1
#else
    #define NRF54L_ERRATA_21_PRESENT 0
#endif

#ifndef NRF54L_ERRATA_21_ENABLE_WORKAROUND
    #define NRF54L_ERRATA_21_ENABLE_WORKAROUND NRF54L_ERRATA_21_PRESENT
#endif

static bool nrf54l_errata_21(void)
{
    #if defined (DISABLE_WORKAROUND_21)
        return false;
    #elif !defined(NRF54L_SERIES)
        return false;
    #else
        #if defined (NRF54L05_XXAA) || defined (DEVELOP_IN_NRF54L05)\
         || defined (NRF54L10_XXAA) || defined (DEVELOP_IN_NRF54L10)\
         || defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15)
            uint32_t var1 = *(uint32_t *)0x00FFC340ul;
            uint32_t var2 = *(uint32_t *)0x00FFC344ul;
        #endif
        #if defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15)
            if (var1 == 0x1C)
            {
                switch(var2)
                {
                    case 0x01ul:
                        return true;
                    case 0x02ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        #if defined (NRF54L10_XXAA) || defined (DEVELOP_IN_NRF54L10)
            if (var1 == 0x2E)
            {
                switch(var2)
                {
                    case 0x01ul:
                        return true;
                    case 0x02ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        #if defined (NRF54L05_XXAA) || defined (DEVELOP_IN_NRF54L05)
            if (var1 == 0x2F)
            {
                switch(var2)
                {
                    case 0x01ul:
                        return true;
                    case 0x02ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        return false;
    #endif
}

/* ========= Errata 22 ========= */
#if    defined (NRF54L05_XXAA) || defined (DEVELOP_IN_NRF54L05) \
    || defined (NRF54L10_XXAA) || defined (DEVELOP_IN_NRF54L10) \
    || defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15)
    #define NRF54L_ERRATA_22_PRESENT 1
#else
    #define NRF54L_ERRATA_22_PRESENT 0
#endif

#ifndef NRF54L_ERRATA_22_ENABLE_WORKAROUND
    #define NRF54L_ERRATA_22_ENABLE_WORKAROUND NRF54L_ERRATA_22_PRESENT
#endif

static bool nrf54l_errata_22(void)
{
    #if defined (DISABLE_WORKAROUND_22)
        return false;
    #elif !defined(NRF54L_SERIES)
        return false;
    #else
        #if defined (NRF54L05_XXAA) || defined (DEVELOP_IN_NRF54L05)\
         || defined (NRF54L10_XXAA) || defined (DEVELOP_IN_NRF54L10)\
         || defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15)
            uint32_t var1 = *(uint32_t *)0x00FFC340ul;
            uint32_t var2 = *(uint32_t *)0x00FFC344ul;
        #endif
        #if defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15)
            if (var1 == 0x1C)
            {
                switch(var2)
                {
                    case 0x01ul:
                        return true;
                    case 0x02ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        #if defined (NRF54L10_XXAA) || defined (DEVELOP_IN_NRF54L10)
            if (var1 == 0x2E)
            {
                switch(var2)
                {
                    case 0x01ul:
                        return true;
                    case 0x02ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        #if defined (NRF54L05_XXAA) || defined (DEVELOP_IN_NRF54L05)
            if (var1 == 0x2F)
            {
                switch(var2)
                {
                    case 0x01ul:
                        return true;
                    case 0x02ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        return false;
    #endif
}

/* ========= Errata 23 ========= */
#if    defined (NRF54L05_XXAA) || defined (DEVELOP_IN_NRF54L05) \
    || defined (NRF54L10_XXAA) || defined (DEVELOP_IN_NRF54L10) \
    || defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15) \
    || defined (NRF54LM20A_ENGA_XXAA) || defined (DEVELOP_IN_NRF54LM20A_ENGA)
    #define NRF54L_ERRATA_23_PRESENT 1
#else
    #define NRF54L_ERRATA_23_PRESENT 0
#endif

#ifndef NRF54L_ERRATA_23_ENABLE_WORKAROUND
    #define NRF54L_ERRATA_23_ENABLE_WORKAROUND NRF54L_ERRATA_23_PRESENT
#endif

static bool nrf54l_errata_23(void)
{
    #if defined (DISABLE_WORKAROUND_23)
        return false;
    #elif !defined(NRF54L_SERIES)
        return false;
    #else
        #if defined (NRF54L05_XXAA) || defined (DEVELOP_IN_NRF54L05)\
         || defined (NRF54L10_XXAA) || defined (DEVELOP_IN_NRF54L10)\
         || defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15)\
         || defined (NRF54LM20A_ENGA_XXAA) || defined (DEVELOP_IN_NRF54LM20A_ENGA)
            uint32_t var1 = *(uint32_t *)0x00FFC340ul;
            uint32_t var2 = *(uint32_t *)0x00FFC344ul;
        #endif
        #if defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15)
            if (var1 == 0x1C)
            {
                switch(var2)
                {
                    case 0x01ul:
                        return true;
                    case 0x02ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        #if defined (NRF54LM20A_ENGA_XXAA) || defined (DEVELOP_IN_NRF54LM20A_ENGA)
            if (var1 == 0x29)
            {
                switch(var2)
                {
                    case 0x00ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        #if defined (NRF54L10_XXAA) || defined (DEVELOP_IN_NRF54L10)
            if (var1 == 0x2E)
            {
                switch(var2)
                {
                    case 0x01ul:
                        return true;
                    case 0x02ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        #if defined (NRF54L05_XXAA) || defined (DEVELOP_IN_NRF54L05)
            if (var1 == 0x2F)
            {
                switch(var2)
                {
                    case 0x01ul:
                        return true;
                    case 0x02ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        return false;
    #endif
}

/* ========= Errata 24 ========= */
#if    defined (NRF54L05_XXAA) || defined (DEVELOP_IN_NRF54L05) \
    || defined (NRF54L10_XXAA) || defined (DEVELOP_IN_NRF54L10) \
    || defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15)
    #define NRF54L_ERRATA_24_PRESENT 1
#else
    #define NRF54L_ERRATA_24_PRESENT 0
#endif

#ifndef NRF54L_ERRATA_24_ENABLE_WORKAROUND
    #define NRF54L_ERRATA_24_ENABLE_WORKAROUND NRF54L_ERRATA_24_PRESENT
#endif

static bool nrf54l_errata_24(void)
{
    #if defined (DISABLE_WORKAROUND_24)
        return false;
    #elif !defined(NRF54L_SERIES)
        return false;
    #else
        #if defined (NRF54L05_XXAA) || defined (DEVELOP_IN_NRF54L05)\
         || defined (NRF54L10_XXAA) || defined (DEVELOP_IN_NRF54L10)\
         || defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15)
            uint32_t var1 = *(uint32_t *)0x00FFC340ul;
            uint32_t var2 = *(uint32_t *)0x00FFC344ul;
        #endif
        #if defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15)
            if (var1 == 0x1C)
            {
                switch(var2)
                {
                    case 0x01ul:
                        return true;
                    case 0x02ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        #if defined (NRF54L10_XXAA) || defined (DEVELOP_IN_NRF54L10)
            if (var1 == 0x2E)
            {
                switch(var2)
                {
                    case 0x01ul:
                        return true;
                    case 0x02ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        #if defined (NRF54L05_XXAA) || defined (DEVELOP_IN_NRF54L05)
            if (var1 == 0x2F)
            {
                switch(var2)
                {
                    case 0x01ul:
                        return true;
                    case 0x02ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        return false;
    #endif
}

/* ========= Errata 25 ========= */
#if    defined (NRF54L05_XXAA) || defined (DEVELOP_IN_NRF54L05) \
    || defined (NRF54L10_XXAA) || defined (DEVELOP_IN_NRF54L10) \
    || defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15)
    #define NRF54L_ERRATA_25_PRESENT 1
#else
    #define NRF54L_ERRATA_25_PRESENT 0
#endif

#ifndef NRF54L_ERRATA_25_ENABLE_WORKAROUND
    #define NRF54L_ERRATA_25_ENABLE_WORKAROUND NRF54L_ERRATA_25_PRESENT
#endif

static bool nrf54l_errata_25(void)
{
    #if defined (DISABLE_WORKAROUND_25)
        return false;
    #elif !defined(NRF54L_SERIES)
        return false;
    #else
        #if defined (NRF54L05_XXAA) || defined (DEVELOP_IN_NRF54L05)\
         || defined (NRF54L10_XXAA) || defined (DEVELOP_IN_NRF54L10)\
         || defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15)
            uint32_t var1 = *(uint32_t *)0x00FFC340ul;
            uint32_t var2 = *(uint32_t *)0x00FFC344ul;
        #endif
        #if defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15)
            if (var1 == 0x1C)
            {
                switch(var2)
                {
                    case 0x01ul:
                        return true;
                    case 0x02ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        #if defined (NRF54L10_XXAA) || defined (DEVELOP_IN_NRF54L10)
            if (var1 == 0x2E)
            {
                switch(var2)
                {
                    case 0x01ul:
                        return true;
                    case 0x02ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        #if defined (NRF54L05_XXAA) || defined (DEVELOP_IN_NRF54L05)
            if (var1 == 0x2F)
            {
                switch(var2)
                {
                    case 0x01ul:
                        return true;
                    case 0x02ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        return false;
    #endif
}

/* ========= Errata 26 ========= */
#if    defined (NRF54L05_XXAA) || defined (DEVELOP_IN_NRF54L05) \
    || defined (NRF54L10_XXAA) || defined (DEVELOP_IN_NRF54L10) \
    || defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15) \
    || defined (NRF54LM20A_ENGA_XXAA) || defined (DEVELOP_IN_NRF54LM20A_ENGA)
    #define NRF54L_ERRATA_26_PRESENT 1
#else
    #define NRF54L_ERRATA_26_PRESENT 0
#endif

#ifndef NRF54L_ERRATA_26_ENABLE_WORKAROUND
    #define NRF54L_ERRATA_26_ENABLE_WORKAROUND NRF54L_ERRATA_26_PRESENT
#endif

static bool nrf54l_errata_26(void)
{
    #if defined (DISABLE_WORKAROUND_26)
        return false;
    #elif !defined(NRF54L_SERIES)
        return false;
    #else
        #if defined (NRF54L05_XXAA) || defined (DEVELOP_IN_NRF54L05)\
         || defined (NRF54L10_XXAA) || defined (DEVELOP_IN_NRF54L10)\
         || defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15)\
         || defined (NRF54LM20A_ENGA_XXAA) || defined (DEVELOP_IN_NRF54LM20A_ENGA)
            uint32_t var1 = *(uint32_t *)0x00FFC340ul;
            uint32_t var2 = *(uint32_t *)0x00FFC344ul;
        #endif
        #if defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15)
            if (var1 == 0x1C)
            {
                switch(var2)
                {
                    case 0x01ul:
                        return true;
                    case 0x02ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        #if defined (NRF54LM20A_ENGA_XXAA) || defined (DEVELOP_IN_NRF54LM20A_ENGA)
            if (var1 == 0x29)
            {
                switch(var2)
                {
                    case 0x00ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        #if defined (NRF54L10_XXAA) || defined (DEVELOP_IN_NRF54L10)
            if (var1 == 0x2E)
            {
                switch(var2)
                {
                    case 0x01ul:
                        return true;
                    case 0x02ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        #if defined (NRF54L05_XXAA) || defined (DEVELOP_IN_NRF54L05)
            if (var1 == 0x2F)
            {
                switch(var2)
                {
                    case 0x01ul:
                        return true;
                    case 0x02ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        return false;
    #endif
}

/* ========= Errata 27 ========= */
#if    defined (NRF54L05_XXAA) || defined (DEVELOP_IN_NRF54L05) \
    || defined (NRF54L10_XXAA) || defined (DEVELOP_IN_NRF54L10) \
    || defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15)
    #define NRF54L_ERRATA_27_PRESENT 1
#else
    #define NRF54L_ERRATA_27_PRESENT 0
#endif

#ifndef NRF54L_ERRATA_27_ENABLE_WORKAROUND
    #define NRF54L_ERRATA_27_ENABLE_WORKAROUND NRF54L_ERRATA_27_PRESENT
#endif

static bool nrf54l_errata_27(void)
{
    #if defined (DISABLE_WORKAROUND_27)
        return false;
    #elif !defined(NRF54L_SERIES)
        return false;
    #else
        #if defined (NRF54L05_XXAA) || defined (DEVELOP_IN_NRF54L05)\
         || defined (NRF54L10_XXAA) || defined (DEVELOP_IN_NRF54L10)\
         || defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15)
            uint32_t var1 = *(uint32_t *)0x00FFC340ul;
            uint32_t var2 = *(uint32_t *)0x00FFC344ul;
        #endif
        #if defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15)
            if (var1 == 0x1C)
            {
                switch(var2)
                {
                    case 0x01ul:
                        return true;
                    case 0x02ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        #if defined (NRF54L10_XXAA) || defined (DEVELOP_IN_NRF54L10)
            if (var1 == 0x2E)
            {
                switch(var2)
                {
                    case 0x01ul:
                        return true;
                    case 0x02ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        #if defined (NRF54L05_XXAA) || defined (DEVELOP_IN_NRF54L05)
            if (var1 == 0x2F)
            {
                switch(var2)
                {
                    case 0x01ul:
                        return true;
                    case 0x02ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        return false;
    #endif
}

/* ========= Errata 30 ========= */
#if    defined (NRF54L05_XXAA) || defined (DEVELOP_IN_NRF54L05) \
    || defined (NRF54L10_XXAA) || defined (DEVELOP_IN_NRF54L10) \
    || defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15)
    #define NRF54L_ERRATA_30_PRESENT 1
#else
    #define NRF54L_ERRATA_30_PRESENT 0
#endif

#ifndef NRF54L_ERRATA_30_ENABLE_WORKAROUND
    #define NRF54L_ERRATA_30_ENABLE_WORKAROUND NRF54L_ERRATA_30_PRESENT
#endif

static bool nrf54l_errata_30(void)
{
    #if defined (DISABLE_WORKAROUND_30)
        return false;
    #elif !defined(NRF54L_SERIES)
        return false;
    #else
        #if defined (NRF54L05_XXAA) || defined (DEVELOP_IN_NRF54L05)\
         || defined (NRF54L10_XXAA) || defined (DEVELOP_IN_NRF54L10)\
         || defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15)
            uint32_t var1 = *(uint32_t *)0x00FFC340ul;
            uint32_t var2 = *(uint32_t *)0x00FFC344ul;
        #endif
        #if defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15)
            if (var1 == 0x1C)
            {
                switch(var2)
                {
                    case 0x01ul:
                        return true;
                    case 0x02ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        #if defined (NRF54L10_XXAA) || defined (DEVELOP_IN_NRF54L10)
            if (var1 == 0x2E)
            {
                switch(var2)
                {
                    case 0x01ul:
                        return true;
                    case 0x02ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        #if defined (NRF54L05_XXAA) || defined (DEVELOP_IN_NRF54L05)
            if (var1 == 0x2F)
            {
                switch(var2)
                {
                    case 0x01ul:
                        return true;
                    case 0x02ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        return false;
    #endif
}

/* ========= Errata 31 ========= */
#if    defined (NRF54L05_XXAA) || defined (DEVELOP_IN_NRF54L05) \
    || defined (NRF54L10_XXAA) || defined (DEVELOP_IN_NRF54L10) \
    || defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15)
    #define NRF54L_ERRATA_31_PRESENT 1
#else
    #define NRF54L_ERRATA_31_PRESENT 0
#endif

#ifndef NRF54L_ERRATA_31_ENABLE_WORKAROUND
    #define NRF54L_ERRATA_31_ENABLE_WORKAROUND NRF54L_ERRATA_31_PRESENT
#endif

static bool nrf54l_errata_31(void)
{
    #if defined (DISABLE_WORKAROUND_31)
        return false;
    #elif !defined(NRF54L_SERIES)
        return false;
    #else
        #if defined (NRF54L05_XXAA) || defined (DEVELOP_IN_NRF54L05)\
         || defined (NRF54L10_XXAA) || defined (DEVELOP_IN_NRF54L10)\
         || defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15)
            uint32_t var1 = *(uint32_t *)0x00FFC340ul;
            uint32_t var2 = *(uint32_t *)0x00FFC344ul;
        #endif
        #if defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15)
            if (var1 == 0x1C)
            {
                switch(var2)
                {
                    case 0x01ul:
                        return true;
                    case 0x02ul:
                        return false;
                    default:
                        return false;
                }
            }
        #endif
        #if defined (NRF54L10_XXAA) || defined (DEVELOP_IN_NRF54L10)
            if (var1 == 0x2E)
            {
                switch(var2)
                {
                    case 0x01ul:
                        return true;
                    case 0x02ul:
                        return false;
                    default:
                        return false;
                }
            }
        #endif
        #if defined (NRF54L05_XXAA) || defined (DEVELOP_IN_NRF54L05)
            if (var1 == 0x2F)
            {
                switch(var2)
                {
                    case 0x01ul:
                        return true;
                    case 0x02ul:
                        return false;
                    default:
                        return false;
                }
            }
        #endif
        return false;
    #endif
}

/* ========= Errata 32 ========= */
#if    defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15)
    #define NRF54L_ERRATA_32_PRESENT 1
#else
    #define NRF54L_ERRATA_32_PRESENT 0
#endif

#ifndef NRF54L_ERRATA_32_ENABLE_WORKAROUND
    #define NRF54L_ERRATA_32_ENABLE_WORKAROUND NRF54L_ERRATA_32_PRESENT
#endif

static bool nrf54l_errata_32(void)
{
    #if defined (DISABLE_WORKAROUND_32)
        return false;
    #elif !defined(NRF54L_SERIES)
        return false;
    #else
        #if defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15)
            uint32_t var1 = *(uint32_t *)0x00FFC340ul;
            uint32_t var2 = *(uint32_t *)0x00FFC344ul;
        #endif
        #if defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15)
            if (var1 == 0x1C)
            {
                switch(var2)
                {
                    case 0x01ul:
                        return true;
                    case 0x02ul:
                        return false;
                    default:
                        return false;
                }
            }
        #endif
        return false;
    #endif
}

/* ========= Errata 33 ========= */
#if    defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15)
    #define NRF54L_ERRATA_33_PRESENT 1
#else
    #define NRF54L_ERRATA_33_PRESENT 0
#endif

#ifndef NRF54L_ERRATA_33_ENABLE_WORKAROUND
    #define NRF54L_ERRATA_33_ENABLE_WORKAROUND 0
#endif

static bool nrf54l_errata_33(void)
{
    #if defined (DISABLE_WORKAROUND_33)
        return false;
    #elif !defined(NRF54L_SERIES)
        return false;
    #else
        #if defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15)
            uint32_t var1 = *(uint32_t *)0x00FFC340ul;
            uint32_t var2 = *(uint32_t *)0x00FFC344ul;
        #endif
        #if defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15)
            if (var1 == 0x1C)
            {
                switch(var2)
                {
                    case 0x01ul:
                        return true;
                    case 0x02ul:
                        return false;
                    default:
                        return false;
                }
            }
        #endif
        return false;
    #endif
}

/* ========= Errata 35 ========= */
#if    defined (NRF54L05_XXAA) || defined (DEVELOP_IN_NRF54L05) \
    || defined (NRF54L10_XXAA) || defined (DEVELOP_IN_NRF54L10) \
    || defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15)
    #define NRF54L_ERRATA_35_PRESENT 1
#else
    #define NRF54L_ERRATA_35_PRESENT 0
#endif

#ifndef NRF54L_ERRATA_35_ENABLE_WORKAROUND
    #define NRF54L_ERRATA_35_ENABLE_WORKAROUND NRF54L_ERRATA_35_PRESENT
#endif

static bool nrf54l_errata_35(void)
{
    #if defined (DISABLE_WORKAROUND_35)
        return false;
    #elif !defined(NRF54L_SERIES)
        return false;
    #else
        #if defined (NRF54L05_XXAA) || defined (DEVELOP_IN_NRF54L05)\
         || defined (NRF54L10_XXAA) || defined (DEVELOP_IN_NRF54L10)\
         || defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15)
            uint32_t var1 = *(uint32_t *)0x00FFC340ul;
            uint32_t var2 = *(uint32_t *)0x00FFC344ul;
        #endif
        #if defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15)
            if (var1 == 0x1C)
            {
                switch(var2)
                {
                    case 0x01ul:
                        return true;
                    case 0x02ul:
                        return false;
                    default:
                        return false;
                }
            }
        #endif
        #if defined (NRF54L10_XXAA) || defined (DEVELOP_IN_NRF54L10)
            if (var1 == 0x2E)
            {
                switch(var2)
                {
                    case 0x01ul:
                        return true;
                    case 0x02ul:
                        return false;
                    default:
                        return false;
                }
            }
        #endif
        #if defined (NRF54L05_XXAA) || defined (DEVELOP_IN_NRF54L05)
            if (var1 == 0x2F)
            {
                switch(var2)
                {
                    case 0x01ul:
                        return true;
                    case 0x02ul:
                        return false;
                    default:
                        return false;
                }
            }
        #endif
        return false;
    #endif
}

/* ========= Errata 37 ========= */
#if    defined (NRF54L05_XXAA) || defined (DEVELOP_IN_NRF54L05) \
    || defined (NRF54L10_XXAA) || defined (DEVELOP_IN_NRF54L10) \
    || defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15) \
    || defined (NRF54LM20A_ENGA_XXAA) || defined (DEVELOP_IN_NRF54LM20A_ENGA)
    #define NRF54L_ERRATA_37_PRESENT 1
#else
    #define NRF54L_ERRATA_37_PRESENT 0
#endif

#ifndef NRF54L_ERRATA_37_ENABLE_WORKAROUND
    #define NRF54L_ERRATA_37_ENABLE_WORKAROUND NRF54L_ERRATA_37_PRESENT
#endif

static bool nrf54l_errata_37(void)
{
    #if defined (DISABLE_WORKAROUND_37)
        return false;
    #elif !defined(NRF54L_SERIES)
        return false;
    #else
        #if defined (NRF54L05_XXAA) || defined (DEVELOP_IN_NRF54L05)\
         || defined (NRF54L10_XXAA) || defined (DEVELOP_IN_NRF54L10)\
         || defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15)\
         || defined (NRF54LM20A_ENGA_XXAA) || defined (DEVELOP_IN_NRF54LM20A_ENGA)
            uint32_t var1 = *(uint32_t *)0x00FFC340ul;
            uint32_t var2 = *(uint32_t *)0x00FFC344ul;
        #endif
        #if defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15)
            if (var1 == 0x1C)
            {
                switch(var2)
                {
                    case 0x01ul:
                        return true;
                    case 0x02ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        #if defined (NRF54LM20A_ENGA_XXAA) || defined (DEVELOP_IN_NRF54LM20A_ENGA)
            if (var1 == 0x29)
            {
                switch(var2)
                {
                    case 0x00ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        #if defined (NRF54L10_XXAA) || defined (DEVELOP_IN_NRF54L10)
            if (var1 == 0x2E)
            {
                switch(var2)
                {
                    case 0x01ul:
                        return true;
                    case 0x02ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        #if defined (NRF54L05_XXAA) || defined (DEVELOP_IN_NRF54L05)
            if (var1 == 0x2F)
            {
                switch(var2)
                {
                    case 0x01ul:
                        return true;
                    case 0x02ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        return false;
    #endif
}

/* ========= Errata 38 ========= */
#if    defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15)
    #define NRF54L_ERRATA_38_PRESENT 1
#else
    #define NRF54L_ERRATA_38_PRESENT 0
#endif

#ifndef NRF54L_ERRATA_38_ENABLE_WORKAROUND
    #define NRF54L_ERRATA_38_ENABLE_WORKAROUND NRF54L_ERRATA_38_PRESENT
#endif

static bool nrf54l_errata_38(void)
{
    #if defined (DISABLE_WORKAROUND_38)
        return false;
    #elif !defined(NRF54L_SERIES)
        return false;
    #else
        #if defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15)
            uint32_t var1 = *(uint32_t *)0x00FFC340ul;
            uint32_t var2 = *(uint32_t *)0x00FFC344ul;
        #endif
        #if defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15)
            if (var1 == 0x1C)
            {
                switch(var2)
                {
                    case 0x01ul:
                        return true;
                    case 0x02ul:
                        return false;
                    default:
                        return false;
                }
            }
        #endif
        return false;
    #endif
}

/* ========= Errata 39 ========= */
#if    defined (NRF54L05_XXAA) || defined (DEVELOP_IN_NRF54L05) \
    || defined (NRF54L10_XXAA) || defined (DEVELOP_IN_NRF54L10) \
    || defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15)
    #define NRF54L_ERRATA_39_PRESENT 1
#else
    #define NRF54L_ERRATA_39_PRESENT 0
#endif

#ifndef NRF54L_ERRATA_39_ENABLE_WORKAROUND
    #define NRF54L_ERRATA_39_ENABLE_WORKAROUND NRF54L_ERRATA_39_PRESENT
#endif

static bool nrf54l_errata_39(void)
{
    #if defined (DISABLE_WORKAROUND_39)
        return false;
    #elif !defined(NRF54L_SERIES)
        return false;
    #else
        #if defined (NRF54L05_XXAA) || defined (DEVELOP_IN_NRF54L05)\
         || defined (NRF54L10_XXAA) || defined (DEVELOP_IN_NRF54L10)\
         || defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15)
            uint32_t var1 = *(uint32_t *)0x00FFC340ul;
            uint32_t var2 = *(uint32_t *)0x00FFC344ul;
        #endif
        #if defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15)
            if (var1 == 0x1C)
            {
                switch(var2)
                {
                    case 0x01ul:
                        return true;
                    case 0x02ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        #if defined (NRF54L10_XXAA) || defined (DEVELOP_IN_NRF54L10)
            if (var1 == 0x2E)
            {
                switch(var2)
                {
                    case 0x01ul:
                        return true;
                    case 0x02ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        #if defined (NRF54L05_XXAA) || defined (DEVELOP_IN_NRF54L05)
            if (var1 == 0x2F)
            {
                switch(var2)
                {
                    case 0x01ul:
                        return true;
                    case 0x02ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        return false;
    #endif
}

/* ========= Errata 40 ========= */
#if    defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15)
    #define NRF54L_ERRATA_40_PRESENT 1
#else
    #define NRF54L_ERRATA_40_PRESENT 0
#endif

#ifndef NRF54L_ERRATA_40_ENABLE_WORKAROUND
    #define NRF54L_ERRATA_40_ENABLE_WORKAROUND NRF54L_ERRATA_40_PRESENT
#endif

static bool nrf54l_errata_40(void)
{
    #if defined (DISABLE_WORKAROUND_40)
        return false;
    #elif !defined(NRF54L_SERIES)
        return false;
    #else
        #if defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15)
            uint32_t var1 = *(uint32_t *)0x00FFC340ul;
            uint32_t var2 = *(uint32_t *)0x00FFC344ul;
        #endif
        #if defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15)
            if (var1 == 0x1C)
            {
                switch(var2)
                {
                    case 0x01ul:
                        return true;
                    case 0x02ul:
                        return false;
                    default:
                        return false;
                }
            }
        #endif
        return false;
    #endif
}

/* ========= Errata 41 ========= */
#if    defined (NRF54L05_XXAA) || defined (DEVELOP_IN_NRF54L05) \
    || defined (NRF54L10_XXAA) || defined (DEVELOP_IN_NRF54L10) \
    || defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15) \
    || defined (NRF54LM20A_ENGA_XXAA) || defined (DEVELOP_IN_NRF54LM20A_ENGA)
    #define NRF54L_ERRATA_41_PRESENT 1
#else
    #define NRF54L_ERRATA_41_PRESENT 0
#endif

#ifndef NRF54L_ERRATA_41_ENABLE_WORKAROUND
    #define NRF54L_ERRATA_41_ENABLE_WORKAROUND NRF54L_ERRATA_41_PRESENT
#endif

static bool nrf54l_errata_41(void)
{
    #if defined (DISABLE_WORKAROUND_41)
        return false;
    #elif !defined(NRF54L_SERIES)
        return false;
    #else
        #if defined (NRF54L05_XXAA) || defined (DEVELOP_IN_NRF54L05)\
         || defined (NRF54L10_XXAA) || defined (DEVELOP_IN_NRF54L10)\
         || defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15)\
         || defined (NRF54LM20A_ENGA_XXAA) || defined (DEVELOP_IN_NRF54LM20A_ENGA)
            uint32_t var1 = *(uint32_t *)0x00FFC340ul;
            uint32_t var2 = *(uint32_t *)0x00FFC344ul;
        #endif
        #if defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15)
            if (var1 == 0x1C)
            {
                switch(var2)
                {
                    case 0x01ul:
                        return true;
                    case 0x02ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        #if defined (NRF54LM20A_ENGA_XXAA) || defined (DEVELOP_IN_NRF54LM20A_ENGA)
            if (var1 == 0x29)
            {
                switch(var2)
                {
                    case 0x00ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        #if defined (NRF54L10_XXAA) || defined (DEVELOP_IN_NRF54L10)
            if (var1 == 0x2E)
            {
                switch(var2)
                {
                    case 0x01ul:
                        return true;
                    case 0x02ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        #if defined (NRF54L05_XXAA) || defined (DEVELOP_IN_NRF54L05)
            if (var1 == 0x2F)
            {
                switch(var2)
                {
                    case 0x01ul:
                        return true;
                    case 0x02ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        return false;
    #endif
}

/* ========= Errata 42 ========= */
#if    defined (NRF54L05_XXAA) || defined (DEVELOP_IN_NRF54L05) \
    || defined (NRF54L10_XXAA) || defined (DEVELOP_IN_NRF54L10) \
    || defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15) \
    || defined (NRF54LM20A_ENGA_XXAA) || defined (DEVELOP_IN_NRF54LM20A_ENGA)
    #define NRF54L_ERRATA_42_PRESENT 1
#else
    #define NRF54L_ERRATA_42_PRESENT 0
#endif

#ifndef NRF54L_ERRATA_42_ENABLE_WORKAROUND
    #define NRF54L_ERRATA_42_ENABLE_WORKAROUND NRF54L_ERRATA_42_PRESENT
#endif

static bool nrf54l_errata_42(void)
{
    #if defined (DISABLE_WORKAROUND_42)
        return false;
    #elif !defined(NRF54L_SERIES)
        return false;
    #else
        #if defined (NRF54L05_XXAA) || defined (DEVELOP_IN_NRF54L05)\
         || defined (NRF54L10_XXAA) || defined (DEVELOP_IN_NRF54L10)\
         || defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15)\
         || defined (NRF54LM20A_ENGA_XXAA) || defined (DEVELOP_IN_NRF54LM20A_ENGA)
            uint32_t var1 = *(uint32_t *)0x00FFC340ul;
            uint32_t var2 = *(uint32_t *)0x00FFC344ul;
        #endif
        #if defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15)
            if (var1 == 0x1C)
            {
                switch(var2)
                {
                    case 0x01ul:
                        return true;
                    case 0x02ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        #if defined (NRF54LM20A_ENGA_XXAA) || defined (DEVELOP_IN_NRF54LM20A_ENGA)
            if (var1 == 0x29)
            {
                switch(var2)
                {
                    case 0x00ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        #if defined (NRF54L10_XXAA) || defined (DEVELOP_IN_NRF54L10)
            if (var1 == 0x2E)
            {
                switch(var2)
                {
                    case 0x01ul:
                        return true;
                    case 0x02ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        #if defined (NRF54L05_XXAA) || defined (DEVELOP_IN_NRF54L05)
            if (var1 == 0x2F)
            {
                switch(var2)
                {
                    case 0x01ul:
                        return true;
                    case 0x02ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        return false;
    #endif
}

/* ========= Errata 43 ========= */
#if    defined (NRF54L05_XXAA) || defined (DEVELOP_IN_NRF54L05) \
    || defined (NRF54L10_XXAA) || defined (DEVELOP_IN_NRF54L10) \
    || defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15) \
    || defined (NRF54LM20A_ENGA_XXAA) || defined (DEVELOP_IN_NRF54LM20A_ENGA)
    #define NRF54L_ERRATA_43_PRESENT 1
#else
    #define NRF54L_ERRATA_43_PRESENT 0
#endif

#ifndef NRF54L_ERRATA_43_ENABLE_WORKAROUND
    #define NRF54L_ERRATA_43_ENABLE_WORKAROUND NRF54L_ERRATA_43_PRESENT
#endif

static bool nrf54l_errata_43(void)
{
    #if defined (DISABLE_WORKAROUND_43)
        return false;
    #elif !defined(NRF54L_SERIES)
        return false;
    #else
        #if defined (NRF54L05_XXAA) || defined (DEVELOP_IN_NRF54L05)\
         || defined (NRF54L10_XXAA) || defined (DEVELOP_IN_NRF54L10)\
         || defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15)\
         || defined (NRF54LM20A_ENGA_XXAA) || defined (DEVELOP_IN_NRF54LM20A_ENGA)
            uint32_t var1 = *(uint32_t *)0x00FFC340ul;
            uint32_t var2 = *(uint32_t *)0x00FFC344ul;
        #endif
        #if defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15)
            if (var1 == 0x1C)
            {
                switch(var2)
                {
                    case 0x01ul:
                        return true;
                    case 0x02ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        #if defined (NRF54LM20A_ENGA_XXAA) || defined (DEVELOP_IN_NRF54LM20A_ENGA)
            if (var1 == 0x29)
            {
                switch(var2)
                {
                    case 0x00ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        #if defined (NRF54L10_XXAA) || defined (DEVELOP_IN_NRF54L10)
            if (var1 == 0x2E)
            {
                switch(var2)
                {
                    case 0x01ul:
                        return true;
                    case 0x02ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        #if defined (NRF54L05_XXAA) || defined (DEVELOP_IN_NRF54L05)
            if (var1 == 0x2F)
            {
                switch(var2)
                {
                    case 0x01ul:
                        return true;
                    case 0x02ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        return false;
    #endif
}

/* ========= Errata 44 ========= */
#if    defined (NRF54L05_XXAA) || defined (DEVELOP_IN_NRF54L05) \
    || defined (NRF54L10_XXAA) || defined (DEVELOP_IN_NRF54L10) \
    || defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15) \
    || defined (NRF54LM20A_ENGA_XXAA) || defined (DEVELOP_IN_NRF54LM20A_ENGA)
    #define NRF54L_ERRATA_44_PRESENT 1
#else
    #define NRF54L_ERRATA_44_PRESENT 0
#endif

#ifndef NRF54L_ERRATA_44_ENABLE_WORKAROUND
    #define NRF54L_ERRATA_44_ENABLE_WORKAROUND NRF54L_ERRATA_44_PRESENT
#endif

static bool nrf54l_errata_44(void)
{
    #if defined (DISABLE_WORKAROUND_44)
        return false;
    #elif !defined(NRF54L_SERIES)
        return false;
    #else
        #if defined (NRF54L05_XXAA) || defined (DEVELOP_IN_NRF54L05)\
         || defined (NRF54L10_XXAA) || defined (DEVELOP_IN_NRF54L10)\
         || defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15)\
         || defined (NRF54LM20A_ENGA_XXAA) || defined (DEVELOP_IN_NRF54LM20A_ENGA)
            uint32_t var1 = *(uint32_t *)0x00FFC340ul;
            uint32_t var2 = *(uint32_t *)0x00FFC344ul;
        #endif
        #if defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15)
            if (var1 == 0x1C)
            {
                switch(var2)
                {
                    case 0x01ul:
                        return true;
                    case 0x02ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        #if defined (NRF54LM20A_ENGA_XXAA) || defined (DEVELOP_IN_NRF54LM20A_ENGA)
            if (var1 == 0x29)
            {
                switch(var2)
                {
                    case 0x00ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        #if defined (NRF54L10_XXAA) || defined (DEVELOP_IN_NRF54L10)
            if (var1 == 0x2E)
            {
                switch(var2)
                {
                    case 0x01ul:
                        return true;
                    case 0x02ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        #if defined (NRF54L05_XXAA) || defined (DEVELOP_IN_NRF54L05)
            if (var1 == 0x2F)
            {
                switch(var2)
                {
                    case 0x01ul:
                        return true;
                    case 0x02ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        return false;
    #endif
}

/* ========= Errata 45 ========= */
#if    defined (NRF54L05_XXAA) || defined (DEVELOP_IN_NRF54L05) \
    || defined (NRF54L10_XXAA) || defined (DEVELOP_IN_NRF54L10) \
    || defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15) \
    || defined (NRF54LM20A_ENGA_XXAA) || defined (DEVELOP_IN_NRF54LM20A_ENGA)
    #define NRF54L_ERRATA_45_PRESENT 1
#else
    #define NRF54L_ERRATA_45_PRESENT 0
#endif

#ifndef NRF54L_ERRATA_45_ENABLE_WORKAROUND
    #define NRF54L_ERRATA_45_ENABLE_WORKAROUND NRF54L_ERRATA_45_PRESENT
#endif

static bool nrf54l_errata_45(void)
{
    #if defined (DISABLE_WORKAROUND_45)
        return false;
    #elif !defined(NRF54L_SERIES)
        return false;
    #else
        #if defined (NRF54L05_XXAA) || defined (DEVELOP_IN_NRF54L05)\
         || defined (NRF54L10_XXAA) || defined (DEVELOP_IN_NRF54L10)\
         || defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15)\
         || defined (NRF54LM20A_ENGA_XXAA) || defined (DEVELOP_IN_NRF54LM20A_ENGA)
            uint32_t var1 = *(uint32_t *)0x00FFC340ul;
            uint32_t var2 = *(uint32_t *)0x00FFC344ul;
        #endif
        #if defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15)
            if (var1 == 0x1C)
            {
                switch(var2)
                {
                    case 0x01ul:
                        return true;
                    case 0x02ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        #if defined (NRF54LM20A_ENGA_XXAA) || defined (DEVELOP_IN_NRF54LM20A_ENGA)
            if (var1 == 0x29)
            {
                switch(var2)
                {
                    case 0x00ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        #if defined (NRF54L10_XXAA) || defined (DEVELOP_IN_NRF54L10)
            if (var1 == 0x2E)
            {
                switch(var2)
                {
                    case 0x01ul:
                        return true;
                    case 0x02ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        #if defined (NRF54L05_XXAA) || defined (DEVELOP_IN_NRF54L05)
            if (var1 == 0x2F)
            {
                switch(var2)
                {
                    case 0x01ul:
                        return true;
                    case 0x02ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        return false;
    #endif
}

/* ========= Errata 46 ========= */
#if    defined (NRF54L05_XXAA) || defined (DEVELOP_IN_NRF54L05) \
    || defined (NRF54L10_XXAA) || defined (DEVELOP_IN_NRF54L10) \
    || defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15)
    #define NRF54L_ERRATA_46_PRESENT 1
#else
    #define NRF54L_ERRATA_46_PRESENT 0
#endif

#ifndef NRF54L_ERRATA_46_ENABLE_WORKAROUND
    #define NRF54L_ERRATA_46_ENABLE_WORKAROUND NRF54L_ERRATA_46_PRESENT
#endif

static bool nrf54l_errata_46(void)
{
    #if defined (DISABLE_WORKAROUND_46)
        return false;
    #elif !defined(NRF54L_SERIES)
        return false;
    #else
        #if defined (NRF54L05_XXAA) || defined (DEVELOP_IN_NRF54L05)\
         || defined (NRF54L10_XXAA) || defined (DEVELOP_IN_NRF54L10)\
         || defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15)
            uint32_t var1 = *(uint32_t *)0x00FFC340ul;
            uint32_t var2 = *(uint32_t *)0x00FFC344ul;
        #endif
        #if defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15)
            if (var1 == 0x1C)
            {
                switch(var2)
                {
                    case 0x01ul:
                        return true;
                    case 0x02ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        #if defined (NRF54L10_XXAA) || defined (DEVELOP_IN_NRF54L10)
            if (var1 == 0x2E)
            {
                switch(var2)
                {
                    case 0x01ul:
                        return true;
                    case 0x02ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        #if defined (NRF54L05_XXAA) || defined (DEVELOP_IN_NRF54L05)
            if (var1 == 0x2F)
            {
                switch(var2)
                {
                    case 0x01ul:
                        return true;
                    case 0x02ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        return false;
    #endif
}

/* ========= Errata 47 ========= */
#if    defined (NRF54L05_XXAA) || defined (DEVELOP_IN_NRF54L05) \
    || defined (NRF54L10_XXAA) || defined (DEVELOP_IN_NRF54L10) \
    || defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15) \
    || defined (NRF54LM20A_ENGA_XXAA) || defined (DEVELOP_IN_NRF54LM20A_ENGA)
    #define NRF54L_ERRATA_47_PRESENT 1
#else
    #define NRF54L_ERRATA_47_PRESENT 0
#endif

#ifndef NRF54L_ERRATA_47_ENABLE_WORKAROUND
    #define NRF54L_ERRATA_47_ENABLE_WORKAROUND NRF54L_ERRATA_47_PRESENT
#endif

static bool nrf54l_errata_47(void)
{
    #if defined (DISABLE_WORKAROUND_47)
        return false;
    #elif !defined(NRF54L_SERIES)
        return false;
    #else
        #if defined (NRF54L05_XXAA) || defined (DEVELOP_IN_NRF54L05)\
         || defined (NRF54L10_XXAA) || defined (DEVELOP_IN_NRF54L10)\
         || defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15)\
         || defined (NRF54LM20A_ENGA_XXAA) || defined (DEVELOP_IN_NRF54LM20A_ENGA)
            uint32_t var1 = *(uint32_t *)0x00FFC340ul;
            uint32_t var2 = *(uint32_t *)0x00FFC344ul;
        #endif
        #if defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15)
            if (var1 == 0x1C)
            {
                switch(var2)
                {
                    case 0x01ul:
                        return true;
                    case 0x02ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        #if defined (NRF54LM20A_ENGA_XXAA) || defined (DEVELOP_IN_NRF54LM20A_ENGA)
            if (var1 == 0x29)
            {
                switch(var2)
                {
                    case 0x00ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        #if defined (NRF54L10_XXAA) || defined (DEVELOP_IN_NRF54L10)
            if (var1 == 0x2E)
            {
                switch(var2)
                {
                    case 0x01ul:
                        return true;
                    case 0x02ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        #if defined (NRF54L05_XXAA) || defined (DEVELOP_IN_NRF54L05)
            if (var1 == 0x2F)
            {
                switch(var2)
                {
                    case 0x01ul:
                        return true;
                    case 0x02ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        return false;
    #endif
}

/* ========= Errata 48 ========= */
#if    defined (NRF54L05_XXAA) || defined (DEVELOP_IN_NRF54L05) \
    || defined (NRF54L10_XXAA) || defined (DEVELOP_IN_NRF54L10) \
    || defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15) \
    || defined (NRF54LM20A_ENGA_XXAA) || defined (DEVELOP_IN_NRF54LM20A_ENGA)
    #define NRF54L_ERRATA_48_PRESENT 1
#else
    #define NRF54L_ERRATA_48_PRESENT 0
#endif

#ifndef NRF54L_ERRATA_48_ENABLE_WORKAROUND
    #define NRF54L_ERRATA_48_ENABLE_WORKAROUND NRF54L_ERRATA_48_PRESENT
#endif

static bool nrf54l_errata_48(void)
{
    #if defined (DISABLE_WORKAROUND_48)
        return false;
    #elif !defined(NRF54L_SERIES)
        return false;
    #else
        #if defined (NRF54L05_XXAA) || defined (DEVELOP_IN_NRF54L05)\
         || defined (NRF54L10_XXAA) || defined (DEVELOP_IN_NRF54L10)\
         || defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15)\
         || defined (NRF54LM20A_ENGA_XXAA) || defined (DEVELOP_IN_NRF54LM20A_ENGA)
            uint32_t var1 = *(uint32_t *)0x00FFC340ul;
            uint32_t var2 = *(uint32_t *)0x00FFC344ul;
        #endif
        #if defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15)
            if (var1 == 0x1C)
            {
                switch(var2)
                {
                    case 0x01ul:
                        return true;
                    case 0x02ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        #if defined (NRF54LM20A_ENGA_XXAA) || defined (DEVELOP_IN_NRF54LM20A_ENGA)
            if (var1 == 0x29)
            {
                switch(var2)
                {
                    case 0x00ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        #if defined (NRF54L10_XXAA) || defined (DEVELOP_IN_NRF54L10)
            if (var1 == 0x2E)
            {
                switch(var2)
                {
                    case 0x01ul:
                        return true;
                    case 0x02ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        #if defined (NRF54L05_XXAA) || defined (DEVELOP_IN_NRF54L05)
            if (var1 == 0x2F)
            {
                switch(var2)
                {
                    case 0x01ul:
                        return true;
                    case 0x02ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        return false;
    #endif
}

/* ========= Errata 49 ========= */
#if    defined (NRF54L05_XXAA) || defined (DEVELOP_IN_NRF54L05) \
    || defined (NRF54L10_XXAA) || defined (DEVELOP_IN_NRF54L10) \
    || defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15) \
    || defined (NRF54LM20A_ENGA_XXAA) || defined (DEVELOP_IN_NRF54LM20A_ENGA) \
    || defined (NRF54LV10A_ENGA_XXAA) || defined (DEVELOP_IN_NRF54LV10A_ENGA)
    #define NRF54L_ERRATA_49_PRESENT 1
#else
    #define NRF54L_ERRATA_49_PRESENT 0
#endif

#ifndef NRF54L_ERRATA_49_ENABLE_WORKAROUND
    #define NRF54L_ERRATA_49_ENABLE_WORKAROUND NRF54L_ERRATA_49_PRESENT
#endif

static bool nrf54l_errata_49(void)
{
    #if defined (DISABLE_WORKAROUND_49)
        return false;
    #elif !defined(NRF54L_SERIES)
        return false;
    #else
        #if defined (NRF54L05_XXAA) || defined (DEVELOP_IN_NRF54L05)\
         || defined (NRF54L10_XXAA) || defined (DEVELOP_IN_NRF54L10)\
         || defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15)\
         || defined (NRF54LM20A_ENGA_XXAA) || defined (DEVELOP_IN_NRF54LM20A_ENGA)\
         || defined (NRF54LV10A_ENGA_XXAA) || defined (DEVELOP_IN_NRF54LV10A_ENGA)
            uint32_t var1 = *(uint32_t *)0x00FFC340ul;
            uint32_t var2 = *(uint32_t *)0x00FFC344ul;
        #endif
        #if defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15)
            if (var1 == 0x1C)
            {
                switch(var2)
                {
                    case 0x01ul:
                        return true;
                    case 0x02ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        #if defined (NRF54LV10A_ENGA_XXAA) || defined (DEVELOP_IN_NRF54LV10A_ENGA)
            if (var1 == 0x27)
            {
                switch(var2)
                {
                    case 0x00ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        #if defined (NRF54LM20A_ENGA_XXAA) || defined (DEVELOP_IN_NRF54LM20A_ENGA)
            if (var1 == 0x29)
            {
                switch(var2)
                {
                    case 0x00ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        #if defined (NRF54L10_XXAA) || defined (DEVELOP_IN_NRF54L10)
            if (var1 == 0x2E)
            {
                switch(var2)
                {
                    case 0x01ul:
                        return true;
                    case 0x02ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        #if defined (NRF54L05_XXAA) || defined (DEVELOP_IN_NRF54L05)
            if (var1 == 0x2F)
            {
                switch(var2)
                {
                    case 0x01ul:
                        return true;
                    case 0x02ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        return false;
    #endif
}

/* ========= Errata 50 ========= */
#if    defined (NRF54L05_XXAA) || defined (DEVELOP_IN_NRF54L05) \
    || defined (NRF54L10_XXAA) || defined (DEVELOP_IN_NRF54L10) \
    || defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15) \
    || defined (NRF54LM20A_ENGA_XXAA) || defined (DEVELOP_IN_NRF54LM20A_ENGA)
    #define NRF54L_ERRATA_50_PRESENT 1
#else
    #define NRF54L_ERRATA_50_PRESENT 0
#endif

#ifndef NRF54L_ERRATA_50_ENABLE_WORKAROUND
    #define NRF54L_ERRATA_50_ENABLE_WORKAROUND NRF54L_ERRATA_50_PRESENT
#endif

static bool nrf54l_errata_50(void)
{
    #if defined (DISABLE_WORKAROUND_50)
        return false;
    #elif !defined(NRF54L_SERIES)
        return false;
    #else
        #if defined (NRF54L05_XXAA) || defined (DEVELOP_IN_NRF54L05)\
         || defined (NRF54L10_XXAA) || defined (DEVELOP_IN_NRF54L10)\
         || defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15)\
         || defined (NRF54LM20A_ENGA_XXAA) || defined (DEVELOP_IN_NRF54LM20A_ENGA)
            uint32_t var1 = *(uint32_t *)0x00FFC340ul;
            uint32_t var2 = *(uint32_t *)0x00FFC344ul;
        #endif
        #if defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15)
            if (var1 == 0x1C)
            {
                switch(var2)
                {
                    case 0x01ul:
                        return true;
                    case 0x02ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        #if defined (NRF54LM20A_ENGA_XXAA) || defined (DEVELOP_IN_NRF54LM20A_ENGA)
            if (var1 == 0x29)
            {
                switch(var2)
                {
                    case 0x00ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        #if defined (NRF54L10_XXAA) || defined (DEVELOP_IN_NRF54L10)
            if (var1 == 0x2E)
            {
                switch(var2)
                {
                    case 0x01ul:
                        return true;
                    case 0x02ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        #if defined (NRF54L05_XXAA) || defined (DEVELOP_IN_NRF54L05)
            if (var1 == 0x2F)
            {
                switch(var2)
                {
                    case 0x01ul:
                        return true;
                    case 0x02ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        return false;
    #endif
}

/* ========= Errata 55 ========= */
#if    defined (NRF54LM20A_ENGA_XXAA) || defined (DEVELOP_IN_NRF54LM20A_ENGA) \
    || defined (NRF54LV10A_ENGA_XXAA) || defined (DEVELOP_IN_NRF54LV10A_ENGA)
    #define NRF54L_ERRATA_55_PRESENT 1
#else
    #define NRF54L_ERRATA_55_PRESENT 0
#endif

#ifndef NRF54L_ERRATA_55_ENABLE_WORKAROUND
    #define NRF54L_ERRATA_55_ENABLE_WORKAROUND NRF54L_ERRATA_55_PRESENT
#endif

static bool nrf54l_errata_55(void)
{
    #if defined (DISABLE_WORKAROUND_55)
        return false;
    #elif !defined(NRF54L_SERIES)
        return false;
    #else
        #if defined (NRF54LM20A_ENGA_XXAA) || defined (DEVELOP_IN_NRF54LM20A_ENGA)\
         || defined (NRF54LV10A_ENGA_XXAA) || defined (DEVELOP_IN_NRF54LV10A_ENGA)
            uint32_t var1 = *(uint32_t *)0x00FFC340ul;
            uint32_t var2 = *(uint32_t *)0x00FFC344ul;
        #endif
        #if defined (NRF54LV10A_ENGA_XXAA) || defined (DEVELOP_IN_NRF54LV10A_ENGA)
            if (var1 == 0x27)
            {
                switch(var2)
                {
                    case 0x00ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        #if defined (NRF54LM20A_ENGA_XXAA) || defined (DEVELOP_IN_NRF54LM20A_ENGA)
            if (var1 == 0x29)
            {
                switch(var2)
                {
                    case 0x00ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        return false;
    #endif
}

/* ========= Errata 56 ========= */
#if    defined (NRF54L05_XXAA) || defined (DEVELOP_IN_NRF54L05) \
    || defined (NRF54L10_XXAA) || defined (DEVELOP_IN_NRF54L10) \
    || defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15)
    #define NRF54L_CONFIGURATION_56_PRESENT 1
#else
    #define NRF54L_CONFIGURATION_56_PRESENT 0
#endif

#ifndef NRF54L_CONFIGURATION_56_ENABLE
    #define NRF54L_CONFIGURATION_56_ENABLE NRF54L_CONFIGURATION_56_PRESENT
#endif

static bool nrf54l_configuration_56(void)
{
    #if defined (DISABLE_WORKAROUND_56)
        return false;
    #elif !defined(NRF54L_SERIES)
        return false;
    #else
        #if defined (NRF54L05_XXAA) || defined (DEVELOP_IN_NRF54L05)\
         || defined (NRF54L10_XXAA) || defined (DEVELOP_IN_NRF54L10)\
         || defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15)
            uint32_t var1 = *(uint32_t *)0x00FFC340ul;
            uint32_t var2 = *(uint32_t *)0x00FFC344ul;
        #endif
        #if defined (NRF54L15_XXAA) || defined (DEVELOP_IN_NRF54L15)
            if (var1 == 0x1C)
            {
                switch(var2)
                {
                    case 0x01ul:
                        return true;
                    case 0x02ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        #if defined (NRF54L10_XXAA) || defined (DEVELOP_IN_NRF54L10)
            if (var1 == 0x2E)
            {
                switch(var2)
                {
                    case 0x01ul:
                        return true;
                    case 0x02ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        #if defined (NRF54L05_XXAA) || defined (DEVELOP_IN_NRF54L05)
            if (var1 == 0x2F)
            {
                switch(var2)
                {
                    case 0x01ul:
                        return true;
                    case 0x02ul:
                        return true;
                    default:
                        return true;
                }
            }
        #endif
        return false;
    #endif
}

#endif /* NRF54L_ERRATAS_H */
