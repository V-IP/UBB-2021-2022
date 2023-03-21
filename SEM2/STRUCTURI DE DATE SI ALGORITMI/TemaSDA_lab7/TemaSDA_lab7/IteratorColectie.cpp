#include <stack>
#include <iostream>
#include "IteratorColectie.h"
#include "Colectie.h"

using namespace std;


void IteratorColectie::inordine() {
	stack<int> stiva;
	int p = col.rad;
	while (!stiva.empty() || p != -1) {
		while (p != -1) {
			stiva.push(p);
			p = col.st[p];
		}
		p = stiva.top();
		stiva.pop();
		int ct = col.fr[p];
		while (ct) {
			vectorIterator[poz++] = p;
			ct--;
		}
		p = col.dr[p];
	}
}

IteratorColectie::IteratorColectie(const Colectie& c) : col(c) {
	vectorIterator = new int[col.cp];
	poz = 0;
	inordine();
}

TElem IteratorColectie::element() const {
	return col.elem[vectorIterator[poz-1]];
}

bool IteratorColectie::valid() const {
	if (col.dim() == 0)
		return false;
	return poz <= col.dim();
}

void IteratorColectie::urmator() {
	poz++;
}

void IteratorColectie::prim() {
	poz = 0;
}