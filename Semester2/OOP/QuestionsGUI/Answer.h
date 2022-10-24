#pragma once
#include<string>
#include<sstream>
class Answer {
private:
	int answerId,questionId,nrVotes;
	std::string name,text;

public:
	Answer();
	Answer(int _aId,int _qId,std::string _name,std::string _text,int _nrVotes);
	void setQuestionId(int id);
	void setAnswerId(int it);
	~Answer();
	inline int getAnswerId() const {
		return this->answerId;
	}

	inline int getQuestionId() const {
		return this->questionId;
	}

	inline int getNrVotes() const {
		return this->nrVotes;
	}

	inline std::string getText() const {
		return this->text;
	}

	inline std::string getName() const {
		return this->name;
	}

	inline void setNrVotes(int nrVotes) {
		this->nrVotes = nrVotes;
	}

	friend std::istream& operator>>(std::istream& is, Answer& a);

	friend std::ostream& operator<<(std::ostream& os, Answer& a);



};