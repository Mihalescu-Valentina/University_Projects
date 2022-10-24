#pragma once
#include<vector>
#include "Programmer.h"
class ProgrammerRepo {

private:
	std::string filename;
	std::vector<Programmer> programmers;

public:
	ProgrammerRepo(std::string& filename);
	std::vector<Programmer> getProgrammers() { return this->programmers; };
	~ProgrammerRepo();
	void readFromFile();
	
};