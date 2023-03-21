#include "repo.h"

void print(Costs* costs)
/*
* Afiseaza toate facturile din lista
* 
* @param (Costs) costs: vectorul de cheltuieli
*/
{
    printf("\n\nCheltuielile sunt:\nNumar apartament, suma, tip\n\n");
    for (int i = 0; i < costs->len; i++)
        printf("%d, %d, %s\n", costs->elems[i].nrAp, costs->elems[i].sum, costs->elems[i].type);
    printf("\n");
}

void add(Costs* costs, Bill bill)
/*
* Adauga in vectorul de cheltuieli factura data
* 
* @param (Costs) costs: vectorul de cheltuieli
* @param (Bill)  bill:  factura pe care dorim s-o introducem in lista
* 
* post: factura este adaugata in lista de cheltuieli
*/
{
    if (costs->len == costs->capacity) {
        int newcapacity = costs->capacity * 2;
        Bill* aux_elems = malloc(sizeof(Bill) * newcapacity);
        for (int i = 0; i < costs->len; i++) {
            aux_elems[i] = costs->elems[i];
        }
        free(costs->elems);
        costs->elems = aux_elems;
        costs->capacity = newcapacity;
    }
    costs->elems[costs->len] = bill;
    costs->len++;
}

int search(Costs* costs, Bill* bill)
/*
* Cauta o factura in vectorul de cheltuieli dupa numarul apartamentului, suma si tipul facturii
* 
* @param (Costs) costs: lista de cheltuieli
* @param (int)   nrAp:  numarul apartamentului
* @param (int)   sum:   suma de pe factura
* @param (char)  type:  tipul facturii (apa, canal, incalzire, gaz)
* 
* @return (int): indicele facturii care contine datele introduse
*                -1 daca elemsentul nu exista
*/
{
    for (int i = 0; i < costs->len; i++)
        if (eq(&costs->elems[i], bill) == 1)
            return i;
}

void modify(Costs* costs, Bill* bill1, Bill* bill2)
/*
* Modifica o factura din vectorul de cheltuieli cu datele primei facturi cu cele de-al doilea facturi
* 
* @param (Costs) costs: vectorul de cheltuieli
* @param (Bill)  bill1: factura care va fi modificata
* @param (Bill)  bill2: factura din care se extrag datele pentru modificare
* 
* post: factura a fost modificata
*/
{
    int poz = search(costs, bill1);
    copy(&costs->elems[poz], bill2);
}

void copy(Bill* bill, Bill* new_bill)
/*
Copiaza datele dintr-o factura in alta
Date de intrare: (Bill) bill     - factura care se va modifica
                 (Bill) new_bill - factura din care se extrag datele
Date de iesire: -
Postconditii: bill = new_bill
*/
{
    bill->nrAp = new_bill->nrAp;
    bill->sum = new_bill->sum;
    bill->type = realloc(bill->type, strlen(new_bill->type) + 1);
    strcpy_s(bill->type, strlen(new_bill->type) + 1, new_bill->type);
}

void delete(Costs* costs, Bill* bill)
/*
* Sterge o factura din vectorul de cheltuieli cautata dupa datele acesteia
* 
* @param (Costs) costs: lista de cheltuieli
* @param (Bill)  bill: factura care se doreste a fi stearsa
* 
* post: factura a fost stearsa din vector
*/
{
    int poz = search(costs, bill);
    for (int i = poz; i < costs->len - 1; i++) {
        costs->elems[i] = costs->elems[i + 1];
    }
    costs->len--;
}

Costs filter(Costs* costs, int ap_criteria, int sum_criteria, char* type_criteria)
/*
* Filtreaza cheltuielile dupa o proprietate (suma, tipul,apartament)
* 
* @param (int)  ap_criteria:   daca !=-1   se face filtrarea dupa apartament, -1  = daca nu se tine cont
* @param (int)  sum_criteria:  daca !=-1   se face filtrarea dupa suma,       -1  = daca nu se tine cont
* @param (char) type_criteria: daca !="-1" se face filtrarea dupa tip  ,     "-1" = daca nu se tine cont
* 
* @return (Costs*): f - adresa unui vector nou cu elemsentele filtrate
*/
{
    Costs f = create_costs();
    if (sum_criteria != -1)
        for (int i = 0; i < costs->len; i++)
            if (costs->elems[i].sum == sum_criteria)
            {
                Bill bill = create_bill(costs->elems[i].nrAp, costs->elems[i].sum, costs->elems[i].type);
                add(&f, bill);
            }
    if (ap_criteria != -1)
        for (int i = 0; i < costs->len; i++)
            if (costs->elems[i].nrAp == ap_criteria)
            {
                Bill bill = create_bill(costs->elems[i].nrAp, costs->elems[i].sum, costs->elems[i].type);
                add(&f, bill);
            }
    if (type_criteria != "-1")
        for (int i = 0; i < costs->len; i++)
            if (strcmp(costs->elems[i].type, type_criteria) == 0)
            {
                Bill bill = create_bill(costs->elems[i].nrAp, costs->elems[i].sum, costs->elems[i].type);
                add(&f, bill);
            }
    return f;
}

Costs sort(Costs* costs, int reversed, int(*cmp)())
{
    Costs f = create_costs();
    for (int i = 0; i < costs->len; i++)
    {
        Bill bill = create_bill(costs->elems[i].nrAp, costs->elems[i].sum, costs->elems[i].type);
        add(&f, bill);
    }
    for (int i = 0; i < f.len - 1; i++)
        for (int j = i + 1; j < f.len; j++)
        {
            if (reversed == 0 && cmp(f.elems[i], f.elems[j]) > 0)
            {
                Bill bill = f.elems[i];
                copy(&f.elems[i], &f.elems[j]);
                copy(&f.elems[j], &bill);
            }
            if (reversed == 1 && cmp(f.elems[i], f.elems[j]) < 0)
            {
                Bill bill = f.elems[i];
                copy(&f.elems[i], &f.elems[j]);
                copy(&f.elems[j], &bill);
            }
        }
    return f;
}