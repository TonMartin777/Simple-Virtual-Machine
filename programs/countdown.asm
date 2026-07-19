; --- countdown.asm ---
; Loop that counts from 3 to 0

SET 0 3        ; R0 = 3

loop:          ; Loop Label
GET 0          ; Stack = R0
BZ end         ; If Stack == 0, jump to end

GET 0          ; R0 -> Stack
PSH 1          ; Stack = 1
SUB            ; Stack = R0 - 1
STR 0          ; Sta

JMP loop       ; Jump to Loop Label
end:           ; End Label
HLT