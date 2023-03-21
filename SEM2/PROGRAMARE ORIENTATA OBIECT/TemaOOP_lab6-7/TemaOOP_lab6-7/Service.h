#pragma once
#include "Validator.h"
#include "Repository.h"

class Service {
private:
	Repository& repo;
	Validator& valid;
public:
	Service(Repository& repo, Validator& valid) noexcept :repo{ repo }, valid{ valid }{};
	Service(const Service& ot) = delete;

	const MyList<Tenant>& getAll_srv() const noexcept;

	void add_srv(int nrAp, string owner, string type, double surface);
	void remove_srv(int nrAp);
	void modify_srv(int nrAp, string newOwner);
	const Tenant& find_srv(int nrAp);
	const MyList<Tenant> filter_srv(string type_criteria, double surface_criteria);
	const MyList<Tenant> sort_srv(bool (*cmp)(const Tenant&, const Tenant&));
};

void testValidate();
void testAdd();
void testRemove();
void testModify();
void testFind();
void testFilter();
void testSort();


bool cmp_name(const Tenant& t1, const Tenant& t2);
bool cmp_surface(const Tenant& t1, const Tenant& t2);
bool cmp_type_surface(const Tenant& t1, const Tenant& t2);
bool cmpR_name(const Tenant& t1, const Tenant& t2);
bool cmpR_surface(const Tenant& t1, const Tenant& t2);
bool cmpR_type_surface(const Tenant& t1, const Tenant& t2);