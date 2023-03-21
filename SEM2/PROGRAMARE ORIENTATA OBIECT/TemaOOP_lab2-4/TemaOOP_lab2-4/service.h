#include <stdlib.h>
#include <crtdbg.h>
#include <stdio.h>
#include <string.h>

#include "repo.h"


void add_srv(Costs* costs, int nrAp, int sum, char* type);

void delete_srv(Costs* costs, int nrAp, int sum, char* type);

void modify_srv(Costs* costs, int nrAp, int sum, int new_sum, char* type, char* new_type);

void filter_srv(Costs* costs, int ap_criteria, int sum_criteria, char* type_criteria);

void sort_srv(Costs* costs, int reversed, int (*cmp)());