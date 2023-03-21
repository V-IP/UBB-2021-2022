bits 32
global start        

extern exit               
import exit msvcrt.dll   

segment data use32 class=data
    d dw 2
segment code use32 class=code
    start:
        ;INMULTIRI, IMPARTIRI WORD 7) [100*(d+3)-10]/d - VINCZE IULIA-PAULA
        mov eax, 0
        mov ax, [d]
        add ax, 3
        mov bx, 100
        mul bx
        mov bx, 10
        sub ax, bx
        div word [d]
        push    dword 0
        call    [exit]
