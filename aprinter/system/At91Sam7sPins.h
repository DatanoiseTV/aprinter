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

#ifndef AMBROLIB_AT91SAM7S_PINS_H
#define AMBROLIB_AT91SAM7S_PINS_H

#include <stdint.h>

#include <aprinter/meta/Position.h>
#include <aprinter/base/DebugObject.h>

#include <aprinter/BeginNamespace.h>

template <int TPinIndex>
struct At91Sam7sPin {
    static const int PinIndex = TPinIndex;
};

template <typename Position, typename Context>
class At91Sam7sPins
: private DebugObject<Context, void>
{
    static At91Sam7sPins * self (Context c)
    {
        return PositionTraverse<typename Context::TheRootPosition, Position>(c.root());
    }
    
public:
    static void init (Context c)
    {
        At91Sam7sPins *o = self(c);
        at91sam7s_pmc_enable_periph(AT91C_ID_PIOA);
        o->debugInit(c);
    }
    
    static void deinit (Context c)
    {
        At91Sam7sPins *o = self(c);
        o->debugDeinit(c);
        at91sam7s_pmc_disable_periph(AT91C_ID_PIOA);
    }
    
    template <typename Pin, typename ThisContext>
    static void setInput (ThisContext c)
    {
        At91Sam7sPins *o = self(c);
        o->debugAccess(c);
        
        AT91C_BASE_PIOA->PIO_ODR = (UINT32_C(1) << Pin::PinIndex);
        AT91C_BASE_PIOA->PIO_PER = (UINT32_C(1) << Pin::PinIndex);;
    }
    
    template <typename Pin, typename ThisContext>
    static void setOutput (ThisContext c)
    {
        At91Sam7sPins *o = self(c);
        o->debugAccess(c);
        
        AT91C_BASE_PIOA->PIO_OER = (UINT32_C(1) << Pin::PinIndex);
        AT91C_BASE_PIOA->PIO_PER = (UINT32_C(1) << Pin::PinIndex);
    }
    
    template <typename Pin, typename ThisContext>
    static bool get (ThisContext c)
    {
        At91Sam7sPins *o = self(c);
        o->debugAccess(c);
        
        return (AT91C_BASE_PIOA->PIO_PDSR & (UINT32_C(1) << Pin::PinIndex));
    }
    
    template <typename Pin, typename ThisContext>
    static void set (ThisContext c, bool x)
    {
        At91Sam7sPins *o = self(c);
        o->debugAccess(c);
        
        if (x) {
            AT91C_BASE_PIOA->PIO_SODR = (UINT32_C(1) << Pin::PinIndex);
        } else {
            AT91C_BASE_PIOA->PIO_CODR = (UINT32_C(1) << Pin::PinIndex);
        }
    }
    
    template <typename Pin>
    static void emergencySet (bool x)
    {
        if (x) {
            AT91C_BASE_PIOA->PIO_SODR = (UINT32_C(1) << Pin::PinIndex);
        } else {
            AT91C_BASE_PIOA->PIO_CODR = (UINT32_C(1) << Pin::PinIndex);
        }
    }
};

#include <aprinter/EndNamespace.h>

#endif
