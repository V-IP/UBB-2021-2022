#include "Validator.h"

string ValidationException::getErrorMsg() {
	string fullMsg = "";
	for (const string err : errorMsg) {
		fullMsg += err + "\n";
	}
	return fullMsg;
}


void Validator::validate(const Tenant& t) {
	vector<string> errors;
	if (t.getNrAp() <= 0)
		errors.push_back("Invalid apartment number!");
	if (t.getOwner().length() < 3)
		errors.push_back("Invalid owner name!");
	if (t.getType().length() < 3)
		errors.push_back("Invalid apartment type!");
	if (t.getSurface() <= 0)
		errors.push_back("Invalid apartment surface!");

	if (errors.size() > 0)
		throw ValidationException(errors);
}