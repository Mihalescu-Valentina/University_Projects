#include "Service.h"
#include <cassert>

Service::Service(ProgrammerRepo programmerRepo, TaskRepo taskRepo): programmerRepo{programmerRepo},taskRepo{taskRepo}
{
}

void Service::addTask(std::string description, int id)
{
	this->taskRepo.addTask(description, id);
	this->notify();
}

int Service::findTask(std::string description)
{
	return this->taskRepo.findTask(description);
	
}

void Service::removeTask(std::string description)
{
	this->taskRepo.removeTask(description);
	this->notify();
	

}

void Service::updateTask(int index,Task t) {
	return this->taskRepo.updateTask(index,t);
	this->notify();
}

/// this function tests the removal of a task from the vector of Tasks in the repo
/// void function,it does not return anything
/// it is adding a new task and then testing if the size before the removal and after are different 
/// and if findTask returns 0 after removal meaning the task is not there anymore
void Service::testRemove() {
	this->addTask("creating windows2",200);
	int size = this->getTasks().size();
	this->removeTask("creating windows2");
	assert(this->findTask("creating windows2")==0);
	assert(this->getTasks().size() != size);

}

/// this function tests the update of a task state
/// void function-it does not return anything
/// it adds one new task which by default will have as status open and then after update,it makes an assert for checking if the status is in progress
void Service::testUpdate() {
	this->addTask("creating windows2", 200);
	this->updateTask(0, Task("creating windows2", "open", 200));
	int size = this->getTasks().size();
	assert(this->getTasks()[size - 1].getStatus() == "in progress");
	this->removeTask("creating windows2");

}

 

void Service::testUpdateTask() {

}
