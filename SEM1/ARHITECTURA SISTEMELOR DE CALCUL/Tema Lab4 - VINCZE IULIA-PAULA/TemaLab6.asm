bits 32
global start

extern exit
import exit msvcrt.dll

segment data use32 class=data
    a dw 0111011101010111b ;30551
    b dw 1001101110111110b ;39870
    ce resd 1 ; c = 0000000001100101 1011 1010111 11111b = 65BAFFh
segment code use32 class=code
    start:
        ; Se dau doua cuvinte A si B. Sa se obtina dublucuvantul C:
        ; bitii 0-4 ai lui C au valoarea 1
        ; bitii 5-11 ai lui C coincid cu bitii 0-6 ai lui A
        ; bitii 16-31 ai lui C au valoarea 0000000001100101b
        ; bitii 12-15 ai lui C coincid cu bitii 8-11 ai lui B
        
        or dword [ce], 01Fh ; c = 000000000000000000000000000011111 = 1Fh
        
        mov ax, [a] ; ax = 0111011101010111b = 7757h
        shl ax, 5 ;ax = 1110101011100000b = EAE0h
        mov cx, 01111111b ;cx = 0000000001111111b = 7Fh
        shl cx, 5 ;cx = 0000111111100000b = FE0h
        and ax, cx ;ax = 0000101011100000b = AE0h
        or [ce], ax ; c = 00000000000000000000101011111111b = AFFh
        
        mov eax, 0 ;eax = 0b = 0h
        mov ax, 0000000001100101b ;eax = 00000000000000000000000001100101b = 65h
        shl eax, 16 ; eax = 00000000011001010000000000000000b = 650000h
        or [ce], eax ; c = 00000000011001010000101011111111b = 650AFFh
        
        mov ax, [b] ; ax = 1001101110111110b = 9BBEh
        shl ax, 4 ; ax = 1011101111100000b = BBE0h
        mov cx, 01111b ; cx = 0000000000001111b = Fh
        shl cx, 12 ; cx = 1111000000000000b = F000h
        and ax, cx ; ax = 1011000000000000b = 5800h
        or [ce], ax ; c = 00000000011001011011101011111111b = 65BAFFh
        
        push    dword 0
        call    [exit]
