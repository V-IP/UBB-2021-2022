#pragma once
#include "Validator.h"
#include "Repository.h"
#include "Undo.h"

class Service {
private:
	Repository& repo;
	Validator& valid;
	WishList& repo2;
	UnorderedMap& umap;
	vector<unique_ptr<UndoAction>> undoActions;
public:
	Service(Repository& repo, Validator& valid, WishList& repo2, UnorderedMap& umap) noexcept :repo{ repo }, valid{ valid }, repo2{ repo2 }, umap{ umap }{};
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
	void addRandom(int cate);

	void updateMap_srv();
	const unordered_map<string, int> getAllMap_srv();
};

void testValidate();
void testAdd();
void testRemove();
void testModify();
void testfind();
void testFilter();
void testSort();


bool cmp_name(const Tenant& t1, const Tenant& t2);
bool cmp_surface(const Tenant& t1, const Tenant& t2) noexcept;
bool cmp_type_surface(const Tenant& t1, const Tenant& t2);
bool cmpR_name(const Tenant& t1, const Tenant& t2);
bool cmpR_surface(const Tenant& t1, const Tenant& t2) noexcept;
bool cmpR_type_surface(const Tenant& t1, const Tenant& t2);