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
    //! No operation. Used to introduce a deterministic delay slot or to align code.
    [[gnu::always_inline]] static inline void asmNop()
    {
        asm volatile("nop");
    }

    //! Yield. Hint to a multiprocessing system that the current thread is unimportant.
    //! On single-core Cortex-M devices this typically executes as NOP.
    [[gnu::always_inline]] static inline void asmYield()
    {
        asm volatile("yield");
    }

    //! Wait For Interrupt. Suspend execution until an exception or debug event occurs.
    //! Enters a low-power state. Acts as NOP if a wake-up event is already pending.
    [[gnu::always_inline]] static inline void asmWfi()
    {
        asm volatile("wfi");
    }

    //! Wait For Event. Suspend execution until an event is signalled (SEV from another
    //! processor, exception entry/exit, or debug event). Acts as NOP if the event
    //! register is already set.
    [[gnu::always_inline]] static inline void asmWfe()
    {
        asm volatile("wfe");
    }

    //! Send Event. Sets the event register on this processor and signals an event to
    //! all processors in a multiprocessor system, waking those waiting on WFE.
    [[gnu::always_inline]] static inline void asmSev()
    {
        asm volatile("sev");
    }

    //! Breakpoint. Causes the processor to enter Debug state when halting debug is
    //! enabled, otherwise generates a HardFault.
    //! \tparam value 8-bit immediate identifier (0-255) passed to the debugger.
    template<uint8_t value>
    [[gnu::always_inline]] static inline void asmBkpt()
    {
        asm volatile("bkpt %0" : : "i" (static_cast<uint16_t>(value)));
    }
}
