#include "User.h"
#include <vector>

User::User(std::string _name) : name{ _name }
{
}

User::User() : name{ " " }
{
}

User::~User()
{
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

std::istream& operator>>(std::istream& is, User& u)
{

	std::string line;
	getline(is, line);
	std::vector<std::string> tokens = tokenize(line, ' ');
	if (tokens.size() != 1)
		return is;
	u.name = tokens[0];





	return is;
}

