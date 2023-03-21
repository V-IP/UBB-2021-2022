#pragma once
#include <iostream>

using namespace std;
typedef int TElem;
class IteratorColectie;


typedef bool(*Relatie)(TElem, TElem);

//in implementarea operatiilor se va folosi functia (relatia) rel (de ex, pentru <=)
// va fi declarata in .h si implementata in .cpp ca functie externa colectiei
bool rel(TElem, TElem);

class Colectie {

	friend class IteratorColectie;

public:

	int cp;
	int n;
	TElem* elem;
	int* pt;
	int* st;
	int* dr;
	int* fr;
	int rad;
	int primLiber;
	Relatie r;

	int aloca();
	void dealoca(int i);
	void initSpatiuLiber();
	void redim();
	int creeazaNod(TElem e);
	void reinitializeaza();
	int minim(int p);
	int adauga_rec(int p, int pt, TElem e);
	int cauta_rec(int p, TElem e);
	int sterge_rec(int p, TElem e);
	int dim_rec(int p) const;

public:
	//constructorul implicit
	Colectie();

	//adauga un element in colectie
	void adauga(TElem e);

	//sterge o aparitie a unui element din colectie
	//returneaza adevarat daca s-a putut sterge
	bool sterge(TElem e);

	//verifica daca un element se afla in colectie
	bool cauta(TElem e);

	//returneaza numar de aparitii ale unui element in colectie
	int nrAparitii(TElem e);

	//intoarce numarul de elemente din colectie;
	int dim() const;

	//verifica daca colectia e vida;
	bool vida() const;

	//returneaza un iterator pe colectie
	IteratorColectie iterator() const;

	// destructorul colectiei
	~Colectie();

	// sterge nr aparitii ale elementului elem in colectie.
	// arunca exceptie in cazul in care este nr este mai mare decat numarul de aparitii ale elementului sau este negativ.
	bool stergeAparitiiMultiple(int nr, TElem elem);

};

