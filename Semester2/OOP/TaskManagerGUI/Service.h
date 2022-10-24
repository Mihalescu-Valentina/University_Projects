#pragma once
#include "ProgrammerRepo.h"
#include "TaskRepo.h"
#include "Observer.h"

class Service:public Subject {
private:
	ProgrammerRepo programmerRepo;
	TaskRepo taskRepo;

public:
	Service(ProgrammerRepo programmerRepo, TaskRepo taskRepo);
	std::vector<Programmer> getProgrammers() { return this->programmerRepo.getProgrammers(); };
	std::vector<Task> getTasks() { return this->taskRepo.getTasks(); };
	std::vector<Task>getsortedTasks() { return this->taskRepo.getSortedTasks(); };
	void addTask(std::string description,int id);
	int findTask(std::string description);
	void removeTask(std::string description);

	void updateTask(int index,Task t);

	void testRemove();

	void testUpdate();

	void testUpdateTask();


};