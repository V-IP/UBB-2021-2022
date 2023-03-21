#include <malloc.h>

#include "entitati.h"

Bill create_bill(int nrAp, int sum, char* type)
/*
* Creeaza o factura cu datele introduse: numarul apartamentului, suma facturii si tipul acesteia (apa, canal, incalzire, gaz)
*
* @param (int)  nrAp: numarul apartamentului
* @param (int)  sum:  suma de pe factura
* @param (char) type: tipul facturii
*
* @return (Bill): bill - factura creata
*
* post: bill este un obiect care contine datele introduse de utilizator
*/
{
    Bill bill;
    bill.nrAp = nrAp;
    bill.sum = sum;
    bill.type = malloc(sizeof(char) * (strlen(type) + 1));
    strcpy_s(bill.type, strlen(type) + 1, type);
    return bill;
}

Costs create_costs()
/*
* Creeaza un vector cu lungime 0, fara elemsente.
* 
* @return (Costs): costs - lista creata
* 
* post: costs are lungimea 0 si nu contine niciun elemsent
*/
{
    Costs costs;
    costs.capacity = 2;
    costs.len = 0;
    costs.elems = malloc(sizeof(Bill) * costs.capacity);
    return costs;
}

/*
* Distruge o factura (Bill)
*
* @param (Bill*) bill: adresa facturii de distrus
*
* post: memoria alocata pentru factura (type) este eliberata
*/
void destroy_bill(Bill* bill)
{
    bill->nrAp = -1;
    bill->sum = -1;
    free(bill->type);
}

/*
* Returneaza elemsentul din lista de pe pozitia data
*
* pre: -1<poz<len
*
* @param (Costs*) costs: adresa listei in care cautam
* @param (int)    poz:   indicele elemsentului de care avem nevoie din lista
*
* @return (Bill): factura de pe pozitia poz
*/
Bill get(Costs* costs, int poz)
{
    return costs->elems[poz];
}

/*
* Distruge lista data si elemsentele sale
*
* @param (Costs*) costs: adresa listei de distrus
*
* post: memoria alocata pentru lista si elemsentele sale este eliberata
*/
void destroy_costs(Costs* costs)
{
    for (int i = 0; i < costs->len; i++) {
        Bill bill = get(costs, i);
        destroy_bill(&bill);
    }
    costs->len = 0;
    free(costs->elems);
}

/*
* Verifica daca 2 facturi sunt identice
*
* @param (Bill*) bill1: adresa primei facturi
* @param (Bill*) bill2: adresa celei de a doua facturi
*
* @return (int): 1 daca sunt egale, 0 altfel
*/
int eq(Bill* bill1, Bill* bill2)
{
    if (bill1->nrAp == bill2->nrAp && bill1->sum == bill2->sum && strcmp(bill1->type, bill2->type) == 0)
        return 1;
    return 0;
}

/*
* Functie de comparare pentru suma a 2 elemente
* 
* @param (Bill*) bill1: adresa primei facturi
* @param (Bill*) bill2: adresa celei de a doua facturi
* 
* @return (int): 0 daca sunt egale
                 1 daca bill1 > bill2
                 -1 altfel
*/

int cmp_sum(Bill* bill1, Bill* bill2)
{
    if (bill1->sum == bill2->sum)
        return 0;
    if (bill1->sum > bill2->sum)
        return 1;
    return -1;
}

/*
* Functie de comparare pentru tipul a 2 elemente
*
* @param (Bill*) bill1: adresa primei facturi
* @param (Bill*) bill2: adresa celei de a doua facturi
*
* @return (int): 0 daca sunt egale
                 1 daca bill1 > bill2
                 -1 altfel
*/

int cmp_type(Bill* bill1, Bill* bill2)
{
    if (strcmp(bill1->type, bill2->type) == 0)
        return 0;
    if (strcmp(bill1->type, bill2->type) > 0)
        return 1;
    return -1;
}