#include <stdio.h>
#include "vm.h"
#include "instructions.h"

int main() {
    VirtualMachine vm;
    
    // Init virtual machine
    vm_init(&vm);

    // Push 20, Push 5, 5 + 20 = 25, Store 25 in Register 1, Stop VM
    uint8_t program[] = {
        PSH, 0x14, 0x00, 0x00, 0x00, // Opcode, 20
        PSH, 0x05, 0x00, 0x00, 0x00, // Opcode, 5
        ADD, // Opcode (5 + 20)
        SET, 0x01, 99, 0x63, 0x00, 0x00, // Opcode, Register 1, 99
        HLT
    };

    // Load program with index 0
    vm_load_program(&vm, program, sizeof(program));

    // Run CPU
    vm_run(&vm);

    if (vm.sp > 0) {
        printf("Top of the Stack (Should be 25): %d\n", vm.stack[vm.sp - 1]);
    }

    return 0;
}