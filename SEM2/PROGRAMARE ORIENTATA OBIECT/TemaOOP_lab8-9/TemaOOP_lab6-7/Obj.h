#pragma once
#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::endl;

class Tenant {
private:
	string owner;
	string type;
	int nrAp;
	double surface;
public:
	Tenant() = delete;
	Tenant(int nrAp, string owner, string type, double surface) : nrAp{ nrAp }, owner{ owner }, type{ type }, surface{ surface }{};
	/*Tenant(const Tenant& ot) : nrAp{ ot.nrAp }, owner{ ot.owner }, type{ ot.type }, surface{ ot.surface } {
		cout << "[TENANT] Copy constructor called." << endl;
	}*/

	int getNrAp() const noexcept;
	string getOwner() const;
	double getSurface() const noexcept;
	string getType() const;

	void setOwner(string newOwner);
};

void testGetSet();