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
    //! Data Synchronization Barrier. Completes when every preceding explicit memory
    //! access has completed; subsequent instructions do not execute until then.
    //! Required after writing to memory-mapped configuration that controls
    //! subsequent instruction behaviour (e.g. NVIC enable before triggering an IRQ).
    [[gnu::always_inline]] static inline void asmDsb()
    {
        asm volatile("dsb sy" ::: "memory");
    }

    //! Data Memory Barrier. Ensures the relative order of memory accesses without
    //! waiting for them to complete. Cheaper than DSB; use when only ordering matters,
    //! not completion (e.g. between writes that must be observed in order).
    [[gnu::always_inline]] static inline void asmDmb()
    {
        asm volatile("dmb sy" ::: "memory");
    }

    //! Instruction Synchronization Barrier. Flushes the processor pipeline so that
    //! subsequent instructions are fetched from cache or memory after any context-
    //! changing operations (e.g. CONTROL/PRIMASK writes, VTOR change, MPU reconfig).
    [[gnu::always_inline]] static inline void asmIsb()
    {
        asm volatile("isb sy" ::: "memory");
    }
}
