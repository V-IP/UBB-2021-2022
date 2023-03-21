bits 32

global start        

extern exit               
import exit msvcrt.dll    

segment data use32 class=data
    ce db 32
    d db 2
    a db 3
    b db 5
segment code use32 class=code
    start:
        ;ADUNARI, SCADERI BYTE 7) c-(d+d+d)+(a-b) - VINCZE IULIA-PAULA
        mov eax,0
        mov ebx,0
        mov ecx,0 
        mov edx,0
        mov al, [ce]
        mov bl, [d]
        add bl, [d]
        add bl, [d]
        sub ax, bx
        mov bl, [a]
        mov cl, [b]
        sub bx, cx
        add ax, bx
        
        push    dword 0
        call    [exit]
