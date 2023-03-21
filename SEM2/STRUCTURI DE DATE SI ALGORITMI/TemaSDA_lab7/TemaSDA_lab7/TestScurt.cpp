#include "TestScurt.h"
#include "Colectie.h"
#include "IteratorColectie.h"
#include <assert.h>

void testFunctionalitateExtra() {
	Colectie c;
	c.adauga(5);
	c.adauga(6);
	c.adauga(0);
	c.adauga(5);
	c.adauga(10);
	c.adauga(8);

	assert(c.dim() == 6);
	assert(c.nrAparitii(5) == 2);

	assert(c.stergeAparitiiMultiple(-5, 5) == false);
	assert(c.stergeAparitiiMultiple(7, 5) == false);
	assert(c.stergeAparitiiMultiple(2, 5) == true);
	assert(c.dim() == 4);
	assert(c.cauta(5) == false);

	c.adauga(5);
	c.adauga(5);
	assert(c.dim() == 6);
	assert(c.nrAparitii(5) == 2);
	assert(c.stergeAparitiiMultiple(1, 5) == true);
	assert(c.dim() == 5);
	assert(c.nrAparitii(5) == 1);
}

void testAll() {
	Colectie c;
	c.adauga(5);
	c.adauga(6);
	c.adauga(0);
	c.adauga(5);
	c.adauga(10);
	c.adauga(8);

	assert(c.dim() == 6);
	assert(c.nrAparitii(5) == 2);

	assert(c.sterge(5) == true);
	assert(c.dim() == 5);

	assert(c.cauta(6) == true);
	assert(c.vida() == false);

	IteratorColectie ic = c.iterator();
	assert(ic.valid() == true);
	while (ic.valid()) {
		ic.element();
		ic.urmator();
	}
	assert(ic.valid() == false);
	ic.prim();
	assert(ic.valid() == true);

}
