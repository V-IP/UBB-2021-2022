bits 32
global start

extern exit,printf
import exit msvcrt.dll
import printf msvcrt.dll

extern prefix

segment data use32 class=data public
    
    sir1 db "impiedicat",0
    l1 equ $-sir1
    sir2 db "imbatranit",0
    l2 equ $-sir2
    sir3 db "impotrivit",0
    format db "%s",0
    rez12 times l1 db 0
    rez13 times l1 db 0
    rez23 times l2 db 0
    
segment code use32 class=code public
    start:
        ;7. Se dau trei siruri de caractere. Sa se afiseze cel mai lung prefix comun pentru fiecare din cele trei perechi de cate doua siruri ce se pot forma.
        ;Programare multi-modul (asm+asm) - VINCZE IULIA-PAULA
        
        ;prefix(sir1,l1,sir2,rez12)
        push dword rez12
        push dword sir2
        push dword l1
        push dword sir1
        call prefix
        add esp,4*5
        
        mov edx, rez12
        mov al,0ah
        stosb
        
        ;printf(format,rez12)
        push dword rez12
        push dword format
        call [printf]
        add esp,4*2
        
        ;prefix(sir1,l1,sir3,rez13)
        push dword rez13
        push dword sir3
        push dword l1
        push dword sir1
        call prefix
        add esp,4*5
        
        mov edx, rez13
        mov al,0ah
        stosb
        
        ;printf(format,rez13)
        push dword rez13
        push dword format
        call [printf]
        add esp,4*2
        
        ;prefix(sir2,l2,sir3,rez23)
        push dword rez23
        push dword sir3
        push dword l2
        push dword sir2
        call prefix
        add esp,4*5
        
        ;printf(format,rez23)
        push dword rez23
        push dword format
        call [printf]
        add esp,4*2
        
        push    dword 0
        call    [exit]