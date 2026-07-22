; Fibonacci Sequence Calculator

; Init Registers
SETI 0 10       ; R0 = 10 (Loop counter)
SETI 1 0        ; R1 = 0  (Actual Value)
SETI 2 1        ; R2 = 1  (Following Value)

loop_start:
    ; Check if counter == 0, if so jump to end
    PUSHR 0     ; R0 -> Stack
    PUSH 0      ; imm 0 -> Stack
    BEQ end     ; if R0 == 0, jump to end

    ; R1 + R2 ---> R3
    PUSHR 1     ; R1 -> Stack
    PUSHR 2     ; R2 -> Stack
    ADD         ; R1 + R2 -> Stack
    POPR 3      ; Stack -> R3

    ; R2 ---> R1 (Update actual value)
    PUSHR 2     ; R2 -> Stack
    POPR 1      ; Stack -> R1

    ; R3 ---> R2 (Following value is the addition)
    PUSHR 3     ; R3 -> Stack
    POPR 2      ; Stack -> R2

    ; R0 - 1 ---> R0 (Substract 1 from counter)
    PUSHR 0     ; R0 -> Stack
    PUSH 1      ; imm 1 -> Stack
    SUB         ; R0 - 1 -> Stack
    POPR 0      ; Stack -> R0

    ; Restart loop
    JMP loop_start

end:
    ; R1 = 55
    PUSHR 1     ; R1 -> Stack
    HLT         ; Stop Virtual Machine