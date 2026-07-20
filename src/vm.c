#include <stdio.h>
#include "vm.h"
#include "instructions.h"
#include <string.h>

// vm.h implementation
void vm_init(VirtualMachine* vm) {
    // Set memory, registers and Stack to 0
    memset(vm->memory, 0, MEMORY_SIZE);
    memset(vm->registers, 0, sizeof(vm->registers));
    memset(vm->stack, 0, sizeof(vm->stack));
    
    vm->ip = 0;
    vm->sp = 0;
    vm->running = false;
}

void vm_load_program(VirtualMachine* vm, uint8_t* program, int size) {
    if (size > MEMORY_SIZE) {
        printf("ERROR: Program is bigger than memory.\n");
        return;
    }
    memcpy(vm->memory, program, size);
}

// Methods for the Stack
void push(VirtualMachine* vm, int value) {
    if (vm->sp >= STACK_SIZE) {
        printf("FATAL ERROR: Stack Overflow\n");
        vm->running = false;
        return;
    }
    vm->stack[vm->sp] = value;
    vm->sp++; 
}

int pop(VirtualMachine* vm) {
    if (vm->sp <= 0) {
        printf("FATAL ERROR: Stack Underflow\n");
        vm->running = false;
        return 0;
    }
    vm->sp--;
    return vm->stack[vm->sp];
}

void print_debugger(VirtualMachine *vm) {
    printf("\n==================== VM DEBUGGER ====================\n");
    
    // Print IP and Opcode
    printf("IP: %04d   |   Following Opcode: 0x%02X\n", vm->ip, vm->memory[vm->ip]);
    printf("-----------------------------------------------------\n");
    
    // Print registers
    printf("REGISTERS: ");
    for (int i = 0; i < NUM_REGISTERS; i++) {
        printf("R%d:[%d]  ", i, vm->registers[i]);
    }
    printf("\n");
    printf("-----------------------------------------------------\n");

    // Print Stack and SP
    printf("STACK (SP: %d): [ ", vm->sp);
    for (int i = 0; i < vm->sp; i++) {
        printf("%d ", vm->stack[i]);
    }
    printf("]\n");
    printf("=====================================================\n\n");
}

