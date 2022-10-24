#pragma once
#include<vector>
#include "User.h"
class UserRepo {

private:
	std::string filename;
	std::vector<User> users;

public:
	UserRepo(std::string& filename);
	UserRepo();
	std::vector<User> getUsers() { return this->users; };
	~UserRepo();
	void readFromFile();

};