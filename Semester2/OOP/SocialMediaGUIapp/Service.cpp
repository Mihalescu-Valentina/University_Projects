#include "Service.h"
#include <algorithm>

Service::Service(UserRepo& userRepo, TopicRepo& topicRepo, PostRepo& postRepo) : userRepo{ userRepo }, topicRepo{ topicRepo }, postRepo{ postRepo }
{
}


void Service::updatePost(std::string oldtext, std::string newtext ) {
	this->postRepo.updatePost(oldtext, newtext);
	this->notify();

}



void Service::addPost(int id, std::string text, std::string time,std::string user)
{
	this->postRepo.addPost(id, text, time,user);
	this->notify();
}




int Service::findPost(std::string text)
{
	return this->postRepo.findPost(text);

}

void Service::writeToFile() {
	this->topicRepo.writeToFile();
}