// Main loop
void vm_run(VirtualMachine* vm) {
    vm->running = true;
    bool debug_mode = false;

    printf("Starting Virtual Machine...\n");
    // Infinite loop
    while (vm->running && vm->ip < MEMORY_SIZE) {

        if (debug_mode) {
            print_debugger(vm);
            
            printf("Press ENTER to execute following instruction");
            getchar();
        }
        
        // INSTRUCTION FETCH (Read byte and add 1 to IP)
        uint8_t opcode = vm->memory[vm->ip];
        vm->ip++; 

        //DECODE AND EXECUTE
        switch (opcode) {
            
            case HLT:
                printf("VM [HLT] -> Execution stopped.\n");
                vm->running = false;
                break;

            case PSH: {
                // We take the following 4B after the Opcode
                int value = *(int*)&vm->memory[vm->ip];
                
                // Add 4 to IP as we've read a 4B value
                vm->ip += 4; 
                
                push(vm, value);
                printf("VM [PSH] -> Value pushed: %d\n", value);
                break;
            }

            case POP: {
                int value = pop(vm);
                printf("VM [POP] -> Value popped: %d\n", value);
                break;
            }

            case ADD: {
                int b = pop(vm); 
                int a = pop(vm); 
                
                int result = a + b;
                push(vm, result);
                
                printf("VM [ADD] -> %d + %d = %d (Result added to the Stack)\n", a, b, result);
                break;
            }

            case SUB: {
                int b = pop(vm); 
                int a = pop(vm); 
                
                int result = a - b;
                push(vm, result);
                
                printf("VM [ADD] -> %d + %d = %d (Result Added to the Stack)\n", a, b, result);
                break;
            }

            case SET: {
                // Read register index
                uint8_t reg_index = vm->memory[vm->ip];
                vm->ip++; // Add 1 to IP as we've read the register index
                
                // Read the value that will be stored in the index
                int value = *(int*)&vm->memory[vm->ip];
                vm->ip += 4; // Add 4 to IP as we've read the 4 Bytes value

                if (reg_index >= NUM_REGISTERS) {
                    printf("ERROR: Register index %d not valid\n", reg_index);
                    vm->running = false;
                    break;
                }
                
                vm->registers[reg_index] = value;
                printf("VM [SET] -> Register R%d has the value %d\n", reg_index, value);
                break;
            }

            case JMP: {
                // Read the address we want to jump
                int address = *(int*)&vm->memory[vm->ip];
                
                if (address < 0 || address >= MEMORY_SIZE) {
                    printf("ERROR: Invalid jump address %d\n", address);
                    vm->running = false;
                    break;
                }
                
                // IP is now pointing to new address
                vm->ip = address;
                
                printf("VM [JMP] -> Jumped to the address %d\n", address);
                break;
            }

            case GET: {
                // Read register index
                uint8_t reg_index = vm->memory[vm->ip];
                vm->ip++; // Add 1 to IP as we've read the register index
                
                int value = vm->registers[reg_index];
                push(vm, value);
                printf("VM [GET] -> Read %d from register R%d and added to the Stack\n", value, reg_index);
                break;
            }
            
            case STR: {
                // Read register index
                uint8_t reg_index = vm->memory[vm->ip];
                vm->ip++; // Add 1 to IP as we've read the register index
                
                int value = pop(vm);
                vm->registers[reg_index] = value;
                printf("VM [STR] -> Popped %d from the Stack and stored in register R%d\n", value, reg_index);
                break;
            }

            case BZ: {
                // Read Memory address (4 Bytes)
                int address = *(int*)&vm->memory[vm->ip];
                vm->ip += 4;
                
                int condition = pop(vm);
                
                if (condition == 0) {
                    vm->ip = address;
                    printf("VM [JZ]  -> Condition is true. Jumping to %d\n", address);
                } else {
                    printf("VM [JZ]  -> Condition is false (%d is not 0). Not jumping.\n", condition);
                }
                break;
            }

            case BNZ: {
                // Read Memory address (4 Bytes)
                int address = *(int*)&vm->memory[vm->ip];
                vm->ip += 4;
                
                int condition = pop(vm);
                
                if (condition != 0) {
                    vm->ip = address;
                    printf("VM [JNZ] -> Condition is true (%d is not 0). Jumping to %d\n", condition, address);
                } else {
                    printf("VM [JNZ] -> Condition is false. Not jumping.\n", condition);
                }
                break;
            }

            case LOAD: {
                // Read Memory address (4 Bytes)
                int address = *(int*)&vm->memory[vm->ip];
                vm->ip += 4;
                
                if (address < 0 || address >= MEMORY_SIZE - 3) {
                    printf("ERROR: Load in %d is out of range.\n", address);
                    vm->running = false;
                    break;
                }
                
                // Turn address int
                int value = *(int*)&vm->memory[address];
                
                // Push value to the Stack
                push(vm, value);
                printf("VM [LOAD] -> Load %d to the Stack, from memory address %d.\n", value, address);
                break;
            }

            case STORE: {
                // Read Memory address (4 Bytes)
                int address = *(int*)&vm->memory[vm->ip];
                vm->ip += 4;
                
                if (address < 0 || address >= MEMORY_SIZE - 3) {
                    printf("ERROR: Store in %d is out of range.\n", address);
                    vm->running = false;
                    break;
                }
                
                // Pop value from the Stack
                int value = pop(vm);
                
                // Value added to the memory
                *(int*)&vm->memory[address] = value;
                
                printf("VM [STORE] -> Store %d in memory adress %d.\n", value, address);
                break;
            }

            case BEQ: {
                // Read the address we want to jump (4 Bytes)
                int address = *(int*)&vm->memory[vm->ip];
                vm->ip += 4;
                
                if (address < 0 || address >= MEMORY_SIZE) {
                    printf("ERROR: Invalid jump address %d\n", address);
                    vm->running = false;
                    break;
                }
                // Pop the two values
                int b = pop(vm);
                int a = pop(vm);
                
                if (a == b) {
                    vm->ip = address;
                    printf("VM [BEQ] -> Condition is true (%d == %d). Jumping to %d\n", a, b, address);
                } else {
                    printf("VM [BEQ] -> Condition is false (%d != %d). Not jumping.\n", a, b);
                }
                break;
            }

            case BNE: {
                int address = *(int*)&vm->memory[vm->ip];
                vm->ip += 4;
                
                if (address < 0 || address >= MEMORY_SIZE) {
                    printf("ERROR: Invalid jump address %d\n", address);
                    vm->running = false;
                    break;
                }
                
                int b = pop(vm);
                int a = pop(vm);
                
                if (a != b) {
                    vm->ip = address;
                    printf("VM [BNE] -> Condition is true (%d != %d). Jumping to %d\n", a, b, address);
                } else {
                    printf("VM [BNE] -> Condition is false (%d == %d). Not jumping.\n", a, b);
                }
                break;
            }

            case BGT: {
                int address = *(int*)&vm->memory[vm->ip];
                vm->ip += 4;
                
                if (address < 0 || address >= MEMORY_SIZE) {
                    printf("ERROR: Invalid jump address %d\n", address);
                    vm->running = false;
                    break;
                }
                
                int b = pop(vm);
                int a = pop(vm);
                
                if (a > b) {
                    vm->ip = address;
                    printf("VM [BGT] -> Condition is true (%d > %d). Jumping to %d\n", a, b, address);
                } else {
                    printf("VM [BGT] -> Condition is false (%d <= %d). Not jumping.\n", a, b);
                }
                break;
            }

            case BLT: {
                int address = *(int*)&vm->memory[vm->ip];
                vm->ip += 4;
                
                if (address < 0 || address >= MEMORY_SIZE) {
                    printf("ERROR: Invalid jump address %d\n", address);
                    vm->running = false;
                    break;
                }
                
                int b = pop(vm);
                int a = pop(vm);
                
                if (a < b) {
                    vm->ip = address;
                    printf("VM [BLT] -> Condition is true (%d < %d). Jumping to %d\n", a, b, address);
                } else {
                    printf("VM [BLT] -> Condition is false (%d >= %d). Not jumping.\n", a, b);
                }
                break;
            }

            case BGE: {
                int address = *(int*)&vm->memory[vm->ip];
                vm->ip += 4;
                
                if (address < 0 || address >= MEMORY_SIZE) {
                    printf("ERROR: Invalid jump address %d\n", address);
                    vm->running = false;
                    break;
                }
                
                int b = pop(vm);
                int a = pop(vm);
                
                if (a >= b) {
                    vm->ip = address;
                    printf("VM [BGE] -> Condition is true (%d >= %d). Jumping to %d\n", a, b, address);
                } else {
                    printf("VM [BGE] -> Condition is false (%d < %d). Not jumping.\n", a, b);
                }
                break;
            }

            case BLE: {
                int address = *(int*)&vm->memory[vm->ip];
                vm->ip += 4;
                
                if (address < 0 || address >= MEMORY_SIZE) {
                    printf("ERROR: Invalid jump address %d\n", address);
                    vm->running = false;
                    break;
                }
                
                int b = pop(vm);
                int a = pop(vm);
                
                if (a <= b) {
                    vm->ip = address;
                    printf("VM [BLE] -> Condition is true (%d <= %d). Jumping to %d\n", a, b, address);
                } else {
                    printf("VM [BLE] -> Condition is false (%d > %d). Not jumping.\n", a, b);
                }
                break;
            }

            default:
                printf("FATAL ERROR: Unknown Opcode 0x%02X in address %d.\n", opcode, vm->ip - 1);
                vm->running = false;
                break;
        }
    }
    
    printf("Virtual Machine Stopped\n");
}