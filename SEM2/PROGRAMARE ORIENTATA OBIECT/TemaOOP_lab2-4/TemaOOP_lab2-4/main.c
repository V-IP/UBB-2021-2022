#define _CRTDBG_MAP_ALLOC
#include <stdio.h>
#include <stdlib.h>
#include <crtdbg.h>

#include "teste.h"
#include "service.h"

/*
7. Administrator imobil

Creati o aplicatie care petmite gestiunea de cheltuieli lunare pentru apartamentele dintr-un bloc.

Fiecare cheltuiala are: numarul apartamentului, suma, tipul (apa, canal, incalzire, gaz).

Aplicatia permite:

a) Adaugarea de cheltuieli pentru un apartament

b) Modificarea unei cheltuieli existente (tipul, suma)

c) Stergere cheltuiala

d) Vizualizare lista de cheltuieli filtrat dupa o proprietate (suma, tipul,apartament)

e) Vizualizare lista de cheltuieli ordonat dupa suma sau tip (crescator/descrescator)
*/

void consola(Costs*);
void UI_print(Costs*);
void UI_add(Costs*);
void UI_modify(Costs*);
void UI_delete(Costs*);
void UI_filter(Costs*);
void UI_sort(Costs*);

int main()
{
	Costs costs = create_costs();
	run_all_tests();
	consola(&costs);
	destroy_costs(&costs);
	_CrtDumpMemoryLeaks();
	return 0;
}

void consola(Costs* costs)
{
	int opt, running = 1;
	while (running)
	{
		printf("    0. Exit\n    1. Adauga\n    2. Modifica\n    3. Sterge\n    4. Filtreaza\n    5. Sortare\n    6. Afisare\n");
		printf("Choose an option:");
		scanf_s("%d", &opt);
		switch (opt)
		{
		case 0:
			running = 0;
			break;
		case 1:
		{
			UI_add(costs);
			break;
		}
		case 2:
		{
			UI_modify(costs);
			break;
		}
		case 3:
		{
			UI_delete(costs);
			break;
		}
		case 4:
		{
			UI_filter(costs);
			break;
		}
		case 5:
		{
			UI_sort(costs);
			break;
		}
		case 6:
		{
			UI_print(costs);
			break;
		}
		default:
			printf("\nInvalid command!\n");
		}
	}
}

void UI_print(Costs* costs)
{
	print(costs);
}

void UI_add(Costs* costs)
{
	int nrAp, sum;
	char type[15];
	printf("Introduceti numarul apartamentului: ");
	scanf_s("%d", &nrAp);
	printf("Introduceti suma facturii: ");
	scanf_s("%d", &sum);
	printf("Introduceti tipul (apa, canal, incalzire, gaz): ");
	scanf_s("%s", &type, 15);
	add_srv(costs, nrAp, sum, type);
}

void UI_modify(Costs* costs)
{
	int nrAp, new_sum, sum;
	char type[15], new_type[15];
	printf("Introduceti numarul apartamentului: ");
	scanf_s("%d", &nrAp);
	printf("Introduceti suma facturii existente: ");
	scanf_s("%d", &sum);
	printf("Introduceti tipul existent (apa, canal, incalzire, gaz): ");
	scanf_s("%s", &type, 15);
	printf("Introduceti noua suma a facturii: ");
	scanf_s("%d", &new_sum);
	printf("Introduceti noul tip: ");
	scanf_s("%s", &new_type, 15);
	modify_srv(costs, nrAp, sum, new_sum, type, new_type);
}

void UI_delete(Costs* costs)
{
	int nrAp, sum;
	char type[15];
	printf("Introduceti numarul apartamentului: ");
	scanf_s("%d", &nrAp);
	printf("Introduceti suma facturii: ");
	scanf_s("%d", &sum);
	printf("Introduceti tipul (apa, canal, incalzire, gaz): ");
	scanf_s("%s", &type, 15);
	delete_srv(costs, nrAp, sum, type);
}

void UI_filter(Costs* costs)
{
	int opt, nrAp, sum;
	char type[15];

	printf("Introduceti criteriul dupa care vreti sa filtrati:\n");
	printf("1. Numarul aparatmentului\n2. Suma\n3. Tip\nChoose an option:");
	scanf_s("%d", &opt);
	if (opt == 1)
	{
		printf("Introduceti numarul apartamentului: ");
		scanf_s("%d", &nrAp);
		filter_srv(costs, nrAp, -1, "-1");
	}
	if (opt == 2)
	{
		printf("Introduceti suma facturii: ");
		scanf_s("%d", &sum);
		filter_srv(costs, -1, sum, "-1");
	}
	if (opt == 3)
	{
		printf("Introduceti tipul (apa, canal, incalzire, gaz): ");
		scanf_s("%s", &type, 15);
		filter_srv(costs, -1, -1, type);
	}
}

void UI_sort(Costs* costs)
{
	int opt, reversed;

	printf("Introduceti criteriul dupa care doriti sa sortati:\n");
	printf("1. Suma\n2. Tip\nChoose an option:");
	scanf_s("%d", &opt);
	printf("Crescator sau descrescator?\n0. Crescator\n1. Descrescator\nChoose an option:");
	scanf_s("%d", &reversed);
	if (opt == 1)
		sort_srv(costs, reversed, &cmp_sum);
	else
		sort_srv(costs, reversed, &cmp_type);
}