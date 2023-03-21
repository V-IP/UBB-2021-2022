#pragma once
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <stdio.h>
#include <string.h>

typedef struct {
	int nrAp;
	int sum;
	char* type;
} Bill;

typedef struct {
	Bill* elems;
	int len;
	int capacity;
} Costs;

/*
* Creeaza o factura noua
*
* @param (int)  nrAp: numarul apartamentului
* @param (int)  sum:  suma facturii
* @param (char) type: tipul facturii
*
* @return (Bill): factura creata
*/
Bill create_bill(int nrAp, int sum, char* type);

/*
* Creeaza o lista goala
*
* @return (Costs): lista creata
*/
Costs create_costs();

/*
* Distruge o factura (Bill)
* 
* @param (Bill*) bill: adresa facturii de distrus
* 
* post: memoria alocata pentru factura (type) este eliberata
*/
void destroy_bill(Bill* bill);

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
Bill get(Costs* costs, int poz);

/*
* Distruge lista data si elemsentele sale
*
* @param (Costs*) costs: adresa listei de distrus
* 
* post: memoria alocata pentru lista si elemsentele sale este eliberata
*/
void destroy_costs(Costs* costs);

/*
* Verifica daca 2 facturi sunt identice
* 
* @param (Bill*) bill1: adresa primei facturi
* @param (Bill*) bill2: adresa celei de a doua facturi
* 
* @return (int): 1 daca sunt egale, 0 altfel
*/
int eq(Bill* bill1, Bill* bill2);

int cmp_sum(Bill* bill1, Bill* bill2);

int cmp_type(Bill* bill1, Bill* bill2);