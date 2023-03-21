bits 32
global start

extern exit
import exit msvcrt.dll

segment data use32 class=data
    
    s1 db 1,3,5,7
    ls1 equ ($-s1)
    s2 db 2,6,9,4
    d times ls1+ls1 db 0 ;1,2,3,6,5,9,7,4
    
segment code use32 class=code
    start:
        ; Se dau doua siruri de octeti S1 si S2 de aceeasi lungime. Sa se obtina sirul D prin intercalarea elementelor celor doua siruri.
        ; - VINCZE M. IULIA-PAULA
        mov eax, 0
        mov ebx, 0 ;pastram contorul indicelui lungimii
        
        mov esi, s1
        mov edi, d
        
        mov ecx, ls1
        jecxz final
        cld
        repeta:
            mov al, [s1+ebx]
            stosb; edi<-[al]
            mov esi, s2
            mov al, [s2+ebx]
            stosb; edi<-[al]
            mov esi, s1
            add ebx, 1
        loop repeta
        final:
        push    dword 0
        call    [exit]
