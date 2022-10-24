#include "Star.h"
#include <vector>

Star::Star(): name{" "},constellation{" "},ra{0},dec{0},diameter{0}
{
}

Star::Star(std::string _name, std::string _constellation,int _ra,int _dec,int _diameter): name{_name},constellation{_constellation},ra{_ra},dec{_dec},diameter{_diameter}
{
}

Star::~Star()
{
}

void Star::setName(std::string name)
{
	this->name = name;
}

void Star::setDiameter(int diameter)
{
	this->diameter = diameter;
}

void Star::setRa(int ra)
{
	this->ra = ra;
}

void Star::setDec(int dec)
{
	this->dec = dec;
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

std::istream& operator>>(std::istream& is, Star& elem)
{

	std::string line;
	getline(is, line);
	std::vector<std::string> tokens = tokenize(line, ',');
	if (tokens.size() != 5)
		return is;
	elem.name = tokens[0];
	elem.constellation = tokens[1];
	elem.ra = stoi(tokens[2]);
	elem.dec = stoi(tokens[3]);
	elem.diameter = stoi(tokens[4]);


	return is;
}

std::ostream& operator<<(std::ostream& os, Star& s)
{
	os << s.getName() << "," << s.getConstellation() << "," << s.getRa() <<","<<s.getDec()<<","<<s.getDiameter()<< "\n";
	return os;
}


