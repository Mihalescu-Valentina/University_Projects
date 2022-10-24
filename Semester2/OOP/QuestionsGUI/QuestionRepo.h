#pragma once
#pragma once
#include "Question.h"
#include<vector>
class QuestionRepo {

private:
	std::string filename;
	std::vector<Question> questions;

public:
	QuestionRepo(std::string& filename);
	std::vector<Question> getQuestions() { return this->questions; };
	~QuestionRepo();
	void readFromFile();

	void writeToFile();

	void addQuestion(int id,std::string description,std::string name);

	int findQuestion(std::string description);

	void removeQuestion(std::string description);


	

};