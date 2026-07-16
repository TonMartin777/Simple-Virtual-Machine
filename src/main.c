#include <stdio.h>
#include "vm.h"
#include "instructions.h"

int main() {
    VirtualMachine vm;
    
    // Init virtual machine
    vm_init(&vm);

    // Push 20, Push 5, 5 + 20 = 25, Store 25 in Register 1, Stop VM
uint8_t program[] = {
        SET, 0, 3, 0, 0, 0,    // R0 = 3
        
        // LOOP
        GET, 0,                 // R0 -> Stack [3]
        BZ, 28, 0, 0, 0,        // If Top == 0 jump to END
        
        GET, 0,                 // R0 -> Stack [3, 3]
        PSH, 1, 0, 0, 0,        // Push 1 to Stack [1, 3, 3]
        SUB,                    // 3 - 1 = 2 to Stack [2, 3]
        STR, 0,                 // R0 = 2
        JMP, 6, 0, 0, 0,        //Jump to LOOP
        
        // END
        HLT                     // Stop VM
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