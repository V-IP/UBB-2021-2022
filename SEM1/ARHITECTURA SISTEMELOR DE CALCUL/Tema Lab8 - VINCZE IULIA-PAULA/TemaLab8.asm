bits 32
global start

extern exit
import exit msvcrt.dll

segment data use32 class=data
    
    s dd 12345678h,1A2B3C4Dh,0FE98DC76h
    len equ ($-s)/4
    trei db 3
    d times len db 0 ; d=12h
    
segment code use32 class=code
    start:
        ; 7. Se da un sir de dublucuvinte. Sa se obtina sirul format din octetii superiori ai cuvitelor superioare din elementele sirului de dublucuvinte care sunt divizibili cu 3
        ; VINCZE IULIA-PAULA
        
        mov esi, s
        mov edi, d
        cld 
        mov ecx, len
        
        repeta:
            lodsd
            shr eax, 24 
            push ax
            div byte [trei]
            cmp ah, 0
            
            jnz nedivizibil
            pop ax
            stosb
            
            nedivizibil:
        loop repeta
        
        push    dword 0
        call    [exit]
