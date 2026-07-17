#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

// Opcode of the instruction (1 Byte)
typedef enum {
    HLT = 0x00,     // Stop execution
    PSH = 0x01,     // Push value (arg1) to Stack
    POP = 0x02,     // Pop top of the Stack (Pointed by SP)
    ADD = 0x03,     // Add 2 values from the Stack
    SUB = 0x04,     // Substract 2 values from the Stack
    SET = 0x05,     // Store value (arg2) in register (arg1)
    JMP = 0x06,     // Change IP
    GET = 0x07,     // Load value from register (arg1) to Stack
    STR = 0x08,     // Store value from Stack to register (arg1)
    BZ = 0x09,      // Jump if value pointed by SP is 0
    BNZ = 0x0A,     // Jump if value pointed by SP is not 0
    LOAD = 0x0B,    // Push value from Memory (arg1) to Stack
    STORE = 0x0C    // Store top of the Stack in Memory (arg1)

} Opcode;

#endif