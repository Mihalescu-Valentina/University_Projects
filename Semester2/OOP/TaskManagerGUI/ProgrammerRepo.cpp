#include "ProgrammerRepo.h"
#include <fstream>

ProgrammerRepo::ProgrammerRepo(std::string& _filename) {
	this->filename = _filename;
	this->readFromFile();
}


ProgrammerRepo::~ProgrammerRepo()
{
}

void ProgrammerRepo::readFromFile() {

	std::ifstream file(this->filename);
	if (file.is_open() == false)
		return;
	Programmer p;
	while (file >> p)
		this->programmers.push_back(p);
	file.close();

}