// VINCZE IULIA-PAULA, gr. 217


#include <iostream>
#include <cstring>
#include <cmath>
#include <stack>
#include <stdlib.h>
using namespace std;
stack<char> stiva;


void baza(char numar[100], int baza1, int baza2)
/*
	Functie care determina un numar din baza initiala in baza destinatie folosind baza intermediara 10
	input: numar - numarul in baza sursa
           baza1 - baza initiala in care se introduce numarul
		   baza2 - baza destinatie in care se calculeaza numarul
	output: mesaj, numarul in baza introdusa
*/
{
    char c1;
    int nr10=0, p=0, contor=1, cifra;
    while(contor <= strlen(numar))
    {
		c1 = numar[strlen(numar) - contor]; //retin caracterul curent
		if (c1 >= 'A' && c1 <= 'Z') //trandform caracterul curent in int
			cifra = c1 - 55;
		else
			cifra = c1 - '0';
        nr10 = nr10 + cifra * pow(baza1,p); //creez numarul in baza 10
        contor++; p++;
    }
    while(nr10)
    {
        if(nr10 % baza2 < 10) //pun pe stiva cifrele numarului in baza destinatie
            stiva.push(nr10 % baza2 + '0');
        else
            stiva.push('A' + nr10 % baza2 - 10);
        nr10 /= baza2; //impart nr la baza2 cat timp e dif de 0
    }
}

void adunare(char nr1[], char nr2[], int baza, int t, int p)
/*
	Functie care determina si afiseaza suma a doua numere dintr-o baza oarecare
	input: nr1 - primul numar
		   nr2 - al doilea numar
		   baza - baza in care s-au introdus numerele, aceeasi in care se realizeaza suma acestora
		   t - transportul necesar in adunare
		   p - contor pentru a lua cifra cu cifra din numerele introduse
	output: mesaj, suma numerelor in baza introdusa
*/
{
	char c1, c2;
	int cifra1, cifra2;
	if(p <= strlen(nr1) || p <= strlen(nr2)) //cat timp putem aduna cifra cu cifra
	{
		c1 = nr1[strlen(nr1) - p], c2 = nr2[strlen(nr2) - p];
		if (c1 >= 'A' && c1 <= 'Z')
			cifra1 = c1 - 55;
		else
			cifra1 = c1 - '0';
		if (c2 >= 'A' && c2 <= 'Z')
			cifra2 = c2 - 55;
		else
			cifra2 = c2 - '0'; //transform cifrele din char in int
		if (p > strlen(nr1)) //daca un nr e mai mare decat celalalt, cifrele ramase vor fi adunate cu 0
			cifra1 = 0;
		if (p > strlen(nr2))
			cifra2 = 0;
		p++;
		if ((cifra1 + cifra2 + t) % baza < 10)
			stiva.push((cifra1 + cifra2 + t) % baza + '0');
		else
			stiva.push('A' + (cifra1 + cifra2 + t) % baza - 10); //adaug pe stiva suma
		adunare(nr1 , nr2, baza, (cifra1 + cifra2 + t) / baza, p);
	}
	else if (t != 0)
        stiva.push(t + '0'); //daca exista transport nefolosit, il retin, de ex: 50+50, restul nefolosit este 1 de la 100
}

void ADUNARE1()
/*
	Functie care citeste de la utilizator doua numere si o baza oarecare pentru a realiza suma acestora
	input: -
	output: -
*/
{
	char nr1[100], nr2[100];
	int baza;
	cout << "Baza in care lucrati este: "; cin >> baza;
	cin.get();
	cout << "Primul numar este (in baza intorusa): "; cin.getline(nr1, 100);
	cout << "Al doilea numar este (in baza introdusa): "; cin.getline(nr2, 100);
	adunare(nr1, nr2, baza, 0, 1);
	cout << "Suma in baza "<<baza<<" este: ";
	while (!stiva.empty())
    {
        cout << stiva.top();
        stiva.pop();
    }
}

