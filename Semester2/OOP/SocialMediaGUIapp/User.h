#pragma once
#include <string>
#include "Observer.h"
#include<sstream>
class User :public Subject {

private:
	std::string name;

public:
	User(std::string _name);
	User();
	~User();

	inline std::string getName() const {
		return this->name;
	}

	friend std::istream& operator>> (std::istream& stream, User& p);

};