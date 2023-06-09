#pragma once

#include <vector>

typedef int TCheie;
typedef int TValoare;

const int MAX = 13;

#include <utility>
typedef std::pair<TCheie, TValoare> TElem;

using namespace std;

class IteratorMDO;

class Nod;

typedef Nod* PNod;

class Nod
{
private:
	TElem e;
	PNod urm;
public:
	friend class MDO;
	friend class IteratorMDO;
	Nod(TElem e, PNod urm);
	TElem element();
	PNod urmator();
};

typedef bool(*Relatie)(TCheie, TCheie);

class MDO {
	friend class IteratorMDO;
private:
	int m; //numarul de locatii din tabela de dispersie
	PNod* l;
	Relatie rel;
	int dispersie(TCheie e);
public:

	// constructorul implicit al MultiDictionarului Ordonat
	MDO(Relatie r);

	// adauga o pereche (cheie, valoare) in MDO
	void adauga(TCheie c, TValoare v);

	//cauta o cheie si returneaza vectorul de valori asociate
	vector<TValoare> cauta(TCheie c);

	//sterge o cheie si o valoare 
	//returneaza adevarat daca s-a gasit cheia si valoarea de sters
	bool sterge(TCheie c, TValoare v);

	//returneaza numarul de perechi (cheie, valoare) din MDO 
	int dim() const;

	//verifica daca MultiDictionarul Ordonat e vid 
	bool vid() const;

	// se returneaza iterator pe MDO
	// iteratorul va returna perechile in ordine in raport cu relatia de ordine
	IteratorMDO iterator() const;

	// destructorul 	
	~MDO();

	// returneaza valoarea care apare cel mai frecvent in multidictionar. 
	// Daca mai multe valori apar cel mai frecvent, se returneaza una (oricare) dintre ele.
	// Daca multidictionarul este vid, operatia returneaza NULL_TVALOARE
	TValoare ceaMaiFrecventaValoare() const;

};
