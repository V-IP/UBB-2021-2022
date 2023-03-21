#include <assert.h>

#include "Service.h"


bool cmp_name(const Tenant& t1, const Tenant& t2)
{
	return t1.getOwner() < t2.getOwner();
}
bool cmp_surface(const Tenant& t1, const Tenant& t2) noexcept
{
	return t1.getSurface() < t2.getSurface();
}
bool cmp_type_surface(const Tenant& t1, const Tenant& t2)
{
	if (t1.getType() < t2.getType())
		return true;
	if (t1.getType() == t2.getType())
		if (t1.getSurface() < t2.getSurface())
			return true;
	return false;
}
bool cmpR_name(const Tenant& t1, const Tenant& t2)
{
	return t1.getOwner() >= t2.getOwner();
}
bool cmpR_surface(const Tenant& t1, const Tenant& t2) noexcept
{
	return t1.getSurface() >= t2.getSurface();
}
bool cmpR_type_surface(const Tenant& t1, const Tenant& t2)
{
	if (t1.getType() > t2.getType())
		return true;
	if (t1.getType() == t2.getType())
		if (t1.getSurface() > t2.getSurface())
			return true;
	return false;
}


const vector<Tenant>& Service::getAll_srv() const noexcept {
	return this->repo.getAll();
}

void Service::add_srv(int nrAp, string owner, string type, double surface) {
	Tenant t{ nrAp,owner,type,surface };
	valid.validate(t);
	repo.add(t);
	undoActions.push_back(std::make_unique<UndoAdd>(repo, t));
}

void Service::remove_srv(int nrAp) {
	Tenant tenant = repo.find(nrAp);
	repo.remove(tenant);
	undoActions.push_back(std::make_unique<UndoRemove>(repo, tenant));
}

void Service::modify_srv(int nrAp, string newOwner) {
	Tenant tenant = repo.find(nrAp);
	Tenant newTenant{ nrAp,newOwner,tenant.getType(),tenant.getSurface()};
	valid.validate(newTenant);
	repo.modify(tenant, newTenant);
	undoActions.push_back(std::make_unique<UndoModify>(repo, tenant, newTenant));
}

const Tenant& Service::find_srv(int nrAp) {
	return repo.find(nrAp);
}

const vector<Tenant> Service::filter_srv(string type_criteria, double surface_criteria) {
	vector<Tenant> filtered;
	if (type_criteria != "-1") {
		std::copy_if(repo.getAll().begin(), repo.getAll().end(), std::back_inserter(filtered), [type_criteria](const Tenant& t) {
			return t.getType() == type_criteria;
			});
	}
	if (surface_criteria != -1) {
		std::copy_if(repo.getAll().begin(), repo.getAll().end(), std::back_inserter(filtered), [surface_criteria](const Tenant& t) {
			return t.getSurface() == surface_criteria;
			});
	}
	return filtered;
}

const vector<Tenant> Service::sort_srv(bool (*cmp)(const Tenant&, const Tenant&))
{
	vector<Tenant> all{ repo.getAll() };
	for (int i = 0; i < all.size(); i++)
	{
		for (int j = i + 1; j < all.size(); j++)
			if (!cmp(all[i], all[j]))
			{
				Tenant aux = all[i];
				all[i] = all[j];
				all[j] = aux;
			}
	}
	return all;
}

void Service::undo() {
	if (undoActions.empty()) {
		throw RepoException{ "There are no Undos left!\n" };
	}
	undoActions.back()->doUndo();
	undoActions.pop_back();
}

void Service::addToWishlist(int nr) {
	repo2.addToWishlist(nr);
}
void Service::deleteAll() noexcept{
	repo2.deleteAll();
}
const vector<Tenant> Service::getAllWishlist() {
	return repo2.getAllWishList();
}
void Service::addRandom(int cate) {
	repo2.addRandom(cate);
}

void Service::updateMap_srv() {
	umap.updateMap();
}

const unordered_map<string, int> Service::getAllMap_srv() {
	return umap.getAllMap();
}

