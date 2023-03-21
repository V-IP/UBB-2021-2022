bits 32
global start

extern exit,printf,scanf
import exit msvcrt.dll
import printf msvcrt.dll
import scanf msvcrt.dll

segment data use32 class=data
    
    a dd 0
    b dd 0
    mesaja db "a=", 0
    mesajb db "b=", 0
    format db "%d", 0
    mesaj_MaiMic db "%d < %d", 0
    mesaj_MaiMare db "%d > %d", 0
    mesaj_Egal db "%d = %d", 0
    
segment code use32 class=code
    start:
        ;Apeluri de functii sistem - VINCZE IULIA-PAULA
        ;25. Sa se citeasca de la tastatura doua numere a si b (in baza 10) şi să se determine relaţia de ordine dintre ele (a < b, a = b sau a > b). Afisati rezultatul în următorul format: "<a> < <b>, <a> = <b> sau <a> > <b>".
        
        push dword mesaja
        call [printf]
        add esp, 4*1
        
        push dword a
        push dword format
        call [scanf]
        add esp, 4*2
        
        push dword mesajb
        call [printf]
        add esp, 4*1
        
        push dword b
        push dword format
        call [scanf]
        add esp, 4*2
        
        mov eax, [a]
        mov ecx, [b]
        
        cmp eax, ecx
        jle micSAUegal
        
        ;daca a > b
        push dword [b]
        push dword [a]
        push dword mesaj_MaiMare
        call [printf]
        add esp, 4*3
        
        micSAUegal:
        cmp eax, ecx
        jge egal
        
        ;daca a < b
        push dword [b]
        push dword [a]
        push dword mesaj_MaiMic
        call [printf]
        add esp, 4*3
        
        egal:
        cmp eax, ecx
        jl final
        cmp eax, ecx
        jg final
        
        ;daca a = b
        push dword [b]
        push dword [a]
        push dword mesaj_Egal
        call [printf]
        add esp, 4*3
        
        final:
        
        push    dword 0
        call    [exit]