void scadere(char nr1[], char nr2[], int baza, int t, int p)
/*
	Functie care determina si afiseaza diferenta a doua numere dintr-o baza oarecare
	input: nr1 - primul numar
		   nr2 - al doilea numar
		   baza - baza in care s-au introdus numerele, aceeasi in care se realizeaza diferenta acestora
		   t - transportul necesar in scadere
		   p - contor pentru a lua cifra cu cifra din numerele introduse
	output: mesaj, diferenta numerelor in baza introdusa
*/
{
	char c1, c2;
	int cifra1, cifra2;
	if (p <= strlen(nr2))
	{
		c1 = nr1[strlen(nr1) - p], c2 = nr2[strlen(nr2) - p];
		if (c1 >= 'A' && c1 <= 'Z')
			cifra1 = c1 - 55;
		else
			cifra1 = c1 - '0';
		if (c2 >= 'A' && c2 <= 'Z')
			cifra2 = c2 - 55;
		else
			cifra2 = c2 - '0'; //transform cifrele din char in int
		p++;
		if (cifra1 >= cifra2)
		{
			if (cifra1 - cifra2 - t < 10)
				stiva.push(cifra1 - cifra2 - t + '0'); //adaug pe stiva diferenta
			else
				stiva.push('A' + (cifra1 - cifra2 - t) - 10);
			scadere(nr1, nr2, baza, 0, p); //apelez functia mentionand ca nu am facut imprumut
		}
		else
		{
			if ((baza + cifra1) - cifra2 - t < 10)
                stiva.push((baza + cifra1) - cifra2 - t + '0'); //adaug pe stiva diferenta
			else
				stiva.push('A' + ((baza + cifra1) - cifra2 - t) - 10);
			scadere(nr1, nr2, baza, 1, p); //apelez functia mentionand ca am facut imprumut
		}
	}
	else if (p <= strlen(nr1)) //daca am ramas cu cifre din primul nr trebuie sa le afisez, tinand cont de transport, de ex la 1002-8 unde imprumutul se tot muta
		for (cifra1 = strlen(nr1) - p; cifra1 >= 0; cifra1--)
            if((nr1[cifra1] - '0') - t > 0)
            {
                    stiva.push((nr1[cifra1] - '0') - t + '0');
                    t = 0;
            }
            else if ((nr1[cifra1] - '0') - t < 0)
                {
                    stiva.push((baza + nr1[cifra1] - '0') - t + '0');
                    t = 1;
                }
                else if (cifra1 != 0)
                    {
                        stiva.push((nr1[cifra1] - '0') - t + '0');
                        t = 0;
                    }
}

void SCADERE2()
/*
	Functie care citeste de la utilizator doua numere si o baza oarecare pentru a realiza diferenta acestora
	input: -
	output: -
*/
{
	char nr1[100], nr2[100];
	int baza;
	cout << "Baza in care lucrati este: "; cin >> baza;
	cin.get();
	cout << "Primul numar este (in baza introdusa): "; cin.getline(nr1, 100);
	cout << "Al doilea numar este (in baza introdusa): "; cin.getline(nr2, 100);
	if ((strlen(nr1) > strlen(nr2)) || (strlen(nr1) == strlen(nr2) && strcmp(nr1,nr2) >= 0))
    {
        scadere(nr1, nr2, baza, 0, 1);
        cout << "Diferenta in baza "<<baza<<" este: ";
        while (!stiva.empty())
        {
            cout << stiva.top();
            stiva.pop();
        }
    }
    else
        cout<<"Eroare! Descazutul trebuie sa fie mai mare decat scazatorul!"<<endl;
}

