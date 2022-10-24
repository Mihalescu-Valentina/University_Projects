#pragma once

#include <string>

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
};


class Event
{

private:

	std::string title, description,link,time;
	int nr_people;
	Date date;

public:

	Event(const std::string& title, const std::string& description,const Date& date,const std::string &time,int nr_people, const std::string& link);

	Event();

	Date getDate() const { return date; }
	
	const std::string& getTime() const;

	inline std::string getTitle() const { return this->title; }

	inline std::string getDescription() const { return this->description; }

	inline std::string getLink() const { return this->link; }

	int getNrPeople() ;

	void setNrPeople();

	void play() const;



};

