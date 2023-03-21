bits 32

global start

extern exit
import exit msvcrt.dll

segment data use32 class=data
    ;a-doubleword; b-byte; c-word; x-qword
    b db 45
    ce dw -15
    a dd 200
    x dq -2
    ; rez = 6
    
segment code use32 class=code
    start:
        ;5. (a+b/c-1)/(b+2)-x - VINCZE M. IULIA-PAULA
        ; - Interpretare cu semn
        mov al, [b] ;al=b
        cbw ;ax=b
        add ax, word 2 ;ax=b+2
        mov bx, ax ;bx=b+2
        mov al, [b] ;al=b
        cbw
        cwd ;dx:ax=b
        idiv word [ce] ;ax=b/c
        cwd ;dx:ax=b/c
        add ax, [a]
        adc dx, [a+2] ;dx:ax=a+b/c
        sub ax, word 1
        sbb dx, 0 ;dx:ax=a+b/c-1
        idiv bx ;ax=(a+b/c-1)/(b+2)
        cwde ;eax=(a+b/c-1)/(b+2)
        cdq ;edx:eax=(a+b/c-1)/(b+2)
        sub eax, [x]
        sbb edx, [x+4] ;edx:eax=(a+b/c-1)/(b+2)-x
        
        push    dword 0
        call    [exit]