void inmultire(char nr1[], int nr2, int baza, int t, int p)
/*
	Functie care determina si afiseaza produsul a doua numere dintr-o baza oarecare
	input: nr1 - primul numar
		   nr2 - al doilea numar
		   baza - baza in care s-au introdus numerele, aceeasi in care se determina produsul acestora
		   t - transportul necesar la produs
		   p - contor pentru a lua cifra cu cifra din numerele introduse
	output: mesaj, produsul numerelor in baza introdusa
*/
{
	char c1;
	int cifra1;
	if (p <= strlen(nr1))
	{
		c1 = nr1[strlen(nr1) - p];
		if (c1 >= 'A' && c1 <= 'Z')
			cifra1 = c1 - 55;
		else
			cifra1 = c1 - '0'; //transform cifrele din char in int
		p++;
		if ((cifra1 * nr2 + t) % baza < 10)
			stiva.push((cifra1 * nr2 + t) % baza + '0'); //adaug produsul dintre cele 2 cifre pe stiva
		else
			stiva.push('A' + (cifra1 * nr2 + t) % baza - 10);
		inmultire(nr1, nr2, baza, (cifra1 * nr2 + t) / baza, p); //apelez functia cu mentionarea transportului care de fapt este catul dintre produs si baza
	}
	else if (p > strlen(nr1) && t != 0) // daca in final raman cu transport, trebuie afisat, de ex 20*5, trasportul ramas este acel 1 din 100
	{
		if (t % baza < 10)
			stiva.push(t % baza + '0');
		else
			stiva.push('A' + t % baza - 10);
		t = 0;
	}
}

void INMULTIRE3()
/*
	Functie care citeste de la utilizator doua numere si o baza oarecare pentru a realiza inmultirea acestora
	+ transformarea celui de-al doilea numar din string in int
	input: -
	output: -
*/
{
	char nr1[100],nr2[100];
	int baza, c2;
	cout << "Baza in care lucrati este: "; cin >> baza;
	cin.get();
	cout << "Primul numar este (in baza introdusa): "; cin.getline(nr1, 100);
	cout << "Al doilea numar este(in baza introdusa): "; cin.getline(nr2, 100);
	if (strlen(nr2) > 1)
        cout<<"Eroare!Al doilea numar trebuie sa fie doar o cifra!"<<endl;
    else
    {
        if (nr2[0] >= 'A' && nr2[0] <= 'Z')
            c2 = nr2[0] - 55;
        else
            c2 = nr2[0] - '0';
        inmultire(nr1, c2, baza, 0, 1);
        cout << "Produsul in baza "<<baza<<" este: ";
        while (!stiva.empty())
        {
            cout << stiva.top();
            stiva.pop();
        }
    }
}

void impartire(char nr1[], int nr2, int baza, int t, int p, char &rest)
/*
	Functie care determina si afiseaza catul si restul a doua numere dintr-o baza oarecare
	input: nr1 - primul numar
		   nr2 - al doilea numar
		   baza - baza in care s-au introdus numerele, aceeasi in care se determina catul si restul acestora
		   t - transportul necesar la impartire
		   p - contor pentru a lua cifra cu cifra din numerele introduse
	output: mesaj, catul si restul impartirii numerelor in baza introdusa
*/
{
	char c1;
	int cifra1;
	if (p < strlen(nr1))
	{
		c1 = nr1[p];
		if (c1 >= 'A' && c1 <= 'Z')
			cifra1 = c1 - 55;
		else
			cifra1 = c1 - '0'; //transform cifrele din char in int
		p++;
		impartire(nr1, nr2, baza, (t * baza + cifra1) % nr2, p, rest); //apelez functia cu trasportul aferent (daca nu este se transmite valoarea 0, adica se imparte exact)
		if ((t * baza + cifra1) / nr2 < 10)
        {
            if ((t * baza + cifra1) / nr2 != 0)
                stiva.push((t * baza + cifra1) / nr2 + '0');
        }
		else
			stiva.push('A' + (t * baza + cifra1) / nr2 - 10); //pun pe stiva cifrele aferente
	}
	else if (p == strlen(nr1) && t != 0)
		rest = t + '0'; //retin restul separat de cat
}

