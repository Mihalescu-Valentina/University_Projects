#pragma once
#include<vector>
#include "Astronomer.h"
class AstronomerRepo {

private:
	std::string filename;
	std::vector<Astronomer> astronomers;

public:
	AstronomerRepo(std::string& filename);
	std::vector<Astronomer> getAstronomers() { return this->astronomers; };
	~AstronomerRepo();
	void readFromFile();
	inline int getSize() {
		return this->astronomers.size();
	}
	
};