#pragma once
#include "DynamicVector.h"
#include <vector>
class EventsList {

private:
	std::vector<Event> events;
public:
	std::vector<Event> eventsMonth(std::string month);

	int getSizeList() const;

	std::vector<Event>& getElems();
	int addEventList(Event e);

	int removeEventList(std::string title);
	virtual void writeinfilelist(std::vector<Event> arr){};
	virtual void open(Event e){};


};

class EventsListCsv :public EventsList
{
protected:
	std::string filename;
public:
	///create the file repository
	EventsListCsv();
	///write the tutorials in a file
	void writeinfilelist(std::vector<Event> arr) override;
	///read the tutorials from a file
	void open(Event e) override;
};

class EventsListHtml :public EventsList
{
protected:
	std::string filename;
public:
	///create the file repository
	EventsListHtml();
	///write the tutorials in a file
	void writeinfilelist(std::vector<Event> arr) override;
	void open(Event e) override;
	///read the tutorials from a file

};