void IMPARTIRE4()
/*
	Functie care citeste de la utilizator doua numere si o baza oarecare pentru a realiza impartirea acestora
	+ transformarea celui de-al doilea numar din string in int
	input: -
	output: -
*/
{
	char rest = NULL, nr1[100], nr2[100];
	int baza, c2;
	cout << "Baza in care lucrati este: "; cin >> baza;
	cin.get();
	cout << "Primul numar este (in baza introdusa): "; cin.getline(nr1, 100);
	cout << "Al doilea numar este (in baza introdusa): "; cin.getline(nr2, 100);
	if (strlen(nr2) > 1)
        cout<<"Eroare!Al doilea numar trebuie sa fie doar o cifra!"<<endl;
    else
	{
	    if (strlen(nr1) > 1)
        {
            if (nr2[0] >= 'A' && nr2[0] <= 'Z')
                c2 = nr2[0] - 55;
            else
                c2 = nr2[0] - '0';
            impartire(nr1, c2, baza, 0, 0, rest);
            cout << "Catul in baza "<<baza<<" este: ";
            while (!stiva.empty())
            {
                cout << stiva.top();
                stiva.pop();
            }
            cout << " rest " << rest;
        }
        else if (nr1[0] < nr2[0])
            cout<<"Eroare!Deimpartitul trebuie sa fie mai mare decat impartitorul!"<<endl;
	}
}

void impartiri_succesive(char nr1[], int baza1, int baza2)
{
    stack<char> rezultat;
	char cat[100] = "", rest = NULL;
	int n = 0;
	while (nr1[0] != '\0') //cat timp numarul este diferit de 0
	{
		impartire(nr1, baza2, baza1, 0, 0, rest); //imaprt nr la baza destinatie
		while (!stiva.empty())
        {
            cat[n++] = stiva.top();
            stiva.pop();
        } //retin catul
		if (rest != NULL)
			if (rest >= '0' && rest <= '9')
				rezultat.push(rest);
			else
				rezultat.push('A' + int(rest) - 10);
        else
            rezultat.push('0'); //pun pe stiva restul, adica noua cifra a numarului in baza destinatie
        strcpy(nr1, cat); strcpy(cat, ""); rest = NULL; n=0;
	}
	while (!rezultat.empty())
    {
        cout << rezultat.top();
        rezultat.pop();
    } // afisez rezultatul
}

void IMPARTIRI_SUCCESIVE()
/*
	Functie care determina si afiseaza un numar dintr-o baza oarecare in baza introdusa
	input: -
	output: -
*/
{
	char nr1[100];
	int baza1, baza2;
	cout << "Introduceti baza initiala: "; cin >> baza1;
	cin.get();
	cout << "Introduceti numarul: "; cin.getline(nr1, 100);
	cout << "Introduceti baza dorita: "; cin >> baza2;
	if (baza2>baza1)
        cout<<"Eroare! Baza destinatie trebuie sa fie mai mica decat baza sursa!"<<endl;
    else
    {
        cout << "Numarul introdus in baza " << baza2 << " este: ";
        impartiri_succesive(nr1, baza1, baza2);
    }
}

void substitutie(char numar[100],int baza1, int baza2)
{
    char c1, nr1[100] = "", nr2[100] = "";
    int cifra1, p=1, n=0, m=0;
    while (p <= strlen(numar))
	{
		c1 = numar[strlen(numar) - p];
		if (c1 >= 'A' && c1 <= 'Z')
			cifra1 = c1 - 55;
		else
			cifra1 = c1 - '0'; //transform cifrele din char in int
        strcpy(nr2, ""); m=0;
        nr2[0] = cifra1*pow(baza1,p-1) + '0'; //pastrez inmultirea pt a o putea converti
        baza(nr2,baza1,baza2); strcpy(nr2, ""); m=0; //convertesc produsul in baza destinatie
        while(!stiva.empty())
        {
            nr2[m++] = stiva.top();
            stiva.pop();
        } //memorez numarul convertit
        adunare(nr1,nr2,baza2,0,1); strcpy(nr1, ""); n=0; //adauga la nr1, noul produs (de la urm cifra)
        while(!stiva.empty())
        {
            nr1[n++] = stiva.top();
            stiva.pop();
        } //retin inapoi in nr1 noua suma
        p++;
	}
    cout<<nr1; //afisez numarul
}

