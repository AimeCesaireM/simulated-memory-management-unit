---

# Simulated Memory Management Unit (MMU)

This project implements a simulated Memory Management Unit (MMU), a crucial component in modern computer systems responsible for translating virtual addresses to physical addresses. The simulation models a two-level page table system commonly used in virtual memory systems.

## Overview

The MMU is designed to translate virtual addresses to physical addresses by following the steps outlined in the `mmu_translate()` function. This involves decomposing the virtual address into various parts, looking up the corresponding entries in the upper and lower page tables, and handling page faults when necessary.

## Features

- **Two-level page table simulation**: Simulates the process of translating a virtual address to a real address using two page tables—upper and lower.
- **Page fault handling**: Handles cases where an entry in the page table is missing or invalid, ensuring that page faults are appropriately simulated and managed.
- **Debugging output**: Prints detailed information for debugging purposes, including virtual address breakdown, page table indices, and real address translation.
  
## File Structure

```
/project_root
│
├── mmu.c          # Contains the implementation of the MMU functions
├── mmu.h          # Header file for MMU function declarations and definitions
├── vmsim.c        # Virtual memory simulation helper functions (for reading page table entries, handling faults, etc.)
├── Makefile       # Makefile for building the project
└── iterative-walk.c  # Example program using the MMU
└── random-hop.c   # Another example program using the MMU
```

## Key Functions

### `mmu_init()`

Initializes the MMU by setting the address of the upper page table.

```c
void mmu_init(vmsim_addr_t new_upper_pt_addr);
```

**Parameters**:
- `new_upper_pt_addr`: The address of the upper page table.

### `mmu_translate()`

Translates a virtual address into a real address using a two-level page table.

```c
vmsim_addr_t mmu_translate(vmsim_addr_t sim_addr);
```

**Parameters**:
- `sim_addr`: The virtual address to be translated.

**Returns**:
- The real address corresponding to the virtual address.

**Details**:
1. The function decomposes the virtual address into a page table index and an offset.
2. It checks the upper and lower page tables for valid entries.
3. If a page fault occurs (i.e., an entry is missing or invalid), the function invokes a page fault handler and attempts the translation again.

### `vmsim_read_real()`

Reads data from a real memory address, used to fetch entries from the page tables.

```c
void vmsim_read_real(void *dest, vmsim_addr_t src, size_t size);
```

**Parameters**:
- `dest`: The destination buffer to read data into.
- `src`: The source address to read data from.
- `size`: The number of bytes to read.

### `vmsim_map_fault()`

Handles a page fault by simulating the mapping of a missing page.

```c
void vmsim_map_fault(vmsim_addr_t sim_addr);
```

**Parameters**:
- `sim_addr`: The virtual address causing the page fault.

## Compilation Instructions

To compile the project, follow these steps:

1. **Ensure you have the necessary dependencies**:
   - GCC compiler (for C)
   - Make utility (for building the project)

2. **Clone the repository**:
   ```bash
   git clone https://github.com/AimeCesaireM/simulated-memory-management.git
   cd simulated-memory-management
   ```

3. **Run `make` to compile the project**:
   - To build the shared library and the example programs, run:
     ```bash
     make
     ```

   This will compile the following:
   - **libvmsim.so**: The shared library containing the MMU implementation and virtual memory simulation functions.
   - **iterative-walk**: An example program using the MMU.
   - **random-hop**: Another example program using the MMU.

4. **Clean up**: To remove all generated files (object files, shared libraries, and executables), run:
   ```bash
   make clean
   ```

## Usage

To use the simulated MMU in a program:

1. **Initialize the MMU**: Call `mmu_init()` with the address of the upper page table.
2. **Translate Virtual Addresses**: Call `mmu_translate()` with a virtual address to obtain the corresponding physical address.

### Example

```c
// Initialize MMU with the address of the upper page table
mmu_init(0x1000);

// Translate a virtual address to a physical address
vmsim_addr_t real_address = mmu_translate(0xABCDEF01);
printf("Real Address: %x\n", real_address);
```

## License

This project is licensed under the MIT License.

---
