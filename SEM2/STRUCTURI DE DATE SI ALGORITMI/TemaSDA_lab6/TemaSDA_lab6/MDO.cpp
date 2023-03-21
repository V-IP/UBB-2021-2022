#include "IteratorMDO.h"
#include "MDO.h"
#include <iostream>
#include <vector>
#include <math.h>
#include <exception>

using namespace std;

bool r(TCheie cheie1, TCheie cheie2) {
	if (cheie1 <= cheie2) {
		return true;
	}
	else {
		return false;
	}
}

//teta(1)
Nod::Nod(TElem e, PNod urm) {
	this->e = e;
	this->urm = urm;
}

//teta(1)
TElem Nod::element() {
	return e;
}

//teta(1)
PNod Nod::urmator() {
	return urm;
}

//teta(1)
int MDO::dispersie(TCheie c) {
	return abs(c) % m;
}

//teta(m)
MDO::MDO(Relatie r) {
	l = new PNod[MAX];
	m = MAX;
	rel = r;
	for (int i = 0; i < m; i++)
		l[i] = nullptr;
}

//O(n)
//n = lungimea maxima a listelor dintr-o pozitie
void MDO::adauga(TCheie c, TValoare v) {
	int i = dispersie(c);
	TElem e(c, v);
	PNod p = new Nod(e, nullptr);
	PNod prim = l[i];
	if (prim == nullptr) {
		p->urm = l[i];
		l[i] = p;
		return;
	}
	if (rel(c,prim->e.first)) {
		p->urm = l[i];
		l[i] = p;
		return;
	}
	while (prim->urm != nullptr && !rel(c, prim->urm->e.first))
		prim = prim->urm;
	p->urm = prim->urm;
	prim->urm = p;
}

//teta(n)
//n = lungimea listei de pe pozitia de dispersie "i"
vector<TValoare> MDO::cauta(TCheie c) {
	vector<TValoare> elem;
	int i = dispersie(c);
	PNod p = l[i];
	while (p != nullptr) {
		if (p->e.first == c) {
			elem.push_back(p->e.second);
		}
		p = p->urm;
	}
	return elem;
}


//O(len)
//n = lungimea listei de pe pozitia de dispersie "i"
bool MDO::sterge(TCheie c, TValoare v) {
	int i = dispersie(c);
	PNod p = l[i];
	if (p == nullptr)
		return false;
	if (p->urm == nullptr && p->e.second == v) {
		l[i] = nullptr;
		delete p;
		return true;
	}
	while (p->urm != nullptr) {
		if (p->urm->e.second == v) {
			p->urm = p->urm->urm;
			return true;
		}
		p = p->urm;
	}
	return false;
}

//teta(max{n,m})
int MDO::dim() const {
	int ct = 0;
	for (int i = 0; i < m; i++) {
		PNod p = l[i];
		while (p != nullptr) {
			ct++;
			p = p->urm;
		}
	}
	return ct;
}

//teta(1)
bool MDO::vid() const {
	if (dim() == 0)
		return true;
	return false;
}


//teta(1)
IteratorMDO MDO::iterator() const {
	return IteratorMDO(*this);
}


//teta(max{n,m})
MDO::~MDO() {
	for (int i = 0; i < m; i++) {
		while (l[i] != nullptr) {
			PNod p = l[i];
			l[i] = l[i]->urm;
			delete p;
		}
	}
}


//teta(max{n,m})
vector <int> contor(100001);
TValoare MDO::ceaMaiFrecventaValoare() const {
	if (vid() == true) {
		return NULL;
	}
	int maxim=0;
	TValoare valMax = NULL;
	for (int i = 0; i < m; i++) {
		PNod p = l[i];
		while (p != nullptr) {
			contor[p->e.second]++;
			if (contor[p->e.second] > maxim) {
				maxim = contor[p->e.second];
				valMax = p->e.second;
			}
			p = p->urm;
		}
	}
	return valMax;
}