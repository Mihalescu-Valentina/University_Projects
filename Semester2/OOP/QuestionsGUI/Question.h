#pragma once
#include<string>
#include<sstream>
class Question {
private:
	std::string description;
	std::string name;
	int id;

public:
	Question();
	Question(int _id,std::string description,std::string name);
	~Question();
	inline std::string getDescription() const {
		return this->description;
	}

	inline std::string getName() const {
		return this->name;
	}


	inline int getId() const {
		return this->id;
	}


	void setDescription(std::string description);

	friend std::istream& operator>>(std::istream& is, Question& a);

	friend std::ostream& operator<<(std::ostream& os, Question& a);



};