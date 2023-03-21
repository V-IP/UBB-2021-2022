#include <QtWidgets/QApplication>
#include <iostream>

#include "UI.h"
#include "TemaQt.h"
#include "ServiceGUI.h"

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
	testFileRepo();
	cout << "Finished tests!" << endl;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	FileRepository fileRepo{ "text.txt" };
	Validator valid;
	WishList repo2{ fileRepo };
	Service srv{ fileRepo,repo2,valid };
	ServiceGUI gui{ srv };
	gui.show();
    return a.exec();
}
