#ifndef VM_H
#define VM_H

#include <stdint.h>
#include <stdbool.h>

// Hardware limitations
#define MEMORY_SIZE 4096   // 4 KB Memory
#define STACK_SIZE 256     // # of instructions at the same time
#define NUM_REGISTERS 4    // 4 Registers (A, B, C, D)

// Representation of CPU and Memory
typedef struct {
    uint8_t memory[MEMORY_SIZE];  // Memory (Instructions and Data)
    
    int stack[STACK_SIZE];        // Stack
    int sp;                       // Stack Pointer (Top)
    
    int registers[NUM_REGISTERS]; // Registers
    
    int ip;                       // Instruction Pointer (Code)
    bool running;                 // State of the machine
} VirtualMachine;

// Public Interface
void vm_init(VirtualMachine* vm);
void vm_load_program(VirtualMachine* vm, uint8_t* program, int size);
void vm_run(VirtualMachine* vm);

#endif