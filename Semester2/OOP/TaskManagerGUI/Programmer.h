#pragma once
#include <string>
#include "Observer.h"
#include<sstream>
class Programmer:public Subject {

private:
    std::string name;
	int id;

public:
	Programmer(std::string _name, int _id);
	Programmer();
	~Programmer();

	inline std::string getName() const {
		return this->name;
	}

	inline int getId() const {
		return this->id;
	}
	friend std::istream& operator>> (std::istream& stream,Programmer&p);

};