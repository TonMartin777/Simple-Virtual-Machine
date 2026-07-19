; --- test.asm ---
; 20 + 5 -> R1

PSH 20       ; Push 20
PSH 5        ; Push 5
ADD          ; 5 + 20 -> Top
SET 1 99     ; R1 = 99
STR 2        ; Sacamos el 25 de la pila y lo guardamos en R2
HLT          ; Apagamos la CPU