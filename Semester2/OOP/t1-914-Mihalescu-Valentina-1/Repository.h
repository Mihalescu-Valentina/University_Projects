#pragma once
#include "DynamicVector.h"
#include "Protein.h"
class Repository
{private:
	DynamicVector<Protein> elems{ 20 };

public:
	int add(Protein p); 
	const inline int getSize() { return this->elems.getSize(); };
	int remove(Protein p);
	

	DynamicVector<Protein>& getData();


};