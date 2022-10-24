#include "AnswerRepo.h"
#include <fstream>

AnswerRepo::AnswerRepo(std::string& _filename) {
	this->filename = _filename;
	this->readFromFile();
}


AnswerRepo::~AnswerRepo()
{
}

void AnswerRepo::addAnswer(Answer a)
{
	for (auto elem : this->answers)
		if (elem.getText() == a.getText())
			return;
	this->answers.push_back(a);
	this->writeToFile();
}

void AnswerRepo::readFromFile() {

	std::ifstream file(this->filename);
	if (file.is_open() == false)
		return;
	Answer p;
	while (file >> p)
		this->answers.push_back(p);
	file.close();

}

void AnswerRepo::writeToFile() {
	std::ofstream file(this->filename);
	if (!file.is_open())
		return;

	for (auto& t : this->answers) {
		file << t;

	}
	file.close();
}