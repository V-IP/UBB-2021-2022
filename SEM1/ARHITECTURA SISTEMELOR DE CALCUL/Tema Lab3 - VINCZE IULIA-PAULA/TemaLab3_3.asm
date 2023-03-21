bits 32

global start        

extern exit
import exit msvcrt.dll

segment data use32 class=data
    a dw 350
    b dw 672
    ce dw 456
    d dw 729
segment code use32 class=code
    start:
        ;ADUNARI, SCADERI WORD 7) (c+c+c)-b+(d-a) - VINCZE IULIA-PAULA
        mov eax, 0
        mov ebx, 0
        mov ecx, 0
        mov ax, [ce]
        add ax, [ce]
        add ax, [ce]
        mov bx, [b]
        sub ax, bx
        mov bx, [d]
        mov cx, [a]
        sub bx, cx
        add ax, bx
        
        
        push    dword 0
        call    [exit]
