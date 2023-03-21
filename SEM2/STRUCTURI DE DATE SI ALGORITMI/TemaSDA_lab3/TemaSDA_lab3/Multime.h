﻿#pragma once

typedef int TElem;

typedef bool(*Relatie)(TElem, TElem);

//in implementarea operatiilor se va folosi functia (relatia) rel (de ex, pentru <=)
// va fi declarata in .h si implementata in .cpp ca functie externa colectiei
bool rel(TElem, TElem);

class IteratorMultime;

class Nod;

typedef Nod* PNod;

class Nod
{
public:
	friend class Multime;
	Nod(TElem elem, PNod urm, PNod prec);
	TElem element();
	PNod urmator();
	PNod precedent();
private:
	TElem elem;
	PNod urm;
	PNod prec;
};


class Multime {

	friend class IteratorMultime;

private:
	PNod prim;
	PNod ultim;

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

	// adaugă toate elementele din mulțimea b în mulțimea curentă
	// foloseste interclasare
	void reuniune(const Multime& b);
};
