#pragma once
#include<vector>
#include "Answer.h"
class AnswerRepo {

private:
	std::string filename;
	std::vector<Answer> answers;

public:
	AnswerRepo(std::string& filename);
	std::vector<Answer> getAnswers() { return this->answers; };
	int getSizeAnswer() {
		return this->answers.size();
	}
	~AnswerRepo();
	void addAnswer(Answer a);
	void readFromFile();
	void writeToFile();

};