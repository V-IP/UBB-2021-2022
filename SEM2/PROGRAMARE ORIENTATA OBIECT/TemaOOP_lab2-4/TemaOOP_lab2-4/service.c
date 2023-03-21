#include <assert.h>
#include <string.h>

#include "service.h"
#include "validare.h"

void add_srv(Costs* costs, int nrAp, int sum, char* type)
{
	Bill bill = create_bill(nrAp, sum, type);
	if (validates(&bill) == 1)
		add(costs, bill);
}

void delete_srv(Costs* costs, int nrAp, int sum, char* type)
{
	Bill bill = create_bill(nrAp, sum, type);
	if (validates(&bill) == 1)
		delete(costs, &bill);
	destroy_bill(&bill);
}
void modify_srv(Costs* costs, int nrAp, int sum, int new_sum, char* type, char* new_type)
{
	Bill bill1 = create_bill(nrAp, sum, type);
	Bill bill2 = create_bill(nrAp, new_sum, new_type);
	if (validates(&bill1) == 1 && validates(&bill2) == 1)
		modify(costs, &bill1, &bill2);
	destroy_bill(&bill1);
	destroy_bill(&bill2);
}
void filter_srv(Costs* costs, int ap_criteria, int sum_criteria, char* type_criteria)
{
	if(ap_criteria != -1 && ap_criteria <= 0)
	{
		printf("Criteriu invalid!\n");
		return;
	}
	if(sum_criteria != -1 && sum_criteria < 0)
	{
		printf("Criteriu invalid!\n");
		return;
	}
	if (strcmp(type_criteria, "-1") != 0 && strcmp(type_criteria, "apa") != 0 && strcmp(type_criteria, "canal") != 0 && strcmp(type_criteria, "incalzire") != 0 && strcmp(type_criteria, "gaz") != 0)
	{
		printf("Criteriu invalid!\n");
		return;
	}
	Costs f = filter(costs, ap_criteria, sum_criteria, type_criteria);
	print(&f);
	destroy_costs(&f);
}

void sort_srv(Costs* costs, int reversed, int (*cmp)())
{
	Costs f = sort(costs, reversed, cmp);
	print(&f);
	destroy_costs(&f);
}