#pragma once
#include "UserRepo.h"
#include "TopicRepo.h"
#include "PostRepo.h"
#include "Observer.h"

class Service :public Subject {
private:
	UserRepo userRepo;
	TopicRepo topicRepo;
	PostRepo postRepo;

public:
	Service(UserRepo& userRepo, TopicRepo& topicRepo, PostRepo& postRepo);
	void updatePost(std::string oldtext, std::string newtext);
	void addPost(int id, std::string text, std::string time, std::string user);
	void setTopic(std::string topicold, std::string topicnew);
	
	int findPost(std::string text);
	void writeToFile();
	std::vector<User> getUsers() { return this->userRepo.getUsers(); }
	std::vector<Post>getPosts() { return this->postRepo.getPosts(); }
	std::vector<Topic>getTopics() { return this->topicRepo.getTopics(); }
	

};
