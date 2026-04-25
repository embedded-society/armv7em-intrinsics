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

// =============================================================================
// ARMv7E-M DSP Extension Intrinsics
//
// These wrappers require the Cortex-M4's DSP extension (compiled with -mcpu of
// a core that has it; -mfpu setting is independent). Operands marked as packed
// are interpreted as two int16 values in a uint32 (low halfword = first
// element) or four int8 values in a uint32 (low byte = first element), as per
// the ARMv7-M Architecture Reference Manual.
//
// This header intentionally exposes a representative subset of the DSP
// instructions, not the full ~70-entry catalogue. Add more on demand.
// =============================================================================

namespace ArmCortex {
    // -------- Saturating add/subtract on a single 32-bit signed value --------

    //! Saturating signed add. Result clamped to int32 range; sets Q flag on overflow.
    [[gnu::always_inline]] static inline uint32_t asmQadd(uint32_t op1, uint32_t op2)
    {
        uint32_t result;
        asm volatile("qadd %0, %1, %2" : "=r" (result) : "r" (op1), "r" (op2));
        return result;
    }

    //! Saturating signed subtract. Result clamped to int32 range; sets Q flag on overflow.
    [[gnu::always_inline]] static inline uint32_t asmQsub(uint32_t op1, uint32_t op2)
    {
        uint32_t result;
        asm volatile("qsub %0, %1, %2" : "=r" (result) : "r" (op1), "r" (op2));
        return result;
    }

    // -------- 16-bit packed signed add/subtract --------

    //! Add two packed 16-bit signed pairs (no saturation). Sets per-halfword GE flags.
    [[gnu::always_inline]] static inline uint32_t asmSadd16(uint32_t op1, uint32_t op2)
    {
        uint32_t result;
        asm volatile("sadd16 %0, %1, %2" : "=r" (result) : "r" (op1), "r" (op2));
        return result;
    }

    //! Add two packed 16-bit signed pairs with per-element saturation to int16.
    [[gnu::always_inline]] static inline uint32_t asmQadd16(uint32_t op1, uint32_t op2)
    {
        uint32_t result;
        asm volatile("qadd16 %0, %1, %2" : "=r" (result) : "r" (op1), "r" (op2));
        return result;
    }

    //! Subtract two packed 16-bit signed pairs (no saturation). Sets per-halfword GE flags.
    [[gnu::always_inline]] static inline uint32_t asmSsub16(uint32_t op1, uint32_t op2)
    {
        uint32_t result;
        asm volatile("ssub16 %0, %1, %2" : "=r" (result) : "r" (op1), "r" (op2));
        return result;
    }

    //! Subtract two packed 16-bit signed pairs with per-element saturation to int16.
    [[gnu::always_inline]] static inline uint32_t asmQsub16(uint32_t op1, uint32_t op2)
    {
        uint32_t result;
        asm volatile("qsub16 %0, %1, %2" : "=r" (result) : "r" (op1), "r" (op2));
        return result;
    }

    // -------- 8-bit packed signed add/subtract --------

    //! Add two packed 8-bit signed quads (no saturation). Sets per-byte GE flags.
    [[gnu::always_inline]] static inline uint32_t asmSadd8(uint32_t op1, uint32_t op2)
    {
        uint32_t result;
        asm volatile("sadd8 %0, %1, %2" : "=r" (result) : "r" (op1), "r" (op2));
        return result;
    }

    //! Add two packed 8-bit signed quads with per-element saturation to int8.
    [[gnu::always_inline]] static inline uint32_t asmQadd8(uint32_t op1, uint32_t op2)
    {
        uint32_t result;
        asm volatile("qadd8 %0, %1, %2" : "=r" (result) : "r" (op1), "r" (op2));
        return result;
    }

    //! Subtract two packed 8-bit signed quads (no saturation). Sets per-byte GE flags.
    [[gnu::always_inline]] static inline uint32_t asmSsub8(uint32_t op1, uint32_t op2)
    {
        uint32_t result;
        asm volatile("ssub8 %0, %1, %2" : "=r" (result) : "r" (op1), "r" (op2));
        return result;
    }

    //! Subtract two packed 8-bit signed quads with per-element saturation to int8.
    [[gnu::always_inline]] static inline uint32_t asmQsub8(uint32_t op1, uint32_t op2)
    {
        uint32_t result;
        asm volatile("qsub8 %0, %1, %2" : "=r" (result) : "r" (op1), "r" (op2));
        return result;
    }

    // -------- Lane-wise selection driven by GE flags --------

    //! Select bytes from op1 or op2 based on the per-byte GE flags set by the most
    //! recent flag-setting DSP instruction (e.g. SADD16). For each byte position,
    //! GE=1 picks op1, GE=0 picks op2.
    [[gnu::always_inline]] static inline uint32_t asmSel(uint32_t op1, uint32_t op2)
    {
        uint32_t result;
        asm volatile("sel %0, %1, %2" : "=r" (result) : "r" (op1), "r" (op2));
        return result;
    }

    // -------- Dual 16x16 multiply-and-accumulate (workhorse for FIR/IIR) --------

    //! Signed Multiply, Add (dual). result = op1.lo * op2.lo + op1.hi * op2.hi.
    //! Sets Q flag if the 32-bit accumulation overflows.
    [[gnu::always_inline]] static inline uint32_t asmSmuad(uint32_t op1, uint32_t op2)
    {
        uint32_t result;
        asm volatile("smuad %0, %1, %2" : "=r" (result) : "r" (op1), "r" (op2));
        return result;
    }

    //! Signed Multiply, Subtract. result = op1.lo * op2.lo - op1.hi * op2.hi.
    [[gnu::always_inline]] static inline uint32_t asmSmusd(uint32_t op1, uint32_t op2)
    {
        uint32_t result;
        asm volatile("smusd %0, %1, %2" : "=r" (result) : "r" (op1), "r" (op2));
        return result;
    }

    //! Signed Multiply, Add with accumulator. result = acc + op1.lo*op2.lo + op1.hi*op2.hi.
    [[gnu::always_inline]] static inline uint32_t asmSmlad(uint32_t op1, uint32_t op2, uint32_t acc)
    {
        uint32_t result;
        asm volatile("smlad %0, %1, %2, %3" : "=r" (result) : "r" (op1), "r" (op2), "r" (acc));
        return result;
    }

    //! Signed Multiply, Subtract with accumulator. result = acc + op1.lo*op2.lo - op1.hi*op2.hi.
    [[gnu::always_inline]] static inline uint32_t asmSmlsd(uint32_t op1, uint32_t op2, uint32_t acc)
    {
        uint32_t result;
        asm volatile("smlsd %0, %1, %2, %3" : "=r" (result) : "r" (op1), "r" (op2), "r" (acc));
        return result;
    }
}
