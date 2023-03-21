#pragma once

class UndoAction {
public:
	virtual void doUndo() = 0;
	virtual ~UndoAction() = default;
};

class UndoAdd :public UndoAction {
	Tenant t;
	Repository& repo;
public:
	UndoAdd(Repository& repo, const Tenant& t) :repo{ repo }, t{ t }{};
	void doUndo() override {
		repo.remove(t);
	}
};

class UndoRemove :public UndoAction {
	Tenant t;
	Repository& repo;
public:
	UndoRemove(Repository& repo, const Tenant& t) :repo{ repo }, t{ t }{};
	void doUndo() override {
		repo.add(t);
	}
};

class UndoModify :public UndoAction {
	Tenant oldT;
	Tenant newT;
	Repository& repo;
public:
	UndoModify(Repository& repo, const Tenant& oldT, const Tenant& newT) : repo{ repo }, oldT{ oldT }, newT{ newT }{};
	void doUndo() override {
		repo.remove(newT);
		repo.add(oldT);
	}
};