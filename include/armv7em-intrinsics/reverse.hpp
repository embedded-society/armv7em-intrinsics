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
    //! Reverse byte order in a 32-bit word: 0xAABBCCDD -> 0xDDCCBBAA.
    //! Equivalent to a 32-bit endianness swap.
    [[gnu::always_inline]] static inline uint32_t asmRev(uint32_t value)
    {
        uint32_t result;
        asm volatile("rev %0, %1" : "=r" (result) : "r" (value));
        return result;
    }

    //! Reverse byte order in each halfword independently: 0xAABBCCDD -> 0xBBAADDCC.
    //! Useful for swapping endianness of two packed 16-bit values.
    [[gnu::always_inline]] static inline uint32_t asmRev16(uint32_t value)
    {
        uint32_t result;
        asm volatile("rev16 %0, %1" : "=r" (result) : "r" (value));
        return result;
    }

    //! Reverse byte order in the lower halfword and sign-extend to 32 bits.
    //! Use to swap endianness of a signed 16-bit value.
    [[gnu::always_inline]] static inline int32_t asmRevsh(int16_t value)
    {
        int32_t result;
        asm volatile("revsh %0, %1" : "=r" (result) : "r" (value));
        return result;
    }
}
