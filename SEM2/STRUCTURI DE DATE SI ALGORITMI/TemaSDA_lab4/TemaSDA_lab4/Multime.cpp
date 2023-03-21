#include "Multime.h"
#include "IteratorMultime.h"
#include <iostream>

using namespace std;

//o posibila relatie
//teta(1)
bool rel(TElem e1, TElem e2) {
	if (e1 <= e2) {
		return true;
	}
	else {
		return false;
	}
}

//teta(1)
int Multime::aloca() {
	int i = primLiber;
	primLiber = urm[primLiber];
	return i;
}

//teta(1)
void Multime::dealoca(int i) {
	urm[i] = primLiber;
	primLiber = i;
}

//teta(cp)
void Multime::initSpatiuLiber() {
	for (int i = 0; i < cp - 1; i++)
		urm[i] = i + 1;
	urm[cp - 1] = -1;
	primLiber = 0;
}

//teta(2*cp)
void Multime::redim() {
	cp = 2 * cp;
	TElem* newElem = new TElem[cp];
	int* newUrm = new int[cp];
	for (int i = 0; i < n; i++) {
		newElem[i] = elem[i];
		newUrm[i] = urm[i];
	}
	delete[] elem;
	delete[] urm;
	elem = newElem;
	urm = newUrm;
	for (int i = n; i < cp - 1; i++)
		urm[i] = i + 1;
	urm[cp - 1] = -1;
	primLiber = n;
}

//teta(1) amortizat
int Multime::creeazaNod(TElem e) {
	if (n == cp) {
		redim();
	}
	int i = aloca();
	elem[i] = e;
	urm[i] = -1;
	return i;
}

//teta(cp)
void Multime::reinitializeaza() {
	cp = 10;
	elem = new TElem[cp];
	urm = new int[cp];
	n = 0;
	initSpatiuLiber();
	prim = -1;
	primLiber = 0;
}

//teta(cp)
Multime::Multime() {
	reinitializeaza();
}

//O(n)
bool Multime::adauga(TElem e) {
	int exista = cauta(e);
	if (exista) {
		return false;
	}
	int q = creeazaNod(e);
	if (prim == -1) {
		prim = q;
		n++;
		return true;
	}
	if (rel(e, elem[prim]) == true) {
		urm[q] = prim;
		prim = q;
		n++;
		return true;
	}
	int p = prim;
	while (urm[p] != -1 && rel(elem[urm[p]], e)) {
		p = urm[p];
	}
	urm[q] = urm[p];
	urm[p] = q;
	n++;
	return true;
}

//O(n)
bool Multime::sterge(TElem e) {
	int exista = cauta(e);
	if (!exista) {
		return false;
	}
	if (elem[prim] == e) {
		if (n == 1) {
			reinitializeaza();
			return true;
		}
		int remove = prim;
		prim = urm[prim];
		n--;
		return true;
	}
	int p;
	int q = prim;
	while (urm[q] != -1 && elem[q] != e) {
		p = q;
		q = urm[q];
	}
	urm[p] = urm[q];
	n--;
	return true;
}

//O(n)
bool Multime::cauta(TElem e) const {
	if (vida() == true)
		return false;
	if (elem[prim] == e) {
		return true;
	}
	int p = prim;
	while (p != -1 && rel(elem[p], e)) {
		if (elem[p] == e)
			return true;
		p = urm[p];
	}
	return false;
}

//teta(1)
int Multime::dim() const {
	return n;
}

//teta(1)
bool Multime::vida() const {
	if (n == 0)
		return true;
	else
		return false;
}

//teta(1)
IteratorMultime Multime::iterator() const {
	return IteratorMultime(*this);
}

//teta(n)
Multime::~Multime() {
	while (prim != -1) {
		prim = urm[prim];
	}
	n = 0;
	cp = 0;
}

//O(lenA+lenB)
int Multime::diferenta(const Multime& b) {
	int ct = 0;
	int p = prim;
	int q = b.prim;
	int ant;
	while (p != -1 && q != -1) {
		while (urm[p] != -1 && b.urm[q] != -1 && rel(elem[q], b.elem[urm[p]])) {
			ant = p;
			p = urm[p];
		}
		if (elem[p] == b.elem[q]) {
			ct++;
			if (urm[p] == -1) {
				urm[ant] = -1;
			}
			else
				urm[p] = urm[urm[p]];
		}
		q = b.urm[q];
	}
	n = n - ct;
	return ct;
}
