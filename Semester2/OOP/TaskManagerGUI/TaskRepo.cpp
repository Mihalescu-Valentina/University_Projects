#include "TaskRepo.h"
#include <fstream>
#include<algorithm>

TaskRepo::TaskRepo(std::string& filename) {
	this->filename = filename;
	this->readFromFile();
}



void TaskRepo::readFromFile() {

	std::ifstream file(this->filename);
	if (file.is_open() == false)
		return;
	Task t;
	while (file >> t)
		this->tasks.push_back(t);
	file.close();

}


void TaskRepo::writeToFile() {
	std::ofstream file(this->filename);
	if (!file.is_open())
		return;

	for (auto& t : this->tasks) {
		file << t;
		
	}
	file.close();
}

int TaskRepo::findTask(std::string description)
{
	for (auto elem : this->tasks)
		if (elem.getDescription() == description)
			return 1;
	return 0;
}

TaskRepo::~TaskRepo()
{
	
}

std::vector<Task> TaskRepo::getSortedTasks() {
	std::vector<Task>tasks;
	for (int i = 0; i < this->getTasks().size(); i++)
		tasks.push_back(this->getTasks()[i]);

	sort(tasks.begin(),tasks.end(), [](Task t1, Task t2) {return t1.getStatus() < t2.getStatus(); });
	return tasks;

}

void TaskRepo::addTask(std::string description,int id) {
	Task t= Task(description,"open", id);
	for (Task elem : this->tasks)
		if (elem.getDescription() == t.getDescription() && elem.getStatus() == "open" && elem.getId() == id)
			return;
	this->tasks.push_back(t);
	this->writeToFile();
	

}

void TaskRepo::removeTask(std::string description)
{
	for (int i = 0; i < this->tasks.size(); i++)
		if (this->tasks[i].getDescription() == description) {
			this->tasks.erase(this->tasks.begin() + i);
			this->writeToFile();
			return ;
		}

}

void TaskRepo::updateTask(int index,Task t) {

	for(int i=0;i<this->tasks.size();i++)
		if (this->tasks[i].getDescription() == t.getDescription() && this->tasks[i].getStatus() == t.getStatus() && this->tasks[i].getId() == t.getId())
		{
			this->tasks[i].setTask("in progress");
		}
			
	
	this->writeToFile();
}


