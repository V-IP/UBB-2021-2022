#include <stdio.h>
#include <string.h>

char prefix(char, int, char, char);

int main()
{
    /*
    7. Se dau trei siruri de caractere. Sa se afiseze cel mai lung prefix comun pentru fiecare din cele trei perechi de cate doua siruri ce se pot forma.
    Programare multi-modul (asm+c) - VINCZE IULIA-PAULA
    */
    char sir1[] = "impiedicat";
    char sir2[] = "imbatranit";
    char sir3[] = "impotrivit";
    char rez1[11] = "", rez2[11] = "", rez3[11] = "";
    int l1 = 11, l2 = 11;
    printf("Pentru sirul %s si %s prefixul este: ",sir1,sir2);
    prefix(sir1,l1,sir2,rez1);
    printf("%s", rez1);
    printf("\nPentru sirul %s si %s prefixul este: ",sir1,sir3);
    prefix(sir1,l1,sir3,rez2);
    printf("%s", rez2);
    printf("\nPentru sirul %s si %s prefixul este: ",sir2,sir3);
    prefix(sir2,l2,sir3,rez3);
    printf("%s", rez3);
    return 0;
}