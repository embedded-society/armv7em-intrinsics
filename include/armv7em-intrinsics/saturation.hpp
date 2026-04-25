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
    //! Signed saturate. Clamps a signed 32-bit value to the signed range that fits
    //! in `sat` bits, i.e. [-2^(sat-1), 2^(sat-1) - 1]. Sets the Q flag in APSR if
    //! saturation occurred.
    //! \tparam sat saturation bit width (1-32 inclusive).
    template<uint8_t sat>
    [[gnu::always_inline]] static inline int32_t asmSsat(int32_t value)
    {
        static_assert(sat >= 1 && sat <= 32, "SSAT saturation width must be 1-32");
        int32_t result;
        asm volatile("ssat %0, %1, %2" : "=r" (result) : "i" (sat), "r" (value));
        return result;
    }

    //! Unsigned saturate. Clamps a signed 32-bit value to the unsigned range that
    //! fits in `sat` bits, i.e. [0, 2^sat - 1]. Sets the Q flag in APSR if
    //! saturation occurred.
    //! \tparam sat saturation bit width (0-31 inclusive).
    template<uint8_t sat>
    [[gnu::always_inline]] static inline uint32_t asmUsat(int32_t value)
    {
        static_assert(sat <= 31, "USAT saturation width must be 0-31");
        uint32_t result;
        asm volatile("usat %0, %1, %2" : "=r" (result) : "i" (sat), "r" (value));
        return result;
    }
}
