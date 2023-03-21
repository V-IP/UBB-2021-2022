#pragma once
#include <vector>
#include <string>
#include <assert.h>

#include "Obj.h"

class ValidationException {
	vector<string> errorMsg;
public:
	ValidationException(vector<string> errorMsgs) : errorMsg{ errorMsgs } {};

	string getErrorMsg();
};

class Validator {
public:
	void validate(const Obj& t);
};