void SUBSTITUTIE()
{
    char nr1[100];
	int baza1, baza2;
	cout << "Introduceti baza initiala: "; cin >> baza1;
	cin.get();
	cout << "Introduceti numarul: "; cin.getline(nr1, 100);
	cout << "Introduceti baza dorita: "; cin >> baza2;
	if (baza2<baza1)
        cout<<"Eroare! Baza destinatie trebuie sa fie mai mare decat baza sursa!"<<endl;
    else
    {
        cout << "Numarul introdus in baza " << baza2 << " este: ";
        substitutie(nr1, baza1, baza2);
    }
}

void CONVERSIE()
/*
	Functie care determina si afiseaza un numar dintr-o baza oarecare in baza introdusa
	input: -
	output: -
*/
{
    char numar[100];
	int baza1, baza2;
	cout << "VINCZE IULIA-PAULA, gr. 217" << endl;
	cout << "Introduceti baza initiala: "; cin >> baza1; cin.get();
	cout << "Introduceti numarul in baza initiala: "; cin.getline(numar,100);
	cout << "Introduceti baza destinatie: "; cin >> baza2;
	baza(numar, baza1, baza2);
	cout << "Numarul introdus este ";
	while (!stiva.empty())
    {
        cout << stiva.top();
        stiva.pop();
    }
}

int main()
/*
	Functie care citeste de la utilizator optiunile dorite in functie de mesajul afisat
	input: -
	output: -
*/
{
	int opt, opt1, opt2;
	do
	{
		cout << endl << "VINCZE IULIA-PAULA, gr. 217" << endl;
		cout << "	0 - Iesire." << endl;
		cout << "	1 - Realizati o conversie intre baze." << endl;
		cout << "	2 - Realizati operatii in diferite baze." << endl;
		cout << "		Introduceti optiunea dorita: "; cin >> opt;
		system("CLS");
		switch (opt)
		{
		case 1:
			do
			{
				cout << "VINCZE IULIA-PAULA, gr. 217" << endl;
				cout << "	0 - Iesire." << endl;
				cout << "	1 - Conversie prin impartiri succesive. (dintr-o baza mai mare intr-o baza mai mica!)" << endl;
				cout << "	2 - Conversie prin substitutie. (dintr-o baza mai mica intr-o baza mai mare!)" << endl;
				cout << "	3 - Conversie utilizand o baza intermediara." << endl;
				cout << "		Introduceti optiunea conversiei dorite: "; cin >> opt1;
                system("CLS");
				switch (opt1)
				{
					case 0:
						break;
					case 1:
						IMPARTIRI_SUCCESIVE();
						cout << endl;
						break;
					case 2:
                        SUBSTITUTIE();
						cout << endl;
						break;
					case 3:
						CONVERSIE();
						cout << endl;
						break;
					default:
						break;
					}
					break;
			} while (opt1 != 0);
			break;
		case 2:
			do
			{
				cout << "VINCZE IULIA-PAULA, gr. 217" << endl;
				cout << "	0 - Iesire." << endl;
				cout << "	1 - Adunare." << endl;
				cout << "	2 - Scadere." << endl;
				cout << "	3 - Inmultire cu o cifra." << endl;
				cout << "	4 - Impartire la o cifra." << endl;
				cout << "		Introduceti optiunea operatiei dorite: "; cin >> opt2;
                system("CLS");
				switch (opt2)
				{
					case 0:
						break;
					case 1:
						ADUNARE1();
						cout << endl;
						break;
					case 2:
						SCADERE2();
						cout << endl;
						break;
					case 3:
						INMULTIRE3();
						cout << endl;
						break;
					case 4:
						IMPARTIRE4();
						cout << endl;
						break;
					default:
						break;
					}
					break;
			} while (opt2 != 0);
		default:
			break;
		}
	} while (opt != 0);
	return 0;
}
