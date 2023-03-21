#pragma once
#include "Colectie.h"

class Colectie;
typedef int TElem;

class IteratorColectie
{
	friend class Colectie;

private:
	//constructorul primeste o referinta catre Container
	//iteratorul va referi primul element din container
	IteratorColectie(const Colectie& c);

	//contine o referinta catre containerul pe care il itereaza
	const Colectie& col;
	int* vectorIterator;
	int poz;
	void inordine();

public:

	//reseteaza pozitia iteratorului la inceputul containerului
	void prim();

	//muta iteratorul in container
	// arunca exceptie daca iteratorul nu e valid
	void urmator();

	//verifica daca iteratorul e valid (indica un element al containerului)
	bool valid() const;

	//returneaza valoarea elementului din container referit de iterator
	//arunca exceptie daca iteratorul nu e valid
	TElem element() const;

	void afisare() {
		for (int p = 0; p < col.cp; p++)
			cout << "poz in vector= " << p << " elem=" << col.elem[p] << " fr=" << col.fr[p] << " parinte=" << col.pt[p] << " st=" << col.st[p] << " dr=" << col.dr[p] << endl;
	}
};

