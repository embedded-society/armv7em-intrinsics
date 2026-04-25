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
    //! Supervisor Call. Raises an SVCall exception; the immediate is encoded in the
    //! instruction itself and must be recovered by the SVC handler from the stacked
    //! return address (SVC #imm is a one-instruction-form, so handler reads the byte
    //! at saved_pc - 2).
    //! \tparam value 8-bit immediate (0-255) identifying the requested service.
    template<uint8_t value>
    [[gnu::always_inline]] static inline void asmSvc()
    {
        asm volatile("svc %0" : : "i" (static_cast<uint16_t>(value)));
    }
}
