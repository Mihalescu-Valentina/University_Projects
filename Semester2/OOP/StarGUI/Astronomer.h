#pragma once
#include <string>
#include<sstream>
class Astronomer {

private:
	std::string name, constellation;

public:
	Astronomer(std::string _name, std::string _constellation);
	Astronomer();
	~Astronomer();

	inline std::string getName() const {
		return this->name;
	}

	inline std::string getConstellation() const {
		return this->constellation;
	}

	

	friend std::istream& operator>> (std::istream& stream,Astronomer&a);

};