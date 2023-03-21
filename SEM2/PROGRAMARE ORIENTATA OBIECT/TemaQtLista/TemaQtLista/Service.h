#pragma once
#include "Validator.h"
#include "Repository.h"
#include "Undo.h"

class Service {
private:
	Repository& repo;
	WishList& repo2;
	Validator& valid;
	vector<unique_ptr<UndoAction>> undoActions;
public:
	Service(Repository& repo, WishList& repo2, Validator& valid) noexcept :repo{ repo }, repo2{ repo2 }, valid{ valid }{};
	Service(const Service& ot) = delete;

	const vector<Tenant>& getAll_srv() const noexcept;

	void add_srv(int nrAp, string owner, string type, double surface);
	void remove_srv(int nrAp);
	void modify_srv(int nrAp, string newOwner);
	const Tenant& find_srv(int nrAp);
	const vector<Tenant> filter_srv(string type_criteria, double surface_criteria);
	const vector<Tenant> sort_srv(bool (*cmp)(const Tenant&, const Tenant&));

	void undo();

	void addToWishlist(int nr);
	const vector<Tenant> getAllWishlist();
	void deleteAll() noexcept;
	void addRandom(int nr);

};


bool cmp_name(const Tenant& t1, const Tenant& t2);
bool cmp_surface(const Tenant& t1, const Tenant& t2) noexcept;
bool cmp_type_surface(const Tenant& t1, const Tenant& t2);
bool cmpR_name(const Tenant& t1, const Tenant& t2);
bool cmpR_surface(const Tenant& t1, const Tenant& t2) noexcept;
bool cmpR_type_surface(const Tenant& t1, const Tenant& t2);