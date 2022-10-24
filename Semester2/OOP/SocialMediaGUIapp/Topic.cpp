#include "Topic.h"
#include "User.h"
#include <vector>

Topic::Topic() : topic{ " " }, subscribers{" "}
{
}

Topic::Topic(std::string topic, std::string subscribers) : topic{ topic}, subscribers{ subscribers }
{
}

Topic::~Topic()
{
}

void Topic::setTopic(std::string topic)
{
	this->topic = topic;
}



std::vector<std::string> tokenize1(std::string str, char delimiter)
{
	std::vector <std::string> result;
	std::stringstream ss(str);
	std::string token;
	while (getline(ss, token, delimiter))
		result.push_back(token);

	return result;
}

std::istream& operator>>(std::istream& is, Topic& elem)
{

	std::string line;
	getline(is, line);
	std::vector<std::string> tokens = tokenize1(line, ',');
	if (tokens.size() != 2)
		return is;
	elem.topic = tokens[0];
	elem.subscribers = tokens[1];


	return is;
}

std::ostream& operator<<(std::ostream& os, Topic& t)
{
	os << t.getTopic() << "," << t.getSubscribers() << "\n";
	return os;
}


