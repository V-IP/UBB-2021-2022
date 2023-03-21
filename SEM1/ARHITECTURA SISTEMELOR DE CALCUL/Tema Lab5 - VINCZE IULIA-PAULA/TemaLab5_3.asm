bits 32

global start

extern exit
import exit msvcrt.dll

segment data use32 class=data
    ;a-doubleword; b-byte; c-word; x-qword
    b db 45 ;al
    ce dw 15 ;ax
    a dd 200 ;eax
    x dq 2
    
segment code use32 class=code
    start:
        ;5. (a+b/c-1)/(b+2)-x - VINCZE M. IULIA-PAULA
        ; - Interpretare fara semn
        mov edx, 0
        mov eax, 0
        mov al, [b] ;dx:ax=b
        div word [ce] ;ax=b/c
        add ax, [a]
        adc dx, [a+2] ;dx:ax=a+b/c
        sub ax, word 1
        sbb dx, 0
        mov bx, 0
        mov bl, [b]
        add bx, word 2
        div bx ;ax=(a+b/c-1)/(b+2)
        mov edx, 0
        sub eax, [x]
        sbb edx, [x+4] ;edx:eax=(a+b/c-1)/(b+2)-x
        
        push    dword 0
        call    [exit]
