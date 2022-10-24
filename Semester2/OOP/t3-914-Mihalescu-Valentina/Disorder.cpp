#include "Disorder.h"
#include <Windows.h>
#include<sstream>
#include<vector>
#include<string>

Disorder::Disorder(const std::string category, std::string name, std::string symptoms) :category{ category }, name{ name }, symptoms{ symptoms }
{
}

Disorder::Disorder() : category{ "" }, name{" "}, symptoms{""}
{
}

Disorder::~Disorder() = default;


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


std::istream& operator>>(std::istream & is, Disorder & elem)
{
	std::string line;
	getline(is, line);
	std::vector<std::string> tokens = tokenize(line, '|');
	if (tokens.size() != 3)
		return is;
	elem.category = tokens[0];
	elem.name= tokens[1];
	elem.symptoms = tokens[2];

	return is;
}

//overloading the <<for writing to a file
std::ostream& operator<<(std::ostream & os, Disorder & elem)
{
	os << elem.getCategory() << "|" << elem.getName() << "|" << elem.getSymptoms() << "\n";
	return os;
}


bool Disorder::operator==(const Disorder & t)
{
	return (this->category == t.getCategory() && this->name == t.getName() && this->symptoms == t.getSymptoms());
}




