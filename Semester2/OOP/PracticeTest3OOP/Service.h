#pragma once
#include "Task.h"
#include <vector>

class Service {
private:

	std::vector<Task> elems;
	std::string filename;
public:
	explicit Service(std::vector<Task>elems,std::string filename);
	~Service();
	virtual int getSize() const;
	virtual int addTask(Task t);
	virtual std::vector<Task>& getElems();
	void loadFromFile();
	std::vector<Task> filterByPriority(int priority);
	int findTask(std::string description);
	virtual int remove(std::string description);
	int update(std::string description, Task t);



};