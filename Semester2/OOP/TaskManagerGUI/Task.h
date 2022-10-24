#pragma once
#include<string>
#include<sstream>
class Task {
private:
	std::string description;
	std::string status;
	int id;

public:
	Task();
	Task(std::string _description, std::string _status,int _id);
	~Task();
	inline std::string getDescription() const {
		return this->description;
	}

	inline std::string getStatus() const {
		return this->status;
	}
	

	inline int getId() const {
		return this->id;
	}

	void setTask(std::string status);
	void setDescription(std::string description);

	friend std::istream& operator>>(std::istream& is, Task& t);

	friend std::ostream& operator<<(std::ostream& os, Task& t);

	

};