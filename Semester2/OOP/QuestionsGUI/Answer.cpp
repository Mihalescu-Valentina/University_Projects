#include "Answer.h"
#include <vector>

Answer::Answer() : answerId{ 0 }, questionId{ 0 },name{" "},text{" "},nrVotes{0}
{
}

Answer::Answer(int _aid, int _qid,std::string _name,std::string _text,int _nrVotes) : answerId{ _aid}, questionId{ _qid },name{_name},text{_text},nrVotes{_nrVotes}
{
}

Answer::~Answer()
{
}

void Answer::setQuestionId(int id)
{
	this->questionId = id;
}

void Answer::setAnswerId(int it)
{
	this->answerId = it;
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

std::istream& operator>>(std::istream& is,Answer& elem)
{

	std::string line;
	getline(is, line);
	std::vector<std::string> tokens = tokenize2(line, ',');
	if (tokens.size() != 5)
		return is;
	elem.answerId = stoi(tokens[0]);
	elem.questionId = stoi(tokens[1]);
	elem.name = tokens[2];
	elem.text = tokens[3];
	elem.nrVotes = stoi(tokens[4]);


	return is;
}

std::ostream& operator<<(std::ostream& os, Answer& e)
{
	os << e.getAnswerId() << "," << e.getQuestionId()<<","+e.getName() << "," << e.getText() << "," << e.getNrVotes() << "\n";
	return os;
}


