#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

// Opcode of the instruction (1 Byte)
typedef enum {
    HLT = 0x00, // Stop execution
    PSH = 0x01, // Push value to Stack (4 Bytes)
    POP = 0x02, // Pop top of the Stack (Pointed by SP)
    ADD = 0x03, // Add 2 values from the Stack
    SUB = 0x04, // Substract 2 values from the Stack
    SET = 0x05, // Store value in register
    JMP = 0x06  // Change IP
} Opcode;

#endif