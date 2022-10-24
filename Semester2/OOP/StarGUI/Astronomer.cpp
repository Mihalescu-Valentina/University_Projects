#include "Astronomer.h"
#include <vector>

Astronomer::Astronomer(std::string _name, std::string _constellation): name{_name},constellation{_constellation}
{
}

Astronomer::Astronomer(): name{" "},constellation{""}
{
}

Astronomer::~Astronomer()
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

std::istream& operator>>(std::istream& is, Astronomer& a)
{
	
        std::string line;
		getline(is, line);
		std::vector<std::string> tokens = tokenize1(line, ',');
		if (tokens.size() != 2) 
			return is;
		a.name = tokens[0];
		a.constellation = tokens[1];
	     
		
		

		return is;
}

