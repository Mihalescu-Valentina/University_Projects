#pragma once
#include "Repository.h"
#include "EventsList.h"
#include <string>
class Service
{
private:
	
	Repository repo;
	EventsList eventslist;
	
public:
	Service(Repository repository,EventsList eventslist);
	
	
	int addEvent(Event e);

	int getSizeRepo() const;
	int getSize() const;
	void events(Service&s);

	int eventsMonth(const std::string& month,Event  list [100]);

	void sortCronologically();

	int addEventList(Event e);

	int removeEventList(Event e);

	

	//Service& getService();
	DynamicVector<Event>& getElemsRepo();

	DynamicVector<Event>& getElems();
	
	int remove(Event e);

	int update(const std::string& old_title, const std::string& old_descr, Event e);



};


