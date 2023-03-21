#include "validare.h"

int validates(Bill* bill)
/*
* Verifica daca datele pentru o factura sunt valide
*
* @param (Bill) bill: factura pe care o verificam
*
* @return (int): 1 daca factura este valida
*                0 daca daca nrAp <= 0
*                0 daca daca sum < 0
*                0 daca daca daca type != "apa" si type != "canal" si type != "incalzire" si type != "gaz"
*/
{
    if (bill->nrAp <= 0)
        return 0;
    if (bill->sum < 0)
        return 0;
    if (strcmp(bill->type, "apa") != 0 && strcmp(bill->type, "canal") != 0 && strcmp(bill->type, "incalzire") != 0 && strcmp(bill->type, "gaz") != 0)
        return 0;
    return 1;
}