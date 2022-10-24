#include "Service.h"
#include <fstream>
#include <algorithm>
Service::Service(std::vector<Disorder> elems, std::string filename) :elems{ elems }, filename{ filename }
{
}
Service::~Service() = default;
int Service::getSize() const
{
	return this->elems.size();
}


std::vector<Disorder>& Service::getElems() {

	return this->elems;
}

void Service::loadFromFile() {
	if (!this->filename.empty())
	{
		Disorder elem;
		std::ifstream fin(this->filename);
		while (fin >> elem)
		{
			if (std::find(this->elems.begin(), this->elems.end(), elem) ==
				this->elems.end())
				this->elems.push_back(elem);
		}
		fin.close();
	}
	std::sort(this->elems.begin(), this->elems.end(), [](const Disorder dis1, const Disorder dis2) {
		return dis1.getName() < dis2.getName();
		});
	
}

std::vector<Disorder> Service::filterByDisorder(std::string name)
{
	std::vector<Disorder> elements = this->getElems();
	int count = count_if(elements.begin(), elements.end(), [&name](const Disorder& elem) {return elem.getName() == name; });
	std::vector<Disorder>elements2(count);
	elements2.reserve(count);
	copy_if(elements.begin(), elements.end(), elements2.begin(), [&name](const Disorder& event) {return event.getName() == name; });
	return elements2;
}

int Service::findDisorder(std::string name)
{
	for (auto& e : this->getElems())
		if (e.getName() == name)
			return -1;
	return 1;
}

std::vector<Disorder> Service::match(std::string match) {
	std::vector<Disorder> found;
	for (auto item :this->getElems()) {
		if (item.getSymptoms().find(match) != std::string::npos || item.getSymptoms().find(match) != std::string::npos)
			found.push_back(item);
	}
	return found;
}


