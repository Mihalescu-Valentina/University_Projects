#include "AstronomerRepo.h"
#include <fstream>

AstronomerRepo::AstronomerRepo(std::string& _filename) {
	this->filename = _filename;
	this->readFromFile();
}


AstronomerRepo::~AstronomerRepo()
{
}

void AstronomerRepo::readFromFile() {

	std::ifstream file(this->filename);
	if (file.is_open() == false)
		return;
	Astronomer a;
	while (file >> a)
		this->astronomers.push_back(a);
	file.close();

}