void testValidate() {
	Validator testValid;

	try {
		Tenant t1{ -7,"Name1","Type1",1 };
		testValid.validate(t1);}
	catch (ValidationException& ve) {
		assert(ve.getErrorMsg() == "Invalid apartment number!\n");
	}


	try {
		Tenant t2{ 2,"","Type2",2 };
		testValid.validate(t2);}
	catch (ValidationException& ve) {
		assert(ve.getErrorMsg() == "Invalid owner name!\n");
	}


	try {
		Tenant t3{ 3,"Name3","",3 };
		testValid.validate(t3);}
	catch (ValidationException& ve) {
		assert(ve.getErrorMsg() == "Invalid apartment type!\n");
	}

	try {
		Tenant t4{ 4,"Name4","Type4",-500 };
		testValid.validate(t4);}
	catch (ValidationException& ve) {
		assert(ve.getErrorMsg() == "Invalid apartment surface!\n");
	}
}

void testAdd() {
	Repository testRepo;
	WishList testRepo2{ testRepo };
	Validator testValid;
	UnorderedMap umap{ testRepo };
	Service testSrv{ testRepo,testValid,testRepo2,umap };

	testSrv.add_srv(1, "Name1", "Type1", 37.75);
	testSrv.undo();
	try {
		testSrv.undo();
	}
	catch (RepoException) {
		assert(true);
	}
	testSrv.add_srv(1, "Name1", "Type1", 37.75);
	testSrv.add_srv(2, "Name2", "Type2", 80.55);
	testSrv.add_srv(3, "Name3", "Type3", 50);
	testSrv.add_srv(4, "Name4", "Type1", 400);
	assert(testSrv.getAll_srv().size() == 4);

	try {
		testSrv.add_srv(1, "Name1", "Type1", 37.75);
	}
	catch (RepoException& re) {
		assert(re.getErrorMsg() == "The object already exists!\n");
	}

	try {
		testSrv.addToWishlist(5);
	}
	catch (RepoException) {
		assert(true);
	}

	try {
		testSrv.addRandom(10);
	}
	catch (RepoException) {
		assert(true);
	}

	testSrv.addToWishlist(1);
	assert(testSrv.getAllWishlist().size() == 1);
	testSrv.deleteAll();
	assert(testSrv.getAllWishlist().size() == 0);
	testSrv.addRandom(1);
	assert(testSrv.getAllWishlist().size() == 1);

	testSrv.updateMap_srv();
	testSrv.getAllMap_srv();


	testSrv.add_srv(5, "Name5", "Type5", 50);
	assert(testSrv.getAll_srv().size() == 5);
	testSrv.undo();
	assert(testSrv.getAll_srv().size() == 4);
}

void testRemove() {
	Repository testRepo;
	WishList testRepo2{ testRepo };
	Validator testValid;
	UnorderedMap umap{ testRepo };
	Service testSrv{ testRepo,testValid,testRepo2,umap };

	testSrv.add_srv(1, "Name1", "Type1", 37.75);
	testSrv.add_srv(2, "Name2", "Type2", 80.55);
	testSrv.add_srv(3, "Name3", "Type3", 50);
	assert(testSrv.getAll_srv().size() == 3);

	testSrv.remove_srv(2);
	assert(testSrv.getAll_srv().size() == 2);

	try {
		testSrv.remove_srv(2);
	}
	catch (RepoException& re) {
		assert(re.getErrorMsg() == "The object doesn't exists!\n");
	}

	testSrv.remove_srv(1);
	assert(testSrv.getAll_srv().size() == 1);
	testSrv.undo();
	assert(testSrv.getAll_srv().size() == 2);
}

void testModify() {
	Repository testRepo;
	WishList testRepo2{ testRepo };
	Validator testValid;
	UnorderedMap umap{ testRepo };
	Service testSrv{ testRepo,testValid,testRepo2,umap };

	testSrv.add_srv(1, "Name1", "Type1", 37.75);
	testSrv.add_srv(2, "Name2", "Type2", 80.55);
	testSrv.add_srv(3, "Name3", "Type3", 50);
	assert(testSrv.getAll_srv().size() == 3);
	
	testSrv.modify_srv(3, "newName");
	Tenant t = testRepo.find(3);
	assert(t.getOwner() == "newName");

	try {
		testSrv.modify_srv(15, "newName");
	}
	catch (RepoException& re) {
		assert(re.getErrorMsg() == "The object doesn't exists!\n");
	}

	testSrv.modify_srv(1, "newName");
	Tenant t1 = testRepo.find(1);
	assert(t1.getOwner() == "newName");
	testSrv.undo();
	Tenant t2 = testRepo.find(1);
	assert(t2.getOwner() == "Name1");
}

