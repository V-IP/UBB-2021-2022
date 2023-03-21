#pragma once
#include "Service.h"

class ConsoleUI {
private:
	Service& srv;
public:
	ConsoleUI(Service& srv) noexcept :srv{ srv } {};
	ConsoleUI(const ConsoleUI& ot) = delete;

	void printMenu();
	void uiAdd();
	void uiRemove();
	void uiModify();
	void uiFind();
	void uiFilter();
	void uiSort();
	void printAll();
	void run();
};