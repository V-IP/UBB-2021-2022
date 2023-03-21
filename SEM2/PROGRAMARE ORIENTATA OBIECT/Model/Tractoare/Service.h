#pragma once

#include "Validator.h"
#include "Repository.h"

class Service {
	Repository& repo;
	Validator& valid;
public:
	Service(Repository& repo, Validator& valid) noexcept :repo{ repo }, valid{ valid }{};
	Service(const Service& ot) = delete;

	const vector<Obj>& getAll_srv() const;

	void add_srv(int id, string denumire, string tip, int nrRoti);
};

void testValidate();
void testAdd();
void testFileRepo();