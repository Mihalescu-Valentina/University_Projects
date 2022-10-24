#pragma once
#include "Topic.h"
#include<vector>
class TopicRepo {

private:
	std::string filename;
	std::vector<Topic> topics;

public:
	TopicRepo(std::string& filename);
	std::vector<Topic> getTopics() { return this->topics; };
	void readFromFile();
	void writeToFile();
	int findTopic(std::string topic);
	~TopicRepo();

	void setTopic(std::string newtopic);

	std::vector<Topic> getSortedTopics();
	//void addTopic(std::string topic,std::string users);
	//void removeTopic(std::string topic);

	//void updateTask(int index, Topic t);


};