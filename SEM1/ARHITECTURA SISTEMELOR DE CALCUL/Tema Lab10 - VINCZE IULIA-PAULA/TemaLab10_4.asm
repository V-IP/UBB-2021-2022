bits 32
global start

extern exit, fopen, fprintf, fclose
import exit msvcrt.dll
import fopen msvcrt.dll
import fprintf msvcrt.dll
import fclose msvcrt.dll

segment data use32 class=data
    
    text db "Ana are 7 mere.", 0
    len equ $-text
    nume_fisier db "nume.txt", 0
    mod_acces db "w", 0
    format db "%c", 0
    fd db -1
    c db 0
    
segment code use32 class=code
    start:
        ;Operatii cu fisiere text - VINCZE IULIA PAULA
        ;25. Se dau un nume de fisier si un text (definite in segmentul de date). Textul contine litere mici, litere mari, cifre si caractere speciale. Sa se inlocuiasca toate spatiile din textul dat cu caracterul 'S'. Sa se creeze un fisier cu numele dat si sa se scrie textul obtinut prin inlocuire in fisier.
        
        ;fopen(nume_fisier, mod_acces)
        push dword mod_acces
        push dword nume_fisier
        call [fopen]
        add esp, 4*2
        
        mov [fd], eax
        cmp eax, 0
        je final
        
        mov esi, text
        mov ecx, len
        
        repeta:
            lodsb
            cmp al, 0
            je final_bucla
            mov ebx, 0
            mov bl, al
            cmp al, ' '
            jne urm
            
            mov bl, 'S'
            
            urm:
                ;fprintf(fd, format, caracter)
                push ebx
                push dword format
                push dword [fd]
                call [fprintf]
                add esp, 4*3
                
        jmp repeta
        
        final_bucla:
        
        ;fclose(fd)
        push dword [fd]
        call [fclose]
        add esp, 4
        
        final:
        
        push    dword 0
        call    [exit]
