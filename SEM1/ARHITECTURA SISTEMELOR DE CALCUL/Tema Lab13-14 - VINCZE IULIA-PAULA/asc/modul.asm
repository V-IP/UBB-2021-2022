bits 32
global prefix
    
segment code use32 class=code public
    prefix:
        ;7. Se dau trei siruri de caractere. Sa se afiseze cel mai lung prefix comun pentru fiecare din cele trei perechi de cate doua siruri ce se pot forma.
        ;Programare multi-modul (asm+asm) - VINCZE IULIA-PAULA
        
        ;[ESP]    <- adresa de revenire
        ;[ESP+4]  <- adresa primului sir
        ;[ESP+8]  <- lungimea lui sir1
        ;[ESP+12] <- adresa celui de-al doilea sir
        ;[ESP+16] <- adresa rezultatului
        
        mov esi, [ESP+4]
        cld
        mov edi, [ESP+16]
        mov ecx, [ESP+8]
        jecxz final
        
        mov ebx, [ESP+4]
        mov edx, [ESP+12]
        
        repeta:
            mov al, [ebx]
            mov ah, [edx]
            cmp al, ah ;cmpsb
            jne final
            stosb
            inc ebx
            inc edx
        
        loop repeta
        
        final:
        ret