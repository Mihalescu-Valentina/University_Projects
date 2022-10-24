#include "Programmer.h"
#include <vector>

Programmer::Programmer(std::string _name, int _id): name{_name},id{_id}
{
}

Programmer::Programmer(): name{" "},id{0}
{
}

Programmer::~Programmer()
{
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

std::istream& operator>>(std::istream& is, Programmer& p)
{
	
        std::string line;
		getline(is, line);
		std::vector<std::string> tokens = tokenize1(line, ',');
		if (tokens.size() != 2) 
			return is;
		p.name = tokens[0];
		p.id = stoi(tokens[1]);
	     
		
		

		return is;
}

