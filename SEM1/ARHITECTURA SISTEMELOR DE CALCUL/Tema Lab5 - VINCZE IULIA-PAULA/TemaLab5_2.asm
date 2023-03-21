bits 32

global start

extern exit
import exit msvcrt.dll

segment data use32 class=data
    ;a - byte, b - word, c - double word, d - qword
    a db 10
    b dw -30
    ce dd 80
    d dq -50
    
segment code use32 class=code
    start:
        ;5. (c+b+b)-(c+a+d) - VINCZE M. IULIA-PAULA
        ; - Interpretare cu semn
        mov ax, [b] ;ax=b
        cwd ;dx:ax=b
        push dx
        push ax
        pop eax ;eax=b
        add eax, eax ;eax=b+b
        add eax, [ce] ;eax=c+b+b
        mov ebx, eax ;ebx=c+b+b
        mov ecx, 0
        mov al, [a] ;al=a
        cbw ;ax=a
        cwd ;dx:ax=a
        push dx
        push ax
        pop eax ;eax=a
        mov edx, 0
        add eax, [ce] ;eax=c+a
        add eax, [d] 
        adc edx, [d+4] ;edx:eax=c+a+d
        sub ebx, eax
        sbb ecx, edx ; ecx:ebx=(c+b+b)-(c+a+d)
        
        push    dword 0
        call    [exit]
