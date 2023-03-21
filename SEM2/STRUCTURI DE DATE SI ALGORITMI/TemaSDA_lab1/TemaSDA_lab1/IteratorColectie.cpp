#include "IteratorColectie.h"
#include "Colectie.h"


//teta(1)
IteratorColectie::IteratorColectie(const Colectie& c) : col(c) {
	curent = 0;
}

//teta(1)
void IteratorColectie::prim() {
	curent = 0;
}

//teta(1)
void IteratorColectie::urmator() {
	curent++;
}

//teta(1)
bool IteratorColectie::valid() const {
	return curent < col.dim();
}

//teta(1)
TElem IteratorColectie::element() const {
	return col.elems[curent];
}