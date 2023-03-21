#pragma once

#include "Obj.h"

class RepoException {
private:
	string errorMsg;
public:
	RepoException(string errorMsg) :errorMsg{ errorMsg } {};

	string getErrorMsg() {
		return this->errorMsg;
	}
};

class Repository {
private:
	vector<Obj> all;
public:
	Repository() = default;
	Repository(const Repository & ot) = delete;

	const vector<Obj>& getAll();
	const Obj& find(int id);
	bool exists(const Obj& obj);
	virtual void add(const Obj& obj);
};

class FileRepository :public Repository {
private:
	string filename;
	void loadFromFile();
	void saveToFile();
public:
	FileRepository(string filename) :Repository(), filename{ filename }{
		loadFromFile();
	};
	void add(const Obj& obj) override;
};