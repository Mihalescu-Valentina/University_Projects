#pragma once
#include<string>
#include<sstream>
class Post {
private:
	std::string text;
	std::string time;
	std::string user;
	int id;

public:
	Post();
	Post(int _id, std::string text, std::string time,std::string user);
	~Post();
	inline std::string getText() const {
		return this->text;
	}

	inline std::string getTime() const {
		return this->time;
	}


	inline int getId() const {
		return this->id;
	}

	inline std::string getUser()const {
		return this->user;
	}

	void setText(std::string text);

	friend std::istream& operator>>(std::istream& is, Post& a);

	friend std::ostream& operator<<(std::ostream& os, Post& a);



};