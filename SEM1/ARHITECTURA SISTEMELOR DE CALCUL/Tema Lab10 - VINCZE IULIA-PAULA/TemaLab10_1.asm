bits 32
global start

extern exit,printf
import exit msvcrt.dll
import printf msvcrt.dll

segment data use32 class=data
    
    a dd 23
    b dw 0
    format db "%d mod %d = %d", 0
    
segment code use32 class=code
    start:
        ;Apeluri de functii sistem - VINCZE M. IULIA-PAULA
        ;7. Se dau doua numere naturale a si b (a: dword, b: word, definite in segmentul de date). Sa se calculeze a/b si sa se afiseze restul impartirii in urmatorul format: "<a> mod <b> = <rest>"
        ;Exemplu: pentru a = 23 si b = 5 se va afisa: "23 mod 5 = 3"
        ;Valorile vor fi afisate in format decimal (baza 10) cu semn.
        
        mov ax, [a]
        mov dx, [a+2]
        mov bx, [b]
        idiv bx
        
        mov ax, dx
        cwde
        push eax
        mov ax, bx
        cwde
        push eax
        push dword [a]
        push format
        call [printf]
        add esp, 4*4
        
        push    dword 0
        call    [exit]
