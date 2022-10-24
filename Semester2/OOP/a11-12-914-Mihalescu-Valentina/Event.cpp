#include "Event.h"
#include <Windows.h>
#include<sstream>
#include<vector>
#include<string>
using namespace std;

Event::Event(const std::string& title, const std::string& description, const Date& date, const std::string& time, intmax_t nr_people, const std::string& link) :title{ title }, description{ description }, date{ date }, time{ time }, nr_people{ nr_people }, link{ link }
{
} //not a copy constructor,just a constructor because e has no dinamically allocated memory so the default one is enough

Event::Event() : title{ "" }, description{ "" }, date{Date()}, time{""}, nr_people{0}, link{""}
{
}  

//a function used for tokenizing the input

vector<std::string> tokenize(std::string str, char delimiter)
{
	vector <std::string> result;
	stringstream ss(str);
	string token;
	while (getline(ss, token, delimiter))
		result.push_back(token);

	return result;
}

//overloading the >>operator for reading from a file
std::istream& operator>>(std::istream& is, Event& s)
{
	string line;
	getline(is, line);

	vector<string> tokens = tokenize(line, ',');
	if (tokens.size() != 8) // make sure all the starship data was valid
		return is;
	s.title = tokens[0];
	s.description = tokens[1];
	s.date = Date(tokens[2], tokens[3], tokens[4]);
	s.time = tokens[5];
	s.setNrPeople(stoi(tokens[6]));
	s.link = tokens[7];

	return is;
}

//overloading the <<for writing to a file
std::ostream& operator<<(std::ostream& os, Event& elem)
{
	os << elem.getTitle() << " " << elem.getDescription() << " " << elem.getDate().getDay() << "-" << elem.getDate().getMonth() << "-" << elem.getDate().getYear() << " " << elem.getTime() << " " << elem.getNrPeople() << " " << elem.getLink() << "\n";
	return os;
}



//a getter for the time of the event
std::string Event::getTime() const
{
	return this->time;
}



//a function that increments the number of people
void Event::incrementNrPeople()
{
	this->nr_people = this->nr_people + 1;
}

//a function that sets the number of people to nr
void Event::setNrPeople(intmax_t nr)
{
	this->nr_people = nr;
}

//overloading operator for == for a date
bool Date::operator==(const Date& d)
{
	return (this->day == d.day && this->month == d.month && this->year == d.year);

}
//overloading operator for an Event
bool Event::operator==(const Event& e)
{
	return (this->title == e.getTitle() && this->description == e.getDescription() && this->date == e.getDate() && this->time == e.getTime() && this->link == e.getLink());
}

//overloading the > operator for a date
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

int Date::compareDay(std::string day)
{
	if (this->getDay() <= day)
		return 1;
	return 0;
}

//function used for comparing 2 months
int Date::compareMonth(const string& month)
{
	if (this->getMonth() <= month)
		return 1;
	return 0;
}

//function used for comparing the years
int Date::compareYear(const string& year)
{
	if (this->getYear() <= year)
		return 1;
	return 0;
}


//function used for opening the html file
void Event::play() const
{
	ShellExecuteA(NULL, NULL, "chrome.exe", this->getLink().c_str(), NULL, SW_SHOWMAXIMIZED);
}


