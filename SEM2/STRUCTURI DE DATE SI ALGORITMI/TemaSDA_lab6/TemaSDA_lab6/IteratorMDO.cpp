#include "IteratorMDO.h"
#include "MDO.h"
#include <iostream>


//teta(n)
void IteratorMDO::interclasare() {
	PNod curentL1, curentL2;
	for (int i = 0; i < dict.m; i++) {
		PNod primLocal = nullptr, ultimLocal = nullptr;
		curentL1 = primLR;
		curentL2 = dict.l[i];
		while (curentL1 != nullptr && curentL2 != nullptr) {
			PNod p = new Nod(TElem(NULL, NULL), nullptr);
			if (dict.rel(curentL1->e.first, curentL2->e.first)) {
				TElem el(curentL1->e.first, curentL1->e.second);
				p->e = curentL1->e;
				curentL1 = curentL1->urm;
			}
			else {
				TElem el(curentL2->e.first, curentL2->e.second);
				p->e = curentL2->e;
				curentL2 = curentL2->urm;
			}
			if (primLocal == nullptr) {
				primLocal = p;
			}
			else {
				ultimLocal->urm = p;
			}
			ultimLocal = p;
		}
		curent = curentL1;
		if (curentL1 == nullptr) {
			curent = curentL2;
		}
		while (curent != nullptr) {
			PNod p = new Nod(curent->e, nullptr);
			curent = curent->urm;
			if (primLocal == nullptr) {
				primLocal = p;
			}
			else {
				ultimLocal->urm = p;
			}
			ultimLocal = p;
		}
		while (primLR != nullptr) {
			PNod sters = primLR;
			primLR = primLR->urm;
			delete sters;
		}
		primLR = primLocal;
	}
}

IteratorMDO::IteratorMDO(const MDO& d) : dict(d) {
	primLR = nullptr;
	ultimLR = nullptr;
	curent = nullptr;
	interclasare();
}

void IteratorMDO::prim() {
	curent = primLR;
}

void IteratorMDO::urmator() {
	curent = curent->urm;
}

bool IteratorMDO::valid() const {
	return curent != nullptr;
}

TElem IteratorMDO::element() const {
	return pair <TCheie, TValoare>(curent->e.first, curent->e.second);
}