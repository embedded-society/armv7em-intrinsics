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

namespace ArmCortex {
    //! Enable interrupts (clear PRIMASK).
    //! Enables all exceptions with configurable priority. NMI and HardFault are
    //! never masked by PRIMASK.
    [[gnu::always_inline]] static inline void asmCpsie()
    {
        asm volatile("cpsie i" : : : "memory");
    }

    //! Disable interrupts (set PRIMASK).
    //! Disables all exceptions with configurable priority. NMI and HardFault remain
    //! enabled. Use to protect short critical sections.
    [[gnu::always_inline]] static inline void asmCpsid()
    {
        asm volatile("cpsid i" : : : "memory");
    }

    //! Enable faults (clear FAULTMASK).
    //! Re-enables all exceptions except NMI. Pair with asmCpsidF() for fault-free
    //! critical sections deeper than what PRIMASK provides.
    [[gnu::always_inline]] static inline void asmCpsieF()
    {
        asm volatile("cpsie f" : : : "memory");
    }

    //! Disable faults (set FAULTMASK).
    //! Disables all exceptions except NMI; configurable-priority faults are
    //! escalated to HardFault and then ignored. Cleared automatically on exception
    //! return from any handler other than NMI. Privileged code only.
    [[gnu::always_inline]] static inline void asmCpsidF()
    {
        asm volatile("cpsid f" : : : "memory");
    }
}
