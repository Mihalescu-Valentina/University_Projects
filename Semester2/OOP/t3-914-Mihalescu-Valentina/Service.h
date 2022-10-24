#pragma once
#include "Disorder.h"
#include <vector>

class Service {
private:

	std::vector<Disorder> elems;
	std::string filename;
public:
	explicit Service(std::vector<Disorder>elems, std::string filename);
	~Service();
	virtual int getSize() const;
	virtual std::vector<Disorder>& getElems();
	void loadFromFile();
	std::vector<Disorder> filterByDisorder(std::string disorder);
	int findDisorder(std::string name);
	std::vector<Disorder> match(std::string match);


};
