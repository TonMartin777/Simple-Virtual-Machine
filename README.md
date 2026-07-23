# Simple 32-bit Stack-Based Virtual Machine

This project is a functional 32-bit stack-based virtual machine implementing a Von Neumann architecture. Includes an execution engine in C that reads and executes the program code in binary 
and an assembly in Python that translates a given program from assembly code into binary.

Developed to showcase core competencies in low-level computing, direct memory management, algorithmic logic and clean software design principles.

## Key Features

* **Architecture:** 32-bit word alignment, little-endian format and unified memory design.
* **Custom Assembler:** Python tool that parses and translates assembly code into executable binary bytecode (`.bin` files).
* **Integrated Debugger:** Real-time stack tracing and memory dumping that intelligently separates executable code from data segments.
* **Instruction Set:** Support for stack manipulation (PUSH, POP), memory access (LOAD, STORE), arithmetic operations, and conditional branching (BEQ, JMP).

## Project Structure

Based on the repository organization:

* `/assembler`: Custom assembly translation tool (`asm.py`).
* `/docs`: Contains the architectural documentation (`ISA Reference Manual.pdf`).
* `/include`: C header files defining the instruction set and VM architecture. (`instructions.h`, `vm.h`)
* `/programs`: Assembly test programs and their compiled binaries (`fibonacci`, `memory_max`, `product`).
* `/src`: Virtual machine source code (`main.c`, `vm.c`).
* `Makefile`: Build automation configuration.

## Prerequisites

* C Compiler (like GCC/MinGW for Windows environments)
* *Optional:* `make` build automation tool
* Python 3.x (to run the assembler)

## Build and Execution

**1. Build the Virtual Machine**

If you have `make` installed, run the following command in the root directory (works on both Linux and Windows):
`make`

*Alternative (Without `make`):* 
If you need to compile the project manually using GCC, ensure you include the headers folder:
* **Linux:** `gcc src/main.c src/vm.c -I include -o vm`
* **Windows:** `gcc src\main.c src\vm.c -I include -o vm.exe`

**2. Assemble a Program**

Use the Python assembler to generate the binary file from an assembly text file. For example, to assemble the `fibonacci` program:
* **Linux:** `python3 assembler/asm.py programs/fibonacci.asm -o programs/fibonacci.bin`
* **Windows:** `python assembler\asm.py programs\fibonacci.asm -o programs\fibonacci.bin`

**3. Run the Program**

Pass the compiled binary to the virtual machine to execute it:
* **Linux:** `./vm programs/fibonacci.bin`
* **Windows:** `.\vm.exe programs\fibonacci.bin`

## Debugger Mode

To analyze the internal state of the machine, visualize stack operations step-by-step, and perform a data memory dump upon halting, run the VM with the `-d` flag:

* **Linux:** `./vm -d programs/fibonacci.bin`
* **Windows:** `.\vm.exe -d programs\fibonacci.bin`
