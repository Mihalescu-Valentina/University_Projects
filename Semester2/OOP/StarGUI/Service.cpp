#include "Service.h"

Service::Service(AstronomerRepo& astronomerRepo, StarRepo& starRepo): astronomerRepo{astronomerRepo},starRepo{starRepo}
{
}

void Service::addStar(Star s)
{
	this->starRepo.addStar(s);
}

int Service::findStar(std::string name)
{
	return this->starRepo.findStar(name);
	
}

void Service::removeStar(std::string name)
{
	this->starRepo.removeStar(name);
	
	

}

void Service::updateStar(std::string name,Star s) {
	return this->starRepo.updateStar(name,s);
	
}

Star Service::searchStar(std::string name) {
	for (auto elem : this->getStars())
		if (elem.getName() == name)
			return elem;
	return Star();
}

std::vector<Star>Service:: starsConstellation(std::string constellation) {
	std::vector<Star>stars;
	for (auto elem : this->getStars())
		if (elem.getConstellation() == constellation)
			stars.push_back(elem);
	return stars;

}
