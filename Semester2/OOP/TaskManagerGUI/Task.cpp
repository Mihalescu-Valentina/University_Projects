#include "Task.h"
#include <vector>

Task::Task(): description{" "},status{" "},id{0}
{
}

Task::Task(std::string _description, std::string _status,int _id): description{_description},status{_status},id{_id}
{
}

Task::~Task()
{
}

void Task::setTask(std::string status)
{
	this->status = status;
}

void Task::setDescription(std::string description)
{
	this->description = description;
}

std::vector<std::string> tokenize(std::string str, char delimiter)
{
	std::vector <std::string> result;
	std::stringstream ss(str);
	std::string token;
	while (getline(ss, token, delimiter))
		result.push_back(token);

	return result;
}

std::istream& operator>>(std::istream& is, Task& elem)
{

	std::string line;
	getline(is, line);
	std::vector<std::string> tokens = tokenize(line, ',');
	if (tokens.size() != 3)
		return is;
	elem.description = tokens[0];
	elem.status = tokens[1];
	elem.id = stoi(tokens[2]);


	return is;
}

std::ostream& operator<<(std::ostream& os, Task& t)
{
	os << t.getDescription() << "," << t.getStatus() << "," << t.getId()<<"\n";
	return os;
}


