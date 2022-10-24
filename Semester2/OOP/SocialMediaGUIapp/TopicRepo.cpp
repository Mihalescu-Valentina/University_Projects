#include "TopicRepo.h"
#include <fstream>
#include<algorithm>

TopicRepo::TopicRepo(std::string& filename) {
	this->filename = filename;
	this->readFromFile();
}



void TopicRepo::readFromFile() {

	std::ifstream file(this->filename);
	if (file.is_open() == false)
		return;
	Topic t;
	while (file >> t)
		this->topics.push_back(t);
	file.close();

}


void TopicRepo::writeToFile() {
	std::ofstream file(this->filename);
	if (!file.is_open())
		return;

	for (auto& t : this->topics) {
		file << t;

	}
	file.close();
}

int TopicRepo::findTopic(std::string topic)
{
	for (auto elem : this->topics)
		if (elem.getTopic() == topic)
			return 1;
	return 0;
}

TopicRepo::~TopicRepo()
{

}




	


