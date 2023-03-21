#pragma once
#include <string>
#include "Obj.h"

using namespace std;
template <typename DynamicVector>

struct Nod {
	DynamicVector tenant;
	Nod* next;
	Nod(DynamicVector t) :tenant{ t }, next{ nullptr }{};
	Nod(DynamicVector t, Nod* next) :tenant{ t }, next{ next }{};
};

template <typename DynamicVector>
class MyListIterator;

template <typename DynamicVector>
class MyList {
	Nod<DynamicVector>* cp;

	//dealoca toate nodurile
	void elibereazaNoduri() noexcept;

	//face o copie a listei,parcurgand lista si creand noduri in care copiaza locatarii
	Nod<DynamicVector>* copiaza(Nod<DynamicVector>* current);

public:
	MyList() noexcept :cp{ nullptr } {};

	//constructor de copiere
	MyList(const MyList& ot);

	//operator de assignment
	void operator=(const MyList& ot);

	//destructor
	~MyList();

	//returneaza nr de elem
	size_t size()const noexcept;

	//adauga la inceput
	void addInceput(DynamicVector t);

	//adauga la sfarsit
	void push_back(DynamicVector t);

	//Returneaza primul element
	DynamicVector& first()const noexcept;

	//returneaza iterator pozitionat pe primul element
	MyListIterator<DynamicVector> begin()const noexcept;

	//returneaza iterator cu nodul nullptr(dupa ultimul element)
	MyListIterator<DynamicVector> end()const noexcept;

	//obtine elementul de pe pozitia poz
	DynamicVector& operator[](int poz) noexcept;


	//sterge un element de dupa un nod dat
	void stergeNod(Nod<DynamicVector>* predecesor)noexcept;

	//sterge locatarul dat
	void removeVal(DynamicVector t);
};

template <typename DynamicVector>
//iteratorul pt lista
class MyListIterator {
	//pozitia curenta-nullptr daca am ajuns la sf listei
	Nod<DynamicVector>* current;

public:
	MyListIterator(Nod<DynamicVector>* current) noexcept :current{ current } {}

	//operator !=
	bool operator!=(const MyListIterator& ot) noexcept;

	//operator ++ pt a trece la urmatorul element din lista
	void operator++() noexcept;

	//operator * pentru a returna elementul curent(locoarea)
	DynamicVector& operator*() noexcept;


};

template <typename DynamicVector>
//lista inlantuita
MyList<DynamicVector>::MyList(const MyList& ot) {
	//copiez din ot in obiectul curent
	cp = copiaza(ot.cp);
}

template <typename DynamicVector>
void MyList<DynamicVector>::operator=(const MyList& ot) {
	elibereazaNoduri();
	cp = copiaza(ot.cp);
}

template <typename DynamicVector>
MyList<DynamicVector>::~MyList() {
	elibereazaNoduri();
}

template <typename DynamicVector>
Nod<DynamicVector>* MyList<DynamicVector>::copiaza(Nod<DynamicVector>* current) {
	if (current == nullptr)
		return nullptr;

	auto nod = new Nod<DynamicVector>{ current->tenant };
	nod->next = copiaza(current->next);
	return nod;
}

template <typename DynamicVector>
void MyList<DynamicVector>::addInceput(DynamicVector t) {
	Nod<DynamicVector>* n = new Nod<DynamicVector>{ t,cp };
	cp = n;
}

template <typename DynamicVector>
void MyList<DynamicVector>::push_back(DynamicVector t) {
	auto nodCurent = cp;
	while (nodCurent != nullptr && nodCurent->next != nullptr) {
		nodCurent = nodCurent->next;
	}
	if (nodCurent == nullptr) {
		cp = new Nod<DynamicVector>{ t,nullptr };
	}
	else {
		nodCurent->next = new Nod<DynamicVector>{ t,nullptr };
	}

}
template <typename DynamicVector>
size_t MyList<DynamicVector>::size()const noexcept {
	auto nodCurent = cp;
	size_t lg = 0;
	while (nodCurent != nullptr) {
		lg++;
		nodCurent = nodCurent->next;
	}
	return lg;
}

template <typename DynamicVector>
DynamicVector& MyList<DynamicVector>::operator[](int poz) noexcept {
	auto nodCurent = cp;
	int lg = 0;
	while (lg < poz) {
		lg++;
		nodCurent = nodCurent->next;
	}
	return nodCurent->tenant;
}
template <typename DynamicVector>
DynamicVector& MyList<DynamicVector>::first()const noexcept {
	return cp->tenant;
}
template <typename DynamicVector>
void MyList<DynamicVector>::elibereazaNoduri() noexcept {
	auto nodCurent = cp;
	while (nodCurent != nullptr) {
		auto aux = nodCurent->next;
		delete nodCurent;
		nodCurent = aux;
	}
	cp = nullptr;
}


template <typename DynamicVector>
void MyList<DynamicVector>::stergeNod(Nod<DynamicVector>* predecesor) noexcept {
	auto* deSters = predecesor->next;
	predecesor->next = predecesor->next->next;
	delete deSters;
}

template <typename DynamicVector>
void MyList<DynamicVector>::removeVal(DynamicVector t) {
	if (cp->tenant == t) {
		auto* deleted = cp;
		cp = cp->next;
		delete deleted;
		return;
	}
	auto* elem = cp;
	while (elem->next != nullptr && elem->next->tenant != t) {
		elem = elem->next;
	}
	if (elem->next != nullptr)
		stergeNod(elem);
}

template <typename DynamicVector>
MyListIterator<DynamicVector> MyList<DynamicVector>::begin() const noexcept {
	return MyListIterator<DynamicVector>{ cp };
}
template <typename DynamicVector>
MyListIterator<DynamicVector> MyList<DynamicVector>::end() const noexcept {
	return MyListIterator<DynamicVector>{ nullptr };

}


//iterator
template <typename DynamicVector>
bool MyListIterator<DynamicVector>::operator!=(const MyListIterator& ot) noexcept {
	return current != ot.current;
}
template <typename DynamicVector>
void MyListIterator<DynamicVector>::operator++() noexcept {
	current = current->next;
}
template <typename DynamicVector>
DynamicVector& MyListIterator<DynamicVector>::operator*() noexcept {
	return current->tenant;
}