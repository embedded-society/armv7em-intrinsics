# armv7em-intrinsics

Header-only C++20 wrappers for ARMv7E-M instructions that are not normally emitted by a C/C++ compiler — including the DSP extension SIMD/MAC instructions.

Targets the **ARMv7E-M** instruction set: Cortex-M4 with the DSP extension.

For ARMv6-M (Cortex-M0/M0+/M1), see [armv6m-intrinsics](https://github.com/embedded-society/armv6m-intrinsics).
For ARMv7-M (Cortex-M3, no DSP), see [armv7m-intrinsics](https://github.com/embedded-society/armv7m-intrinsics).

## Usage

Copy the library into your project (e.g., into `lib/`) and add it via CMake:

```cmake
add_subdirectory(lib/armv7em-intrinsics)
target_link_libraries(your_target PRIVATE armv7em-intrinsics)
```

Then include what you need:

```cpp
#include <armv7em-intrinsics/dsp.hpp>

// FIR tap pair: two 16-bit samples × two 16-bit coefficients, single-cycle MAC
uint32_t fir_step(uint32_t samples_packed, uint32_t coeffs_packed, uint32_t acc) {
    return ArmCortex::asmSmlad(samples_packed, coeffs_packed, acc);
}
```

CMake is optional — every header is self-contained, so you can drop the `include/` directory anywhere on your include path and `#include` directly without using CMake at all.

## Contents

All wrappers live in the `ArmCortex` namespace and are `[[gnu::always_inline]] static inline` so the compiler inlines them straight into the call site without function-call overhead.

| File | Instructions | Notes |
|------|--------------|-------|
| `hints.hpp` | `NOP`, `YIELD`, `WFI`, `WFE`, `SEV`, `BKPT<imm>` | Hint-class instructions; `BKPT` takes an 8-bit immediate identifier |
| `barriers.hpp` | `DSB`, `DMB`, `ISB` | Memory and instruction synchronisation barriers (full system domain) |
| `interrupts.hpp` | `CPSIE i/f`, `CPSID i/f` | Enable/disable maskable exceptions (PRIMASK) and faults (FAULTMASK) |
| `svc.hpp` | `SVC<imm>` | Supervisor call with 8-bit immediate (template-encoded) |
| `reverse.hpp` | `REV`, `REV16`, `REVSH` | Byte-order reversal of word, halfword pairs, and signed lower halfword |
| `bits.hpp` | `CLZ`, `RBIT` | Count leading zeros, reverse bits |
| `exclusive.hpp` | `LDREX`, `LDREXH`, `LDREXB`, `STREX`, `STREXH`, `STREXB`, `CLREX` | Load/store-exclusive primitives for lock-free atomics |
| `saturation.hpp` | `SSAT<sat>`, `USAT<sat>` | Signed/unsigned saturation to `sat` bits (template-encoded) |
| `dsp.hpp` | `QADD`, `QSUB`, `SADD16`, `QADD16`, `SSUB16`, `QSUB16`, `SADD8`, `QADD8`, `SSUB8`, `QSUB8`, `SEL`, `SMUAD`, `SMUSD`, `SMLAD`, `SMLSD` | Saturating arithmetic + packed-SIMD add/sub + dual 16×16 MAC |

> **Note:** `dsp.hpp` exposes a representative subset of the ~70 DSP instructions in the ARMv7E-M ISA (the highest-leverage ones for FIR/IIR filtering, lane-wise saturation, and packed arithmetic). The remaining DSP instructions (the rest of the `S*ADD/SUB/ASX/SAX/HASX/HSAX/USAD/USADA/PKHBT/PKHTB/SXTB16/UXTB16/SXTAB16/UXTAB16` family, the long-accumulate variants `SMLALD`, `SMLSLD`, the `*X` cross variants, `SMMUL/SMMLA/SMMLS`, …) are **not yet covered** — add as needed.

## Licence

This project is licensed under the Apache License Version 2.0.  
Copyright (C) 2026 The Embedded Society <https://github.com/embedded-society/armv7em-intrinsics>.  
See the attached [LICENCE](./LICENCE) file for more info.
