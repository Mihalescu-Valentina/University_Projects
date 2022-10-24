#include "UserRepo.h"
#include <fstream>

UserRepo::UserRepo(std::string& _filename) {
	this->filename = _filename;
	this->readFromFile();
}


UserRepo::~UserRepo()
{
}

void UserRepo::readFromFile() {

	std::ifstream file(this->filename);
	if (file.is_open() == false)
		return;
	User p;
	while (file >> p)
		this->users.push_back(p);
	file.close();

}