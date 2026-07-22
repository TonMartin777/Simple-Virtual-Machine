; Loads two values from memory and stores the maximum in a new memory address.

; Load values from address 256 and 260 to the Stack
LOAD 256                ; Memory(256) -> Stack
LOAD 260                ; Memory(260) -> Stack

; Store values in register
POPR 1                  ; Stack -> R1 (Value from address 260 is B)
POPR 0                  ; Stack -> R0 (Value from address 256 is A)

; Compare values
PUSHR 0                 ; R0 -> Stack
PUSHR 1                 ; R1 -> Stack
BGT a_is_greater        ; If A > B, jump to a_is_greater, else, continue in b_is_greater

b_is_greater:
    PUSHR 1             ; R1 -> Stack
    JMP store_result    ; Jump to store_result

a_is_greater:
    PUSHR 0             ; R0 -> Stack

store_result:
    STORE 264           ; Stack -> Memory(264)
    HLT                 ; Stop Virtual Machine