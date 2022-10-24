#pragma once
#include<string>
#include<sstream>
#include "User.h"
#include <vector>
class Topic {
private:
	std::string topic;
	std::string subscribers;
	

public:
	Topic();
	Topic(std::string topic, std::string subscribers);
	~Topic();
	inline std::string getTopic() const {
		return this->topic;
	}

	inline std::string getSubscribers() const {
		return this->subscribers;
	}


	void setTopic(std::string topic);
	

	friend std::istream& operator>>(std::istream& is, Topic& t);

	friend std::ostream& operator<<(std::ostream& os, Topic& t);



};