#include "Multime.h"
#include "IteratorMultime.h"
#include <iostream>

using namespace std;

//o posibila relatie
//teta(1)
bool rel(TElem e1, TElem e2) {
	if (e1 < e2) {
		return true;
	}
	else {
		return false;
	}
}

//teta(1)
Nod::Nod(TElem elem, PNod urm, PNod prec) {
	this->elem = elem;
	this->urm = urm;
	this->prec = prec;
}

//teta(1)
TElem Nod::element() {
	return elem;
}

//teta(1)
PNod Nod::urmator() {
	return urm;
}

//teta(1)
PNod Nod::precedent() {
	return prec;
}

//teta(1)
Multime::Multime() {
	prim = nullptr;
	ultim = nullptr;
}

//O(len)
bool Multime::adauga(TElem elem) {
	int exists = cauta(elem);
	if (exists) {
		return false;
	}
	PNod q = new Nod(elem, nullptr, nullptr);
	if (prim == nullptr) {
		ultim = prim = q;
		return true;
	}
	if (rel(elem, prim->elem) == true) {
		q->urm = prim;
		prim->prec = q;
		prim = q;
		return true;
	}
	if (rel(ultim->elem, elem) == true) {
		ultim->urm = q;
		q->prec = ultim;
		ultim = q;
		return true;
	}
	PNod p = prim;
	while (rel(p->elem, elem))
		p = p->urm;
	p = p->prec;
	q->urm = p->urm;
	q->prec = p;
	p->urm->prec = q;
	p->urm = q;
	return true;
}

//O(len)
bool Multime::sterge(TElem elem) {
	int exists = cauta(elem);
	if (!exists)
		return false;
	if (prim->elem == elem) {
		if (ultim == prim) {
			prim = ultim = nullptr;
			return true;
		}
		PNod p = prim;
		prim = prim->urm;
		prim->prec = nullptr;
		delete p;
		return true;
	}
	if (ultim->elem == elem) {
		PNod p = ultim;
		ultim = ultim->prec;
		ultim->urm = nullptr;
		delete p;
		return true;
	}
	PNod p = prim;
	while (p->elem != elem) {
		p = p->urm;
	}
	p->prec->urm = p->urm;
	p->urm->prec = p->prec;
	delete p;
	return true;
}

//O(len)
bool Multime::cauta(TElem elem) const {
	if (vida() == true)
		return false;
	if (prim->elem == elem)
		return true;
	if (ultim->elem == elem)
		return true;
	PNod p = prim;
	while (p != nullptr && p->elem <= elem) {
		if (p->elem == elem)
			return true;
		p = p->urm;
	}
	return false;
}

//teta(len)
int Multime::dim() const {
	if (prim == nullptr)
		return 0;
	int ct = 0;
	PNod p = prim;
	while (p != ultim) {
		ct++;
		p = p->urm;
	}
	return ct + 1;
}

//teta(1)
bool Multime::vida() const {
	if (dim() == 0)
		return true;
	else
		return false;
}

//teta(1)
IteratorMultime Multime::iterator() const {
	return IteratorMultime(*this);
}

//teta(len)
Multime::~Multime() {
	while (prim != nullptr) {
		PNod p = prim;
		prim = prim->urm;
		delete p;
	}
}

//teta(lenA+lenB)
void Multime::reuniune(const Multime& b) {
	PNod p = prim;
	PNod q = b.prim;
	while (p != nullptr && q != nullptr) {
		while (rel(p->elem, q->elem) == true && rel(q->elem, p->urm->elem) == true) {
			PNod nou = new Nod(q->elem, nullptr, nullptr);
			nou->urm = p->urm;
			nou->prec = p;
			p->urm->prec = nou;
			p->urm = nou;
			q = q->urm;
		}
		p = p->urm;
	}
}





