#pragma once
#pragma once
#include "Repository.h"
class Service {
private:Repository repo;
public:
	int add(Protein p);
	int getSize();
	Service(Repository repo);
	DynamicVector<Protein>& getData();
	int remove(Protein p);
	void addProteins();
};