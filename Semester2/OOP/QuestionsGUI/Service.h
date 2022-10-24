#pragma once
#include "UserRepo.h"
#include "AnswerRepo.h"
#include "QuestionRepo.h"
#include "Observer.h"

class Service :public Subject {
private:
	UserRepo userRepo;
	AnswerRepo answerRepo;
	QuestionRepo questionRepo;

public:
	Service(UserRepo& userRepo, QuestionRepo& Repo,AnswerRepo& answerRepo);
	int getAnswersNr(Question q);
	std::vector<Answer> getMostVoted(Question q);
	std::vector<Question> getSortedQuestions();
	Question Search(std::string name);
	void addQuestion(int id, std::string description, std::string name);
	std::vector<Answer> showAnswers(Question q);
	void addAnswer(Answer a);
	int findQuestion(std::string description);
	void removeQuestion(std::string description);
	std::vector<User> getUsers() { return this->userRepo.getUsers(); };
	std::vector<Question> getQuestions() { return this->questionRepo.getQuestions(); };
	std::vector<Answer>getAnswers() { return this->answerRepo.getAnswers(); };
	int getSizeAnswer() {
		return this->answerRepo.getSizeAnswer();
	}
	


};
