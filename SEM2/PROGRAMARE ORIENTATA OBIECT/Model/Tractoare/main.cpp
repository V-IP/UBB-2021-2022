#include "Tractoare.h"
#include <QtWidgets/QApplication>
#include "ServiceGUI.h"

void testAll() {
	cout << "Starting tests!" << endl;
	testGetSet();
	testValidate();
	testAdd();
	testFileRepo();
	cout << "Finished tests!" << endl;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	FileRepository fileRepo{ "text.txt" };
	Validator valid;
	Service srv{ fileRepo,valid };
	ServiceGUI gui{ srv };
	gui.show();
	return a.exec();
}
