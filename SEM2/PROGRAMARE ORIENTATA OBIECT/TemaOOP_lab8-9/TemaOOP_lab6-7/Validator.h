#pragma once
#include <vector>
#include <string>
#include <assert.h>

#include "Obj.h"

using std::vector;
using std::string;

class ValidationException {
	vector<string> errorMsg;
public:
	ValidationException(vector<string> errorMsgs) : errorMsg{ errorMsgs } {};

	string getErrorMsg();
};

class Validator {
public:
	void validate(const Tenant& t);
};