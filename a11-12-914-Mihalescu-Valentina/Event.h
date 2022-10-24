#pragma once
#include <string>
#include<fstream>

class Date
{
private:
	std::string day,month,year;
	
public:
	Date() : day(""), month(""),year("") {}
	Date(std::string day, std::string month, std:: string year) : day(day), month(month),year(year) {}

	std::string getDay() const { return day; }
	std::string getMonth() const { return month; }
	std::string getYear() const { return year; }
	bool operator==(const Date& d);
	bool operator>(const Date& d);
	int compareDay(std::string day);
	int compareMonth(const std::string& month);
	int compareYear(const std::string& year);
	
};


class Event
{

private:

	std::string title, description,link,time;
	intmax_t nr_people;
	Date date;

public:

	Event(const std::string& title, const std::string& description,const Date& date,const std::string &time,std::intmax_t nr_people, const std::string& link);

	Event();

	Date getDate() const { return date; }
	
	std::string getTime() const;

	inline std::string getTitle() const { return this->title; }

	inline std::string getDescription() const { return this->description; }

	inline std::string getLink() const { return this->link; }

	inline intmax_t getNrPeople() { return this->nr_people; };

	void incrementNrPeople();

	void setNrPeople(intmax_t nr);

	bool operator==(const Event& e);

	void play() const;
	friend std::istream& operator>>(std::istream& is, Event& s);
	friend std::ostream& operator<<(std::ostream& os, Event& e);



};

