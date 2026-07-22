; Product via Repeated Addition

; Init Registes
SETI 0 7        ; R0 = 7 (Multiplicand)
SETI 1 5        ; R1 = 5 (Multiplier used as counter)
SETI 2 0        ; R2 = 0 (Result)

loop_start:
    ; Check if R1 == 0, if so jump to end
    PUSHR 1     ; R1 -> Stack
    PUSH 0      ; imm 0 -> Stack
    BEQ end     ; if R1 == 0, jump to end

    ; R0 + R2 --- R2
    PUSHR 2     ; R2 -> Stack
    PUSHR 0     ; R0 -> Stack
    ADD         ; R2 + R0 -> Stack
    POPR 2      ; Stack -> R2

    ; Substract 1 from counter
    PUSHR 1     ; R1 -> Stack
    PUSH 1      ; imm -> Stack
    SUB         ; B - 1 -> Stack
    POPR 1      ; Stack -> R1
    
    ; Restart loop
    JMP loop_start

end:
    ; R2 = 35
    PUSHR 2     ; R2 -_ Stack
    HLT         ; Stop Virtual Machine