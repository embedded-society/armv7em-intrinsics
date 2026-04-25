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
    //! Count Leading Zeros. Returns the number of zero bits before the first 1 bit
    //! when scanning from the most-significant bit. CLZ(0) = 32.
    [[gnu::always_inline]] static inline uint32_t asmClz(uint32_t value)
    {
        uint32_t result;
        asm volatile("clz %0, %1" : "=r" (result) : "r" (value));
        return result;
    }

    //! Reverse Bits. Reverses the bit order of a 32-bit word: bit 0 becomes bit 31,
    //! bit 1 becomes bit 30, and so on. Useful with CLZ for find-lowest-set-bit.
    [[gnu::always_inline]] static inline uint32_t asmRbit(uint32_t value)
    {
        uint32_t result;
        asm volatile("rbit %0, %1" : "=r" (result) : "r" (value));
        return result;
    }
}
