#include "Repository.h"
#include "Validator.h"
#include<iostream>
#include<fstream>
using namespace std;


Repository_file::Repository_file() {
	this->filename = "C:\\Users\\Valentina\\source\\repos\\a8-9-914-Mihalescu-Valentina\\Homework8-9\\Events.txt";
}

//this function adds an event e to the dynamic vector
int Repository::addEvent(Event e)
{   
	int ok = 1;
	try {
		EventValidator::validate(e);
	}
	catch (ValidationException& ex)
	{
		std::cout << ex.getMessage() << std::endl;
		ok = 0;
	}
	
	if (std::count(this->elems.begin(), this->elems.end(), e)!=0||ok==0)
		return 0;
	else
	{
		this->elems.push_back(e);
		return 1;
	}

	
}


//this function removes an event e from the dynamic vector
int Repository::remove(std::string title)
{   
	
	for (auto it = this->elems.begin(); it != this->elems.end(); ++it)
		if (it->getTitle()==title)
		{
			this->elems.erase(it);
			return 1;
		}

	return 0;
}



//this function returns the size of the dynamic vector
int Repository::getSize() const
{
	return this->elems.size();
}

//this function returns the dynamic vector
std::vector<Event>& Repository::getElemsRepo() {

	return this->elems;
}

//this function updates the dynamic vector
int Repository::update(const std::string& old_title, const std::string& old_descr,Event e)
{
	int ok = 1;
	try {
		EventValidator::validate(e);
	}
	catch (ValidationException& ex)
	{
		std::cout << ex.getMessage() << std::endl;
		ok = 0;
	}
	
	for (auto& elem : this->elems)
	{
		if (ok == 0)
			return 0;
		if (elem.getTitle() == old_title && elem.getDescription() == old_descr)
		{
			elem = e;
			return 1;

		}
	}
	return 0;
	
	
}


std::vector<Event> Repository_file::readfromfile()
{
	std::ifstream file(this->filename);

	std::vector<Event> arr;
	if (!file.is_open())
		return arr;

	Event e;
	while (file >> e)
		arr.push_back(e);
	//std::cout << arr[0].getTitle();
	file.close();
	return arr;
}

void Repository_file::writeinfile(std::vector<Event> event)
{
	std::ofstream file(this->filename);
	int index = 0;
	if (!file.is_open())
		return;

	for ( auto& e : event) {
		if (index != 0)
			file << "\n";
		file << e;
		index++;
	}
	file.close();
}
