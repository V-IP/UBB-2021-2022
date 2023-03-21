#define _CRTDBG_MAP_ALLOC
#include <iostream>
#include <crtdbg.h>

#include "UI.h"

using std::cout;
using std::endl;

void testAll() {
	cout << "Starting tests!" << endl;
	testGetSet();
	testValidate();
	testAdd();
	testRemove();
	testModify();
	testfind();
	testFilter();
	testSort();
	cout << "Finished tests!" << endl;
}

void startApp() {
	Repository repo;
	WishList repo2{ repo };
	Validator valid;
	UnorderedMap umap{ repo };
	Service srv{ repo,valid,repo2,umap };
	ConsoleUI ui{ srv };

	ui.run();
}

int main() {
	testAll();
	startApp();
	_CrtDumpMemoryLeaks();
}