#include "Task.h"
#include <Windows.h>
#include<sstream>
#include<vector>
#include<string>

Task::Task(const std::string& description, int duration, int priority) :description{ description }, duration{ duration }, priority{ priority }
{
} 

Task::Task() : description{ "" }, duration{ 0 }, priority{ 0 }
{
}

Task::~Task() = default;

//a function used for tokenizing the input

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
    std::vector<std::string> tokens = tokenize(line, '|');
	if (tokens.size() != 3)
		return is;
	elem.description = tokens[0];
	elem.duration = stoi(tokens[1]);
	elem.priority = stoi(tokens[2]);

	return is;
}

//overloading the <<for writing to a file
std::ostream& operator<<(std::ostream& os, Task& elem)
{
	os << elem.getDescription() << "|" << elem.getDuration() << "|" << elem.getPriority() << "\n";
	return os;
}


bool Task::operator==(const Task& t)
{
	return (this->description == t.getDescription() && this->duration == t.getDuration() && this->priority == t.getPriority());
}




