/*
 
Copyright (c) 2009-2023 ARM Limited. All rights reserved.

    SPDX-License-Identifier: Apache-2.0

Licensed under the Apache License, Version 2.0 (the License); you may
not use this file except in compliance with the License.
You may obtain a copy of the License at

    www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an AS IS BASIS, WITHOUT
WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

NOTICE: This file has been modified by Nordic Semiconductor ASA.

*/

    .syntax unified
    .arch armv8-m.main

#ifdef __STARTUP_CONFIG
#include "startup_config.h"
#ifndef __STARTUP_CONFIG_STACK_ALIGNEMENT
#define __STARTUP_CONFIG_STACK_ALIGNEMENT 3
#endif
#endif

    .section .stack
#if defined(__STARTUP_CONFIG)
    .align __STARTUP_CONFIG_STACK_ALIGNEMENT
    .equ    Stack_Size, __STARTUP_CONFIG_STACK_SIZE
#elif defined(__STACK_SIZE)
    .align 3
    .equ    Stack_Size, __STACK_SIZE
#else
    .align 3
    .equ    Stack_Size, 8192
#endif
    .globl __StackTop
    .globl __StackLimit
__StackLimit:
    .space Stack_Size
    .size __StackLimit, . - __StackLimit
__StackTop:
    .size __StackTop, . - __StackTop

    .section .heap
    .align 3
#if defined(__STARTUP_CONFIG)
    .equ Heap_Size, __STARTUP_CONFIG_HEAP_SIZE
#elif defined(__HEAP_SIZE)
    .equ Heap_Size, __HEAP_SIZE
#else
    .equ Heap_Size, 8192
#endif
    .globl __HeapBase
    .globl __HeapLimit
__HeapBase:
    .if Heap_Size
    .space Heap_Size
    .endif
    .size __HeapBase, . - __HeapBase
__HeapLimit:
    .size __HeapLimit, . - __HeapLimit

    .section .isr_vector, "ax"
    .align 2
    .globl __isr_vector
__isr_vector:
    .long   __StackTop                  /* Top of Stack */
    .long   Reset_Handler
    .size __isr_vector, . - __isr_vector

/* Reset Handler */

.equ OSCILLATORS_PLL_FREQ, 0x50120800
.equ SPU00_PERIPH_C_PERM, 0x50040530
.equ VPR00_INITPC,        0x5004c808
.equ VPR00_CPURUN,        0x5004c800
.equ VPR_CODE_NVM_START,  0x00040000 /* NVM start address for the FLPR code */
.equ VPR_CODE_RAM_START,  0x20000000 /* Destination FLPR RAM code start*/
.equ VPR_CODE_RAM_END,    0x20040000 /* Destination FLPR RAM code end */
.equ P0_DIR, 0x5010A010
.equ P0_OUT, 0x5010A000

    .text
    .thumb
    .thumb_func
    .align 1
    .globl Reset_Handler
    .type Reset_Handler, %function
Reset_Handler:
    // Set frequency to 128 (1 = 128, 3 = 64 - default)
    movs r0, #1 
    ldr r1, =OSCILLATORS_PLL_FREQ
    str r0, [r1]

    /* Copy FLPR code from NVM to RAM */
    ldr r1, =VPR_CODE_NVM_START
    ldr r2, =VPR_CODE_RAM_START
    ldr r3, =VPR_CODE_RAM_END

    subs r3, r3, r2
    ble .L_loop1_done

.L_loop1:
    subs r3, r3, #4
    ldr r0, [r1,r3]
    str r0, [r2,r3]
    bgt .L_loop1

.L_loop1_done: 
    /* 0x50040530 = (1 << 4);  // SPU00->PERIPH[0xc].PERM = (1 << 4); */
    movs r0, #16
    ldr r1, =SPU00_PERIPH_C_PERM
    str  r0, [r1]

    ldr r0, =VPR_CODE_RAM_START /* start address 0x20000000 */
    ldr r1, =VPR00_INITPC
    str r0, [r1]

    movs r0, #1 /* RUN */
    ldr r1, =VPR00_CPURUN
    str r0, [r1]
/*
    ldr r0, =P0_DIR
    movs r1, #16
    str r1, [r0]

    ldr r0, =P0_OUT
    str r1, [r0]
*/

    wfe
    wfi

    .pool
    .size   Reset_Handler,.-Reset_Handler

    .section ".text"



