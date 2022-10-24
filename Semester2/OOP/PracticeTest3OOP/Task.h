#pragma once
#include <string>
class Task {
private:
	std::string description;
	int duration, priority;

public:
	Task(const std::string& description, int duration,int priority);

	Task();
	~Task();

	inline int getDuration() const { return this->duration; }

	inline std::string getDescription() const { return this->description; }

	inline int getPriority() const { return this->priority; };

	bool operator==(const Task& );
	friend std::istream& operator>>(std::istream& is, Task& ti);
	friend std::ostream& operator<<(std::ostream& os, const Task& to);


};