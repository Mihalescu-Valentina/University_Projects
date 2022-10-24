#pragma once
#include "Task.h"
#include<vector>
class TaskRepo {

private:
	std::string filename;
	std::vector<Task> tasks;

public:
	TaskRepo(std::string& filename);
	std::vector<Task> getTasks() { return this->tasks; };
	void readFromFile();
	void writeToFile();
	int findTask(std::string description);
	~TaskRepo();

	std::vector<Task> getSortedTasks();
	void addTask(std::string description, int id);
	void removeTask(std::string description);

	void updateTask(int index,Task t);
	

};