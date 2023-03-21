#include "IteratorMultime.h"
#include "Multime.h"



//teta(1)
IteratorMultime::IteratorMultime(const Multime& m) : mult(m) {
	curent = m.prim;
}

//teta(1)
TElem IteratorMultime::element() const {
	return mult.elem[curent];
}

//teta(1)
bool IteratorMultime::valid() const {
	return curent != -1;
}

//teta(1)
void IteratorMultime::urmator() {
	curent = mult.urm[curent];
}

//teta(1)
void IteratorMultime::prim() {
	curent = mult.prim;
}

