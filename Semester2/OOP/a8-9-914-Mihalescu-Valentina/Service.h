#pragma once
#include "Repository.h"
#include "EventsList.h"
#include <string>
#include<vector>
class Service
{
private:
	
	Repository_file* repo;
	EventsList* eventslist;
	
public:
	Service(Repository_file* repository,EventsList* eventslist);
	
	
	int addEvent(Event e);

	int getSizeRepo() const;
	int getSize() const;
	void events(Service&s);

	std::vector<Event> eventsMonth(const std::string& month);

	void sortCronologically();

	std::vector<Event> sortCron();

	int addEventList(Event e);

	int removeEventList(std::string title);

	void read();

	void open(Event e);

	

	std::vector<Event>& getElemsRepo();

	std::vector<Event>& getElems();
	
	int remove(std::string);

	int update(const std::string& old_title, const std::string& old_descr, Event e);



};


