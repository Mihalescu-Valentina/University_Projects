#include "Service.h"
#include <algorithm>

Service::Service(UserRepo& userRepo,QuestionRepo& questionRepo, AnswerRepo& answerRepo) : userRepo{ userRepo },questionRepo{questionRepo}, answerRepo{ answerRepo }
{
}



int Service::getAnswersNr(Question q) {
	int nr = 0,j=0;
	for (j = 0; j < this->getAnswers().size(); j++)
		if (this->getAnswers()[j].getQuestionId() == q.getId())
			nr++;
	return nr;

}


std::vector<Answer> Service::getMostVoted(Question q) {
	std::vector<Answer> votedAnswers;
	for (auto elem : this->getAnswers())
		if (elem.getQuestionId() == q.getId())
			votedAnswers.push_back(elem);

	sort(votedAnswers.begin(), votedAnswers.end(), [this](Answer a1, Answer a2) {return a1.getNrVotes() > a2.getNrVotes(); });
	return votedAnswers;

}

std::vector<Question> Service::getSortedQuestions() {
	std::vector<Question>questions;
	for (int i = 0; i < this->getQuestions().size(); i++)
		questions.push_back(this->getQuestions()[i]);

	sort(questions.begin(), questions.end(), [this](Question q1, Question q2) {return this->getAnswersNr(q1) > this->getAnswersNr(q2); });
	return questions;

}

Question Service::Search(std::string name) {
	for (auto elem : this->getQuestions())
		if (elem.getDescription() == name)
			return elem;
	return Question();
}


void Service::addQuestion(int id,std::string description, std::string name)
{
	this->questionRepo.addQuestion(id,description,name);
	this->notify();
}

std::vector<Answer> Service::showAnswers(Question q) {

	std::vector<Answer> answers;
	for (auto elem : this->getAnswers())
		if (elem.getQuestionId() == q.getId())
			answers.push_back(elem);
	//this->notify();
	return answers;
	
}

void Service::addAnswer(Answer a)
{
	this->answerRepo.addAnswer(a);
	this->notify();
}

int Service::findQuestion(std::string description)
{
	return this->questionRepo.findQuestion(description);

}

void Service::removeQuestion(std::string description)
{
	this->questionRepo.removeQuestion(description);
	this->notify();


}
/*
void Service::updateTask(int index, Task t) {
	return this->taskRepo.updateTask(index, t);
	this->notify();
}
*/