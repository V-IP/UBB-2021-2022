bits 32
global _prefix
    
segment data use32 class=data

    sir times 20 db 0
    
segment code use32 class=code public
    _prefix:
        ;7. Se dau trei siruri de caractere. Sa se afiseze cel mai lung prefix comun pentru fiecare din cele trei perechi de cate doua siruri ce se pot forma.
        ;Programare multi-modul (asm+c) - VINCZE IULIA-PAULA
        
        ;[ESP]    <- EBP
        ;[ESP+4]  <- adresa de revenire
        ;[ESP+8]  <- adresa primului sir
        ;[ESP+12] <- lungimea primului sir
        ;[ESP+16] <- adresa celui de-al doilea sir
        ;[ESP+20] <- adresa rezultatului
        
        push ebp
        mov ebp, esp
        
        mov esi, [EBP+8]
        cld
        mov edi, [EBP+20]
        mov ecx, [EBP+12]
        jecxz final
        
        mov ebx, [EBP+16]
        
        repeta:
            lodsb ; al=caracter din primul sir
            mov ah, [ebx] ; ah=caracter din al doilea sir
            cmp al, ah
            jne final
            stosb
            inc ebx
        
        loop repeta
        
        final:
        mov esp, ebp
        pop ebp
        ret