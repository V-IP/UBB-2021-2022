bits 32
global start

extern exit,fopen,fread,fclose,printf
import exit msvcrt.dll
import fopen msvcrt.dll
import fread msvcrt.dll
import fclose msvcrt.dll
import printf msvcrt.dll

segment data use32 class=data
    
    ; in fisier este sirul: acdaace
    pozitie_litera db 0
    aparitie db 0
    x dd 0
    fd dd -1
    nume_fisier db "fisier.txt", 0
    mod_acces db "r", 0
    mesaj db "Litera cu cea mai mare frecventa este %c si apare de %d ori", 0
    frecventa times 26 db 0
    
segment code use32 class=code
    start:
        ;Operatii cu fisiere text - VINCZE M. IULIA-PAULA
        ;7. Se da un fisier text. Sa se citeasca continutul fisierului, sa se determine litera mica (lowercase) cu cea mai mare frecventa si sa se afiseze acea litera, impreuna cu frecventa acesteia. Numele fisierului text este definit in segmentul de date.
        
        ; atentie la fisier!!
        
        ;fopen(mod_acces,nume_fisier)
        push dword mod_acces
        push dword nume_fisier
        call [fopen]
        add esp, 4*2
        
        mov [fd], eax ;salvam valoarea returnata de fopen in variabila fd
        cmp eax, 0
        je eroare ;verificam daca functia fopen a creat cu succes fisierul (daca EAX != 0)
        
        bucla:
            ;fread(x, 1, 1, fd)
            push dword [fd]
            push dword 1
            push dword 1
            push dword x
            call [fread]
            add esp, 4*4
            
            cmp eax, 0
            je final_bucla
            
            mov eax, 0
            mov eax, [x]
            sub eax, 'a'
            mov ebx, [frecventa+eax]
            add ebx, 1
            mov [frecventa+eax], bl
            
            jmp bucla
            
        final_bucla:
            ;fclose(fd)
            push dword [fd]
            call [fclose]
            add esp, 4
            
            ;caut maximul din sirul de frecventa
            mov esi, frecventa
            cld
            mov ecx, 26
            mov ebx, 0
            
            mov dword [x], 0
            repeta:
                mov eax, 0
                lodsb
                cmp ax, [aparitie] ;compar val din vector cu maximul
                jbe urm ;daca nu e mai mare, trec peste
                mov [aparitie], al ;salvez nr de aparitii
                mov ebx, ecx ;salvez in ebx pozitia din sir
                
                urm:
                    loop repeta
        
        mov eax, [frecventa+ebx]
        add eax, 'a' ;din pozitie, transform in litera corespunzatoare
        
        ;printf(mesaj,caracter,nr aparitii)
        push dword [aparitie]
        push eax
        push dword mesaj
        call [printf]
        add esp, 4*3
            
        eroare:
            push dword 0
            call [exit]