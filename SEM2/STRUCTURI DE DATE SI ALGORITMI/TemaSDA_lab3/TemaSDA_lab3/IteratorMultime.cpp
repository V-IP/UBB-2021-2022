#include "IteratorMultime.h"
#include "Multime.h"

//teta(1)
IteratorMultime::IteratorMultime(const Multime& m) : mult(m) {
	curent = m.prim;
}

//teta(1)
TElem IteratorMultime::element() const {
	return curent->element();
}

//teta(1)
bool IteratorMultime::valid() const {
	return curent != nullptr;
}

//teta(1)
void IteratorMultime::urmator() {
	curent = curent->urmator();
}

//teta(1)
void IteratorMultime::prim() {
	curent = mult.prim;
}

