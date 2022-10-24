#pragma once
#include "DynamicVector.h"
class EventsList {

private:
	DynamicVector<Event> events{ 20 };

public:
	void eventsMonth(std::string month, Event list[100]);

	int getSizeList() const;

	DynamicVector<Event>& getElems();
	int addEventList(Event e);

	int removeEventList(Event e);

};