#include "teste.h"

void print_test()
/*
Test pt afisarea vectorului
*/
{
	Costs costs = create_costs();
	add_srv(&costs, 12, 200, "gaz");
	add_srv(&costs, 5, 500, "apa");
	add_srv(&costs, 12, 500, "apa");

	print(&costs);

	destroy_costs(&costs);
}

void eq_test()
/*
Test pt a verifica daca 2 facturi sunt identice
*/
{
	Bill bill1 = create_bill(12, 200, "gaz");
	Bill bill2 = create_bill(-12, 200, "apa");
	assert(eq(&bill1, &bill2) == 0);
	assert(eq(&bill1, &bill1) == 1);

	destroy_bill(&bill1);
	destroy_bill(&bill2);
}

void validates_test()
/*
Test pt validarea datelor
*/
{
	Bill bill1 = create_bill(12, 200, "gaz");
	assert(validates(&bill1) == 1);
	Bill bill2 = create_bill(-12, 200, "apa");
	assert(validates(&bill2) == 0);
	Bill bill3 = create_bill(12, -200, "apa");
	assert(validates(&bill3) == 0);
	Bill bill4 = create_bill(12, 200, "abc");
	assert(validates(&bill4) == 0);
	Bill bill5 = create_bill(-12, -200, "abc");
	assert(validates(&bill5) == 0);

	destroy_bill(&bill1);
	destroy_bill(&bill2);
	destroy_bill(&bill3);
	destroy_bill(&bill4);
	destroy_bill(&bill5);
}

void add_test()
/*
Test pt adaugarea in vector
*/
{
	Costs costs = create_costs();
	add_srv(&costs, 12, 200, "gaz");
	assert(costs.len == 1);
	assert(costs.elems[0].nrAp == 12);
	assert(costs.elems[0].sum == 200);
	assert(strcmp(costs.elems[0].type, "gaz") == 0);

	add_srv(&costs, 5, 500, "apa");

	assert(costs.len == 2);
	assert(costs.elems[1].nrAp == 5);
	assert(costs.elems[1].sum == 500);
	assert(strcmp(costs.elems[1].type, "apa") == 0);

	add_srv(&costs, 12, 500, "apa");

	assert(costs.len == 3);
	assert(costs.elems[2].nrAp == 12);
	assert(costs.elems[2].sum == 500);
	assert(strcmp(costs.elems[2].type, "apa") == 0);

	destroy_costs(&costs);
}

void search_test()
/*
Test pt cautarea unei facturi in vector
*/
{
	Costs costs = create_costs();
	Bill bill = create_bill(12,200,"gaz");
	add(&costs, bill);

	int poz = search(&costs, &bill);

	assert(costs.elems[poz].nrAp == 12);
	assert(costs.elems[poz].sum == 200);
	assert(strcmp(costs.elems[poz].type, "gaz") == 0);

	destroy_costs(&costs);
}

void modify_test()
/*
Test pt modificarea unei facturi
*/
{
	Costs costs = create_costs();
	Bill bill = create_bill(12,200,"gaz");
	add(&costs, bill);

	assert(costs.len == 1);
	assert(costs.elems[0].nrAp == 12);
	assert(costs.elems[0].sum == 200);
	assert(strcmp(costs.elems[0].type, "gaz") == 0);

	modify_srv(&costs, 12, 200, 500, "gaz", "apa");

	assert(costs.elems[0].nrAp == 12);
	assert(costs.elems[0].sum == 500);
	assert(strcmp(costs.elems[0].type, "apa") == 0);

	destroy_costs(&costs);
}

void copy_test()
/*
Test pt copierea informatiilor unei facturi
*/
{
	Bill bill1 = create_bill(12, 200, "gaz");
	Bill bill2 = create_bill(5, 500, "apa");

	copy(&bill1, &bill2);

	assert(bill1.nrAp == 5);
	assert(bill1.sum == 500);
	assert(strcmp(bill1.type, "apa") == 0);

	destroy_bill(&bill1);
	destroy_bill(&bill2);
}

void delete_test()
/*
Test pt stergerea unei facturi din vector
*/
{
	Costs costs = create_costs();
	Bill bill1 = create_bill(12, 200, "gaz");
	add(&costs, bill1);

	assert(costs.len == 1);

	Bill bill2 = create_bill(5, 500, "apa");
	add(&costs, bill2);

	assert(costs.len == 2);

	delete_srv(&costs, 12, 200, "gaz");

	assert(costs.elems[0].nrAp == 5);
	assert(costs.elems[0].sum == 500);
	assert(strcmp(costs.elems[0].type, "apa") == 0);

	destroy_bill(&bill1);
	destroy_costs(&costs);
}

