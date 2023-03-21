#include <QtWidgets/QApplication>
#include <iostream>

#include "TemaQtLista.h"
#include "ServiceGUI.h"

using std::cout;
using std::endl;

int main(int argc, char* argv[])
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
