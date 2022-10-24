#include "Question.h"
#include <vector>

Question::Question() : id{ 0 }, description{ "" }, name{ " " }
{
}

Question::Question(int _id, std::string _descr, std::string _name) : id{ _id }, description{ _descr },name{_name}
{
}

Question::~Question()
{
}

void Question::setDescription(std::string descr)
{
	this->description = descr;
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

std::istream& operator>>(std::istream& is, Question& elem)
{

	std::string line;
	getline(is, line);
	std::vector<std::string> tokens = tokenize1(line, ',');
	if (tokens.size() != 3)
		return is;
	elem.id = stoi(tokens[0]);
	elem.description = tokens[1];
	elem.name = tokens[2];


	return is;
}

std::ostream& operator<<(std::ostream& os, Question& t)
{
	os <<t.getId()<<","<<t.getDescription() << "," << t.getName() << "\n";
	return os;
}


