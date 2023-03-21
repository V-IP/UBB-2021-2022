#include "Validator.h"

string ValidationException::getErrorMsg() {
	string fullMsg = "";
	for (const string err : errorMsg) {
		fullMsg += err + "\n";
	}
	return fullMsg;
}


void Validator::validate(const Obj& obj) {
	vector<string> errors;
	if (obj.getId() <= 0)
		errors.push_back("Id invalid!\n");
	if (obj.getDenumire().length() == 0)
		errors.push_back("Denumire invalida!\n");
	if (obj.getTip().length() == 0)
		errors.push_back("Tip invalid!\n");
	if (obj.getNrRoti() < 2 || obj.getNrRoti() > 16 || obj.getNrRoti() % 2 == 1)
		errors.push_back("Numar de roti invalid!\n");

	if (errors.size() > 0)
		throw ValidationException(errors);
}