bits 32

global start        

extern exit               
import exit msvcrt.dll   

segment data use32 class=data
    a db 2
    b db 3
    ce db 4
    d db 5
segment code use32 class=code
    start:
        ;INMULTIRI, IMPARTIRI BYTE (a+b)*(c+d) - VINCZE IULIA-PAULA
        mov eax, 0
        mov ebx, 0
        mov al, [a]
        add al, [b]
        mov bl, [ce]
        add bl, [d]
        mul bl
        
        push    dword 0
        call    [exit]
