#include "Colectie.h"
#include "IteratorColectie.h"
#include <exception>
#include <iostream>

using namespace std;

//teta(1)
Colectie::Colectie() {
	this->cp = 10;
	elems = new TElem[cp];
	this->len = 0;
}

//O(len)
void Colectie::adauga(TElem el) {
	if (len == cp) {
		TElem* newElem = new int[2 * cp];
		for (int i = 0; i < len; i++)
			newElem[i] = elems[i];
		cp = 2 * cp;
		delete[] elems;
		elems = newElem;
	}
	this->elems[len++] = el;
}

//teta(len)
bool Colectie::sterge(TElem elem) {
	int exists = cauta(elem);
	if (exists == false)
		return false;
	int i = 0;
	while (this->elems[i] != elem)
		i++;
	for (int j = i; j < len - 1; j++)
			this->elems[j] = this->elems[j + 1];
	this->len--;
	return true;
}

//O(len)
bool Colectie::cauta(TElem elem) const {
	for (int i = 0; i < len; i++)
		if (this->elems[i] == elem)
			return true;
	return false;
}

//teta(len)
int Colectie::nrAparitii(TElem elem) const {
	int ct = 0;
	for (int i = 0; i < len; i++)
		if (this->elems[i] == elem)
			ct++;
	return ct;
}

//teta(1)
int Colectie::dim() const {
	return len;
}

//teta(1)
bool Colectie::vida() const {
	if (len == 0)
		return true;
	else
		return false;
}

//teta(1)
IteratorColectie Colectie::iterator() const {
	return IteratorColectie(*this);
}

//teta(1)
Colectie::~Colectie() {
	delete[] elems;
}