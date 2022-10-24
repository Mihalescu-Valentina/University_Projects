#include "Repository.h"
#include<iostream>
using namespace std;

//this function adds an event e to the dynamic vector
int Repository::addEvent(Event e)
{   
	return this->elems.add(e);
	//return this->elems + e;
}


//this function removes an event e from the dynamic vector
int Repository::remove(Event e)
{
	return this->elems.remove(e);

}

//this function returns the size of the dynamic vector
int Repository::getSize() const
{
	return this->elems.getSize();
}

//this function returns the dynamic vector
DynamicVector<Event>& Repository::getElemsRepo() {

	return this->elems;
}

//this function updates the dynamic vector
int Repository::update(const std::string& old_title, const std::string& old_descr,Event e)
{
	return this->elems.update(old_title,old_descr,e);
}