void testfind() {
	Repository testRepo;
	WishList testRepo2{ testRepo };
	Validator testValid;
	UnorderedMap umap{ testRepo };
	Service testSrv{ testRepo,testValid,testRepo2,umap };

	testSrv.add_srv(1, "Name1", "Type1", 37.75);
	testSrv.add_srv(2, "Name2", "Type2", 80.55);
	testSrv.add_srv(3, "Name3", "Type3", 50);
	assert(testSrv.getAll_srv().size() == 3);

	Tenant t2 = testSrv.find_srv(2);
	assert(t2.getNrAp() == 2);
	assert(t2.getOwner() == "Name2");
	assert(t2.getType() == "Type2");
	assert(t2.getSurface() == 80.55);

	try {
		testSrv.find_srv(15);
	}
	catch (RepoException& re) {
		assert(re.getErrorMsg() == "The object doesn't exists!\n");
	}
}

void testFilter() {
	Repository testRepo;
	WishList testRepo2{ testRepo };
	Validator testValid;
	UnorderedMap umap{ testRepo };
	Service testSrv{ testRepo,testValid,testRepo2,umap };

	testSrv.add_srv(1, "Name1", "Type1", 37.75);
	testSrv.add_srv(2, "Name2", "Type2", 80.55);
	testSrv.add_srv(3, "Name3", "Type3", 37.75);
	testSrv.add_srv(4, "Name4", "Type2", 13.12);
	assert(testSrv.getAll_srv().size() == 4);

	vector<Tenant> f1 = testSrv.filter_srv("Type2", -1);
	assert(f1.size() == 2);

	vector<Tenant> f2 = testSrv.filter_srv("-1", 37.75);
	assert(f1.size() == 2);
}

void testSort() {
	Repository testRepo;
	WishList testRepo2{ testRepo };
	Validator testValid;
	UnorderedMap umap{ testRepo };
	Service testSrv{ testRepo,testValid,testRepo2,umap };

	testSrv.add_srv(1, "Name1", "Type1", 37.75);
	testSrv.add_srv(2, "BName2", "BType2", 80.55);
	testSrv.add_srv(3, "FName3", "FType3", 100);
	testSrv.add_srv(4, "Name4", "Type1", 13.12);
	assert(testSrv.getAll_srv().size() == 4);

	vector<Tenant> s1 = testSrv.sort_srv(cmp_name);
	assert(s1[0].getNrAp() == 2);
	assert(s1[1].getNrAp() == 3);
	assert(s1[2].getNrAp() == 1);
	assert(s1[3].getNrAp() == 4);

	vector<Tenant> s2 = testSrv.sort_srv(cmpR_name);
	assert(s2[0].getNrAp() == 4);
	assert(s2[1].getNrAp() == 1);
	assert(s2[2].getNrAp() == 3);
	assert(s2[3].getNrAp() == 2);

	vector<Tenant> s3 = testSrv.sort_srv(cmp_surface);
	assert(s3[0].getNrAp() == 4);
	assert(s3[1].getNrAp() == 1);
	assert(s3[2].getNrAp() == 2);
	assert(s3[3].getNrAp() == 3);

	vector<Tenant> s4 = testSrv.sort_srv(cmpR_surface);
	assert(s4[0].getNrAp() == 3);
	assert(s4[1].getNrAp() == 2);
	assert(s4[2].getNrAp() == 1);
	assert(s4[3].getNrAp() == 4);

	vector<Tenant> s5 = testSrv.sort_srv(cmp_type_surface);
	assert(s5[0].getNrAp() == 2);
	assert(s5[1].getNrAp() == 3);
	assert(s5[2].getNrAp() == 4);
	assert(s5[3].getNrAp() == 1);

	vector<Tenant> s6 = testSrv.sort_srv(cmpR_type_surface);
	assert(s6[0].getNrAp() == 1);
	assert(s6[1].getNrAp() == 4);
	assert(s6[2].getNrAp() == 3);
	assert(s6[3].getNrAp() == 2);
}