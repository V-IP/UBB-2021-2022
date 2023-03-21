#include "Colectie.h"
#include "IteratorColectie.h"
#include <iostream>

using namespace std;


//teta(1)
bool rel(TElem e1, TElem e2) {
	return e1 < e2;
}

//teta(1)
int Colectie::aloca() {
	int i = primLiber;
	primLiber = st[primLiber];
	return i;
}

//teta(1)
void Colectie::dealoca(int i) {
	if (st[pt[i]] == i)
		st[pt[i]] = -1;
	if (dr[pt[i]] == i)
		dr[pt[i]] = -1;
	st[i] = primLiber;
	pt[i] = -1;
	dr[i] = -1;
	fr[i] = 0;
	primLiber = i;
}

//teta(cp)
void Colectie::initSpatiuLiber() {
	for (int i = 0; i < cp - 1; i++) {
		pt[i] = -1;
		st[i] = i + 1;
		dr[i] = -1;
		fr[i] = 0;
	}
	st[cp - 1] = -1;
	primLiber = 0;
}

//teta(2*cp)
void Colectie::redim() {
	cp = 2 * cp;
	TElem* newElem = new TElem[cp];
	int* newPt = new int[cp];
	int* newSt = new int[cp];
	int* newDr = new int[cp];
	int* newFr = new int[cp];
	for (int i = 0; i < n - 1; i++) {
		newElem[i] = elem[i];
		newPt[i] = pt[i];
		newSt[i] = st[i];
		newDr[i] = dr[i];
		newFr[i] = fr[i];
	}
	delete[] elem;
	delete[] pt;
	delete[] st;
	delete[] dr;
	delete[] fr;
	elem = newElem;
	pt = newPt;
	st = newSt;
	dr = newDr;
	fr = newFr;
	for (int i = n - 1; i < cp - 1; i++) {
		pt[i] = -1;
		st[i] = i + 1;
		dr[i] = -1;
		fr[i] = 0;
	}
	st[cp - 1] = -1;
	primLiber = n - 1;
}


//teta(1) amortizat
int Colectie::creeazaNod(TElem e) {
	if (n == cp) {
		redim();
	}
	int i = aloca();
	elem[i] = e;
	fr[i]++;
	st[i] = -1;
	return i;
}

//teta(1) amortizat
void Colectie::reinitializeaza() {
	cp = 10;
	elem = new TElem[cp];
	pt = new int[cp];
	st = new int[cp];
	dr = new int[cp];
	fr = new int[cp];
	n = 0;
	initSpatiuLiber();
	rad = -1;
	primLiber = 0;
}


//teta(1) amortizat
Colectie::Colectie() {
	r = rel;
	reinitializeaza();
}


//O(h)
int Colectie::adauga_rec(int p, int parinte, TElem e) {
	if (p == -1) {
		p = creeazaNod(e);
		pt[p] = parinte;
	}
	else
		if (r(e, elem[p]))
			st[p] = adauga_rec(st[p], p, e);
		else
			dr[p] = adauga_rec(dr[p], p, e);
	return p;
}


//O(h)
void Colectie::adauga(TElem e) {
	n++;
	if (n == cp)
		redim();
	int i = cauta_rec(rad, e);
	if (i != -1) {
		fr[i]++;
		n--;
		return;
	}
	rad = adauga_rec(rad, -1, e);
}


//O(h)
int Colectie::minim(int p) {
	while (st[p] != -1) {
		p = st[p];
	}
	return p;
}


//O(h)
int Colectie::sterge_rec(int p, TElem e) {
	if (p == -1)
		return -1;
	if (r(e, elem[p])) {
		st[p] = sterge_rec(st[p], e);
		pt[st[p]] = p;
		return p;
	}
	else
		if (r(elem[p], e)) {
			dr[p] = sterge_rec(dr[p], e);
			pt[dr[p]] = p;
			return p;
		}
		else
			if (st[p] != -1 && dr[p] != -1) {
				int temp = minim(dr[p]);
				elem[p] = elem[temp];
				fr[p] = fr[temp];
				dr[p] = sterge_rec(dr[p], elem[p]);
				return p;
			}
			else {
				int temp = p;
				int repl;
				if (st[p] == -1)
					repl = dr[p];
				else
					repl = st[p];
				dealoca(temp);
				return repl;
			}
}


//O(h)
bool Colectie::sterge(TElem e) {
	if (dim() == 0)
		return false;
	int i = cauta_rec(rad, e);
	if (i == -1)
		return false;
	if (elem[rad] == e && fr[i] == 1 && n == 1) {
		reinitializeaza();
		return true;
	}
	fr[i]--;
	if (fr[i] == 0) {
		rad = sterge_rec(rad, e);
		pt[rad] = -1;
		n--;
	}
	return true;
}


//O(h)
int Colectie::cauta_rec(int p, TElem e) {
	if (p == -1 || elem[p] == e)
		return p;
	else
		if (r(e, elem[p]))
			cauta_rec(st[p], e);
		else
			cauta_rec(dr[p], e);
}


//O(h)
bool Colectie::cauta(TElem e) {
	return cauta_rec(rad, e) != -1;
}


//teta(1) amortizat
int Colectie::nrAparitii(TElem e) {
	if (dim() == 0)
		return 0;
	int poz = cauta_rec(rad, e);
	if (poz == -1)
		return 0;
	return fr[poz];
}


//teta(h)
int Colectie::dim_rec(int p) const {
	if (st[p] == -1 && dr[p] == -1)
		return fr[p];
	if (p == -1)
		return 0;
	return dim_rec(st[p]) + dim_rec(dr[p]) + fr[p];
}


//teta(n)
int Colectie::dim() const {
	if (n == 0)
		return 0;
	return dim_rec(rad);
}


//teta(1) amortizat
bool Colectie::vida() const {
	return n == 0;
}


//teta(1)
IteratorColectie Colectie::iterator() const {
	return IteratorColectie(*this);
}


//teta(1)
Colectie::~Colectie() {
	delete[] elem;
	delete[] st;
	delete[] dr;
	delete[] fr;
	rad = primLiber = -1;
	n = cp = 0;
}


//O(h)
bool Colectie::stergeAparitiiMultiple(int nr, TElem e) {
	if (nr < 0)
		return false;
	int i = cauta_rec(rad, e);
	if (i == -1)
		return false;
	if (nr > fr[i]) 
		return false;
	fr[i] -= nr;
	if (fr[i] == 0)
		sterge_rec(rad, e);
	return true;
}