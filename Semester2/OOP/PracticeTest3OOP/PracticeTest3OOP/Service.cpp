#include "Service.h"
#include <fstream>
#include <algorithm>
Service::Service(std::vector<Task> elems, std::string filename):elems{elems},filename{filename}
{
}
Service::~Service() = default;
int Service::getSize() const
{
	return this->elems.size();
}

int Service::addTask(Task elem)
{
	if (count(this->elems.begin(), this->elems.end(), elem))
		return 0;
	else
	{
		this->elems.push_back(elem);
		return 1;

	}

}

int Service::remove(std::string description)
{
	for (auto it = this->elems.begin(); it != this->elems.end(); ++it)
		if (it->getDescription() == description)
		{
			this->elems.erase(it);
			return 1;
		}

	return 0;
	
}

int Service::update(std::string description,Task t)
{
	for (auto& elem : this->elems)
	{
		if (elem.getDescription() == description)
		{
			elem = t;
			return 1;

		}
	}
	return 0;
}

std::vector<Task>& Service::getElems() {

	return this->elems;
}

void Service::loadFromFile() {
	if (!this->filename.empty())
	{
		Task elem;
		std::ifstream fin(this->filename);
		while (fin >> elem)
		{
			if (std::find(this->elems.begin(), this->elems.end(), elem) ==
				this->elems.end())
				this->elems.push_back(elem);
		}
		fin.close();
	}
	std::sort(this->elems.begin(), this->elems.end(), [](const Task task1, const Task task2) {
		return task1.getPriority() < task2.getPriority();
		});
	std::sort(this->elems.begin(), this->elems.end(), [](const Task task1, const Task task2) {
		return task1.getDuration() > task2.getDuration();
		});
}

std::vector<Task> Service::filterByPriority(int priority)
{
	std::vector<Task> elements = this->getElems();
	int count = count_if(elements.begin(), elements.end(), [&priority](const Task& elem) {return elem.getPriority() == priority; });
	std::vector<Task>elements2(count);
	elements2.reserve(count);
	copy_if(elements.begin(), elements.end(), elements2.begin(), [&priority](const Task& event) {return event.getPriority() == priority; });
	return elements2;
}

int Service::findTask(std::string description)
{
	for (auto& e : this->getElems())
		if (e.getDescription() == description)
			return -1;
	return 1;
}


