bits 32 

global start        

extern exit               
import exit msvcrt.dll

segment data use32 class=data

segment code use32 class=code
    start:
    ; EXERCITII SIMPLE 7) 256/1 - VINCZE IULIA-PAULA
        mov eax, 0
        mov ebx, 0
        mov ax, 256
        mov bl, 1
        div bl
        
        push    dword 0
        call    [exit]
