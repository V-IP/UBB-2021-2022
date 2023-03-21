bits 32

global start

extern exit
import exit msvcrt.dll

segment data use32 class=data
    ;a - byte, b - word, c - double word, d - qword
    a db 10
    b dw 30
    ce dd 80
    d dq 50
    
segment code use32 class=code
    start:
        ; (c-a-d)+(c-b)-a - VINCZE M. IULIA-PAULA
        ; - Interpretare fara semn
        mov eax, [ce] ; eax = c
        mov ebx, 0
        mov bl, [a] ; ebx = a
        sub eax, ebx ; eax = c-a
        mov edx, 0
        mov ebx, [d]
        mov ecx, [d+4] ; ecx:ebx = d
        sub eax, ebx
        sbb edx, ecx ; edx:eax = c-a-d
        mov ebx, [ce] ; ebx = c
        mov ecx, 0
        mov cx, [b] ; ecx = b
        sub ebx, ecx ; ebx = c-b
        add eax, ebx 
        adc edx, 0 ; edx:eax = (c-a-d)+(c-b)
        mov ebx, 0
        mov bl, [a] ; ebx = a
        sub eax, ebx
        sbb edx, 0 ; edc:eax = (c-a-d)+(c-b)-a
        
        push    dword 0
        call    [exit]
