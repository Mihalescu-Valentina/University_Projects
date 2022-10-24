#include "Post.h"
#include <vector>

Post::Post() : id{ 0 }, text{ "" }, time{ " " },user{" "}
{
}

Post::Post(int _id, std::string _text, std::string _time,std::string _user) : id{_id}, text{_text}, time{_time},user{_user}
{
}

Post::~Post()
{
}

void Post::setText(std::string text)
{
	this->text = text;
}



std::vector<std::string> tokenize2(std::string str, char delimiter)
{
	std::vector <std::string> result;
	std::stringstream ss(str);
	std::string token;
	while (getline(ss, token, delimiter))
		result.push_back(token);

	return result;
}

std::istream& operator>>(std::istream& is, Post& elem)
{

	std::string line;
	getline(is, line);
	std::vector<std::string> tokens = tokenize2(line, ',');
	if (tokens.size() != 4)
		return is;
	elem.id = stoi(tokens[0]);
	elem.text = tokens[1];
	elem.time = tokens[2];
	elem.user = tokens[3];


	return is;
}

std::ostream& operator<<(std::ostream& os,Post& t)
{
	os << t.getId() << "," << t.getText() << "," << t.getTime() << +","+t.getUser()<<"\n";
	return os;
}


