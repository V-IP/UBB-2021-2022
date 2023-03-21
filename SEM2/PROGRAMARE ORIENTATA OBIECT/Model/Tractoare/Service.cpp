#include "Service.h"
#include <assert.h>
#include <fstream>

const vector<Obj>& Service::getAll_srv() const {
	return this->repo.getAll();
}

void Service::add_srv(int id, string denumire, string tip, int nrRoti) {
	Obj obj{ id,denumire,tip,nrRoti };
	valid.validate(obj);
	repo.add(obj);
}

void testValidate() {
	Validator testValid;

	try {
		Obj o1{ -7,"Denumire1","Tip1",2 };
		testValid.validate(o1);
	}
	catch (ValidationException& ve) {
		assert(ve.getErrorMsg() == "Id invalid!\n");
	}


	try {
		Obj o2{ 2,"","Tip2",2 };
		testValid.validate(o2);
	}
	catch (ValidationException& ve) {
		assert(ve.getErrorMsg() == "Denumire invalida!\n");
	}


	try {
		Obj o3{ 3,"Denumire3","",3 };
		testValid.validate(o3);
	}
	catch (ValidationException& ve) {
		assert(ve.getErrorMsg() == "Tip invalid!\n");
	}

	try {
		Obj o4{ 4,"Denumire4","Tip4",-500 };
		testValid.validate(o4);
	}
	catch (ValidationException& ve) {
		assert(ve.getErrorMsg() == "Numar de roti invalid!\n");
	}
}

void testAdd() {
	Repository testRepo;
	Validator testValid;
	Service testSrv{ testRepo, testValid };

	testSrv.add_srv(1, "Denumire1", "Tip1", 2);
	testSrv.add_srv(2, "Denumire2", "Tip2", 4);
	testSrv.add_srv(3, "Denumire3", "Tip3", 12);
	testSrv.add_srv(4, "Denumire4", "Tip1", 16);
	assert(testSrv.getAll_srv().size() == 4);

	try {
		testSrv.add_srv(1, "Denumire", "Tip", 10);
	}
	catch (RepoException& re) {
		assert(re.getErrorMsg() == "The object already exists!\n");
	}
}

void testFileRepo() {
	std::ofstream ofs;
	ofs.open("test.txt", std::ofstream::out | std::ofstream::trunc);
	ofs << "1,Name1,Type1,2\n";
	ofs << "2,Name2,Type2,4\n";
	ofs << "3,Name3,Type3,12\n";
	ofs << "4,Name4,Type4,16\n";
	ofs.close();
	try {
		FileRepository testFileRepo{ "test2.txt" };
	}
	catch (RepoException&) {
		assert(true);
	}
	FileRepository testFileRepo{ "test.txt" };
	assert(testFileRepo.getAll().size() == 4);
}