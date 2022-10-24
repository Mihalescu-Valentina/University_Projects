#pragma once
#include "Star.h"
#include<vector>
class StarRepo {

private:
	std::string filename;
	std::vector<Star> stars;

public:
	StarRepo(std::string& filename);
	std::vector<Star> getStars() { return this->stars; };
	void readFromFile();
	void writeToFile();
	int findStar(std::string name);
	~StarRepo();

	std::vector<Star> getSortedStars();
	void addStar(Star s);
	void removeStar(std::string name);
	inline int getSize() {
		return this->stars.size();
	}

	void updateStar(std::string name,Star s);
	

};