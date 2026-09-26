<div align="center">

# ⚡ AetherOS Kernel ⚡
### *A 32-Bit Bare-Metal Protected-Mode Microkernel in C++ & Assembly*

![Arch](https://img.shields.io/badge/Architecture-x86__32--bit-00599C?style=for-the-badge&logo=intel)
![Language](https://img.shields.io/badge/Language-C%2B%2B%20%26%20NASM-F34B7D?style=for-the-badge&logo=c%2B%2B)
![Standard](https://img.shields.io/badge/Multiboot-Compliant-brightgreen?style=for-the-badge)
![Environment](https://img.shields.io/badge/Runtime-Freestanding%20(No--std)-orange?style=for-the-badge)

<p align="center">
  <b>Direct hardware memory-mapped manipulation, protected-mode entry, and low-level kernel routines built without external standard libraries.</b>
</p>

---

</div>

## 🧬 Architectural Topology

```text
       +-------------------------------------------------------+
       |             Direct Hardware Layer (x86)               |
       |  - 32-bit Protected Mode CPU Registers (CR0, EIP)    |
       |  - Video MMIO Text Framebuffer (0x000B8000)           |
       +───────────────────────────┬───────────────────────────+
                                   │
                                   ▼
       +───────────────────────────────────────────────────────+
       |                  AetherOS Core Subsystems             |
       +───────────────────────────┬───────────────────────────+
                                   │
         ┌─────────────────────────┴─────────────────────────┐
         ▼                                                   ▼
┌─────────────────────────────────┐   ┌─────────────────────────────────┐
│           boot.asm              │   │           kernel.cpp            │
│  - Multiboot 1 KiB Header       │   │  - Freestanding C++ Runtime     │
│  - 16 KiB Kernel Stack Setup    │   │  - MMIO Direct Screen Driver    │
│  - Transition to Protected Mode │   │  - Hardware Color Attributes    │
└─────────────────────────────────┘   └─────────────────────────────────┘
