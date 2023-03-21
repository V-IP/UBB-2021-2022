﻿#pragma once

#include <iostream>

using namespace std;

typedef int TElem;

typedef bool(*Relatie)(TElem, TElem);

//in implementarea operatiilor se va folosi functia (relatia) rel (de ex, pentru <=)
// va fi declarata in .h si implementata in .cpp ca functie externa colectiei
bool rel(TElem, TElem);

class IteratorMultime;

class Multime {

	friend class IteratorMultime;

private:
	int cp;
	int n;
	TElem* elem;
	int* urm;
	int prim;
	int primLiber;

	int aloca();
	void dealoca(int i);
	void initSpatiuLiber();
	void redim();
	int creeazaNod(TElem e);
	void reinitializeaza();

public:
		//constructorul implicit
		Multime();

		//adauga un element in multime
		//returneaza adevarat daca elementul a fost adaugat (nu exista deja in multime)
		bool adauga(TElem e);

		//sterge un element din multime
		//returneaza adevarat daca elementul a existat si a fost sters
		bool sterge(TElem e);

		//verifica daca un element se afla in multime
		bool cauta(TElem elem) const;


		//intoarce numarul de elemente din multime;
		int dim() const;

		//verifica daca multimea e vida;
		bool vida() const;

		//returneaza un iterator pe multime
		IteratorMultime iterator() const;

		// destructorul multimii
		~Multime();

		// păstrează numai acele elemente care nu apar în mulțimea b
		// returnează numărul de elemente eliminate
		int diferenta(const Multime& b);

		void print() {
			int poz = prim;
			for (int i = 1; i <= n; i++) {
				cout << "poz=" << poz << " elem=" << elem[poz] << "urm=" << urm[poz] << endl;
				poz = urm[poz];
			}
		}
};
