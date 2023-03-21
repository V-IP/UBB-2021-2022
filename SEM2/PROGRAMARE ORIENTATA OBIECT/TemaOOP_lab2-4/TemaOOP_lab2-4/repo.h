#pragma once
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>

#include "entitati.h"


/*
* Afiseaza toate facturile din lista
*
* @param (Costs) costs: vectorul de cheltuieli
*/
void print(Costs* costs);


/*
* Adauga in vectorul de cheltuieli factura data
*
* @param (Costs) costs: vectorul de cheltuieli
* @param (Bill)  bill:  factura pe care dorim s-o introducem in lista
*
* post: factura este adaugata in lista de cheltuieli
*/
void add(Costs* costs, Bill bill);


/*
* Cauta o factura in vectorul de cheltuieli dupa numarul apartamentului, suma si tipul facturii
*
* @param (Costs) costs: lista de cheltuieli
* @param (int)   nrAp:  numarul apartamentului
* @param (int)   sum:   suma de pe factura
* @param (char)  type:  tipul facturii (apa, canal, incalzire, gaz)
*
* @return (int): indicele facturii care contine datele introduse
*/
int search(Costs* costs, Bill* bill);


/*
* Modifica o factura din vectorul de cheltuieli cu datele primei facturi cu cele de-al doilea facturi
*
* @param (Costs) costs: vectorul de cheltuieli
* @param (Bill)  bill1: factura care va fi modificata
* @param (Bill)  bill2: factura din care se extrag datele pentru modificare
*
* post: factura a fost modificata
*/
void modify(Costs* costs, Bill* bill1, Bill* bill2);


/*
Copiaza datele dintr-o factura in alta
Date de intrare: (Bill) bill     - factura care se va modifica
                 (Bill) new_bill - factura din care se extrag datele
Date de iesire: -
Postconditii: bill = new_bill
*/
void copy(Bill* bill, Bill* new_bill);


/*
* Sterge o factura din vectorul de cheltuieli cautata dupa datele acesteia
*
* @param (Costs) costs: lista de cheltuieli
* @param (Bill)  bill: factura care se doreste a fi stearsa
*
* post: factura a fost stearsa din vector
*/
void delete(Costs* costs, Bill* bill);


/*
* Filtreaza cheltuielile dupa o proprietate (suma, tipul,apartament)
*
* @param (Costs) costs: lista de cheltuieli
* @param (int)  ap_criteria:   daca !=0 se face filtrarea dupa apartament, 0  = daca nu se tine cont
* @param (int)  sum_criteria:  daca !=0 se face filtrarea dupa suma,       0  = daca nu se tine cont
* @param (char) type_criteria: daca !="0" se face filtrarea dupa tip,     "0" = daca nu se tine cont
*
* @return (Costs*): f - adresa unui vector nou cu elemsentele filtrate
*/
Costs filter(Costs* costs, int ap_criteria, int sum_criteria, char* type_criteria);


/*
* Sorteaza cheltuielile dupa o proprietate (suma, tipul,apartament)
*
* @param (Costs) costs: lista de cheltuieli
* @param (int) reversed: daca ==1 se face sortare descrescatoare, 0 = daca e crescator
*
* @return (Costs): f - un vector nou cu elementele sortate
*/
Costs sort(Costs* costs, int reversed, int (*cmp)());