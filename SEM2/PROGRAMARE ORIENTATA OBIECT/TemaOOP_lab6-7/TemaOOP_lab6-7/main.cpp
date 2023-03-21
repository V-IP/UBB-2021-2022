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
	testFind();
	testFilter();
	testSort();
	cout << "Finished tests!" << endl;
}

void startApp() {
	Repository repo;
	Validator valid;
	Service srv{ repo,valid };
	ConsoleUI ui{ srv };

	ui.run();
}

int main() {
	testAll();
	startApp();
	_CrtDumpMemoryLeaks();
}