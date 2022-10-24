#include "Event.h"
#include <Windows.h>

Event::Event(const std::string& title, const std::string& description, const Date& date, const std::string& time, int nr_people, const std::string& link) :title{ title }, description{ description }, date{ date }, time{ time }, nr_people{ nr_people }, link{ link }
{
} //not a copy constructor,just a constructor because e have no dinamically allocated memory so the default one is enough

Event::Event() : title{ "" }, description{ "" }, date{Date()}, time{""}, nr_people{0}, link{""}
{
}  




//a getter for the time of the event
const std::string& Event::getTime() const
{
	return this->time;
}

//a getter for the number of people at the event
int Event::getNrPeople() 
{
	return this->nr_people;
}

void Event::setNrPeople()
{
	this->nr_people = this->nr_people + 1;
}

bool Date::operator==(const Date& d)
{
	return (this->day == d.day && this->month == d.month && this->year == d.year);

}

bool Date::operator>(const Date& d)
{
	if (this->year > d.getYear())
		return true;
	else
		if (this->year == d.getYear() && this->month > d.getMonth())
			return true;
		else
			if (this->year == d.getYear() && this->month > d.getMonth() && this->day > d.getDay())
				return true;
	return false;
}

void Event::play() const
{
	ShellExecuteA(NULL, NULL, "chrome.exe", this->getLink().c_str(), NULL, SW_SHOWMAXIMIZED);
}