void filter_test()
/*
Test pt filtrare pe criterii
*/
{
	Costs costs = create_costs();
	Bill bill1 = create_bill(12, 200, "gaz");
	add(&costs, bill1);
	Bill bill2 = create_bill(5, 500, "apa");
	add(&costs, bill2);
	Bill bill3 = create_bill(12, 500, "apa");
	add(&costs, bill3);

	filter_srv(&costs, -12, -1, "-1");
	filter_srv(&costs, -1, -500, "-1");
	filter_srv(&costs, -1, -1, "abc");

	filter_srv(&costs, 12, -1, "-1");
	filter_srv(&costs, -1, 500, "-1");
	filter_srv(&costs, -1, -1, "apa");

	Costs f1 = filter(&costs, 12, -1, "-1");
	assert(f1.len == 2);
	assert(f1.elems[0].sum == 200);
	assert(strcmp(f1.elems[0].type, "gaz") == 0);
	assert(f1.elems[1].sum == 500);
	assert(strcmp(f1.elems[1].type, "apa") == 0);

	Costs f2 = filter(&costs, -1, 500, "-1");
	assert(f2.len == 2);
	assert(f2.elems[0].nrAp == 5);
	assert(strcmp(f2.elems[0].type, "apa") == 0);
	assert(f2.elems[1].nrAp == 12);
	assert(strcmp(f2.elems[1].type, "apa") == 0);

	Costs f3 = filter(&costs, -1, -1, "apa");
	assert(f3.len == 2);
	assert(f3.elems[0].nrAp == 5);
	assert(f3.elems[1].nrAp == 12);

	destroy_costs(&f1);
	destroy_costs(&f2);
	destroy_costs(&f3);
	destroy_costs(&costs);
}

void sort_test()
{
	Costs costs = create_costs();
	Bill bill1 = create_bill(12, 400, "gaz");
	add(&costs, bill1);
	Bill bill2 = create_bill(5, 100, "apa");
	add(&costs, bill2);
	Bill bill3 = create_bill(23, 200, "incalzire");
	add(&costs, bill3);
	Bill bill4 = create_bill(50, 5, "canal");
	add(&costs, bill4);

	sort_srv(&costs, 0, &cmp_sum);
	sort_srv(&costs, 1, &cmp_sum);
	sort_srv(&costs, 0, &cmp_type);
	sort_srv(&costs, 1, &cmp_type);

	Costs f1 = sort(&costs, 0, &cmp_sum);
	assert(f1.len == 4);
	assert(f1.elems[0].sum == 5);
	assert(f1.elems[1].sum == 100);
	assert(f1.elems[2].sum == 200);
	assert(f1.elems[3].sum == 400);

	Costs f2 = sort(&costs, 1, &cmp_sum);
	assert(f2.len == 4);
	assert(f2.elems[0].sum == 400);
	assert(f2.elems[1].sum == 200);
	assert(f2.elems[2].sum == 100);
	assert(f2.elems[3].sum == 5);

	Costs f3 = sort(&costs, 0, &cmp_type);
	assert(f3.len == 4);
	assert(strcmp(f3.elems[0].type, "apa") == 0);
	assert(strcmp(f3.elems[1].type, "canal") == 0);
	assert(strcmp(f3.elems[2].type, "gaz") == 0);
	assert(strcmp(f3.elems[3].type, "incalzire") == 0);

	Costs f4 = sort(&costs, 1, &cmp_type);
	assert(f2.len == 4);
	assert(strcmp(f4.elems[0].type, "incalzire") == 0);
	assert(strcmp(f4.elems[1].type, "gaz") == 0);
	assert(strcmp(f4.elems[2].type, "canal") == 0);
	assert(strcmp(f4.elems[3].type, "apa") == 0);

	destroy_costs(&f1);
	destroy_costs(&f2);
	destroy_costs(&f3);
	destroy_costs(&f4);
	destroy_costs(&costs);
}

void run_all_tests()
{
	printf("START TESTE...\n");
	print_test();
	eq_test();
	validates_test();
	add_test();
	search_test();
	modify_test();
	copy_test();
	delete_test();
	filter_test();
	//sort_test();
	printf("STOP TESTE...\n");
}