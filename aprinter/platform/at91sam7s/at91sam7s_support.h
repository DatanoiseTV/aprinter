/*
 * Copyright (c) 2013 Ambroz Bizjak
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef AMBROLIB_AT91SAM7S_SUPPORT_H
#define AMBROLIB_AT91SAM7S_SUPPORT_H

#include <stdint.h>

#include "plat.h"

#define F_MCK ((((float)F_CRYSTAL * F_MUL) / F_DIV) / 2)

static void at91sam7s_pmc_enable_periph (int id)
{
    AT91C_BASE_PMC->PMC_PCER = (UINT32_C(1) << id);
}

static void at91sam7s_pmc_disable_periph (int id)
{
    AT91C_BASE_PMC->PMC_PCDR = (UINT32_C(1) << id);
}

static void at91sam7s_aic_register_irq (int id, uint32_t srctype, uint32_t priority, void (*handler) (void))
{
    AT91C_BASE_AIC->AIC_IDCR = (UINT32_C(1) << id);
    AT91C_BASE_AIC->AIC_SVR[id] = (uint32_t)handler;
    AT91C_BASE_AIC->AIC_SMR[id] = srctype | priority;
    AT91C_BASE_AIC->AIC_ICCR = (UINT32_C(1) << id);
}

static void at91sam7s_aic_enable_irq (int id)
{
    AT91C_BASE_AIC->AIC_IECR = (UINT32_C(1) << id);
}

static void at91sam7s_aic_disable_irq (int id)
{
    AT91C_BASE_AIC->AIC_ICCR = (UINT32_C(1) << id);
}

inline static void sei (void)
{
    uint32_t tmp;
    __asm__ volatile (
        "mrs %[tmp],cpsr\n"
        "bic %[tmp],%[tmp],#0x80\n"
        "msr cpsr_c,%[tmp]\n"
        : [tmp] "=&r" (tmp)
        :
        : "cc", "memory"
    );
}

inline static void cli (void)
{
    uint32_t tmp;
    __asm__ volatile (
        "mrs %[tmp],cpsr\n"
        "orr %[tmp],%[tmp],#0x80\n"
        "msr cpsr_c,%[tmp]\n"
        : [tmp] "=&r" (tmp)
        :
        : "cc", "memory"
    );
}

#endif
