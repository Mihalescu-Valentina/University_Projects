#include "QuestionRepo.h"
#include <fstream>
#include <algorithm>

QuestionRepo::QuestionRepo(std::string& _filename) {
	this->filename = _filename;
	this->readFromFile();
}


QuestionRepo::~QuestionRepo()
{
}

void QuestionRepo::readFromFile() {

	std::ifstream file(this->filename);
	if (file.is_open() == false)
		return;
	Question p;
	while (file >> p)
		this->questions.push_back(p);
	file.close();

}

void QuestionRepo::writeToFile() {
	std::ofstream file(this->filename);
	if (!file.is_open())
		return;

	for (auto& t : this->questions) {
		file << t;

	}
	file.close();
}

void QuestionRepo::addQuestion(int id,std::string description,std::string name) {
	 Question q = Question(id,description,name);
	this->questions.push_back(q);
	this->writeToFile();
}

int QuestionRepo::findQuestion(std::string description)
{
	for (auto elem : this->questions)
		if (elem.getDescription() == description)
			return 1;
	return 0;
}

void  QuestionRepo::removeQuestion(std::string description) {
	for (int i = 0; i < this->questions.size(); i++)
		if (this->questions[i].getDescription() == description) {
			this->questions.erase(this->questions.begin() + i);
			this->writeToFile();
			return;
		}

}