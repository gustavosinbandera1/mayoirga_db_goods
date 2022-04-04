#pragma once
#include "pch.h"

class Application {
protected:
	mutex           cs;
	database        db;
public:
	int main();
};

