#pragma once
#include "Service.h"
class UI
{
private:
	Service& s;

public:
	UI(Service& s);
	void startUI(Service &s);
	int readOption();
	Event read();
	void addEventUI(Service &s);
	void removeEventUI(Service& s);
	void updateEventUI(Service& s);
	void printAllEvents(Service &s);

	void printEventsMonth(Event list[100], const int& length);

	void printEventsList(Service& s);

	

};
