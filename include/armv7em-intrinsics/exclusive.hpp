/*
    Copyright (C) 2026 The Embedded Society <https://github.com/embedded-society/armv7em-intrinsics>

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#pragma once

#include <cstdint>

namespace ArmCortex {
    //! Exclusive load (byte). Marks the address as held by an exclusive monitor.
    //! Pair with asmStrexB on the same address; the store succeeds only if no
    //! intervening write/exception/CLREX cleared the monitor.
    [[gnu::always_inline]] static inline uint8_t asmLdrexB(volatile const uint8_t* addr)
    {
        uint32_t result;
        asm volatile("ldrexb %0, [%1]" : "=r" (result) : "r" (addr) : "memory");
        return static_cast<uint8_t>(result);
    }

    //! Exclusive load (halfword). See asmLdrexB for monitor semantics.
    [[gnu::always_inline]] static inline uint16_t asmLdrexH(volatile const uint16_t* addr)
    {
        uint32_t result;
        asm volatile("ldrexh %0, [%1]" : "=r" (result) : "r" (addr) : "memory");
        return static_cast<uint16_t>(result);
    }

    //! Exclusive load (word). See asmLdrexB for monitor semantics.
    [[gnu::always_inline]] static inline uint32_t asmLdrex(volatile const uint32_t* addr)
    {
        uint32_t result;
        asm volatile("ldrex %0, [%1]" : "=r" (result) : "r" (addr) : "memory");
        return result;
    }

    //! Exclusive store (byte). Returns 0 on success, 1 on failure (monitor cleared).
    [[gnu::always_inline]] static inline uint32_t asmStrexB(uint8_t value, volatile uint8_t* addr)
    {
        uint32_t result;
        asm volatile("strexb %0, %2, [%1]" : "=&r" (result) : "r" (addr), "r" (value) : "memory");
        return result;
    }

    //! Exclusive store (halfword). Returns 0 on success, 1 on failure.
    [[gnu::always_inline]] static inline uint32_t asmStrexH(uint16_t value, volatile uint16_t* addr)
    {
        uint32_t result;
        asm volatile("strexh %0, %2, [%1]" : "=&r" (result) : "r" (addr), "r" (value) : "memory");
        return result;
    }

    //! Exclusive store (word). Returns 0 on success, 1 on failure.
    [[gnu::always_inline]] static inline uint32_t asmStrex(uint32_t value, volatile uint32_t* addr)
    {
        uint32_t result;
        asm volatile("strex %0, %2, [%1]" : "=&r" (result) : "r" (addr), "r" (value) : "memory");
        return result;
    }

    //! Clear the local exclusive monitor.
    //! Forces the next exclusive store on this processor to fail. Use when
    //! abandoning a load-linked / store-conditional sequence (e.g. on context
    //! switch out of a partially-completed exclusive sequence).
    [[gnu::always_inline]] static inline void asmClrex()
    {
        asm volatile("clrex" ::: "memory");
    }
}
