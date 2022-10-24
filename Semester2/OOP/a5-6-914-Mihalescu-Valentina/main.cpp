#include "DynamicVector.h"
#include "Event.h"
#include <crtdbg.h>
#include <string>
#include <iostream>
#include <assert.h>
#include"Repository.h"
#include "Service.h"
#include "UI.h"
#include"Tests.h"
#include "EventsList.h"
using namespace std;
int main()
{
	
	Repository repo{};
	EventsList eventslist{};
	Service s{repo,eventslist};
	UI ui{s};
	ui.startUI(s);
	testAll();
	_CrtDumpMemoryLeaks();
	/*Event e = Event("Save the animals", "volunteering activity", "01-02-2022", "20:35", 1100, "http:save-the-animals");
	DynamicVector<Event> dynamic_vector{ 20 };
	dynamic_vector + e;
	for (int i = 0; i < dynamic_vector.getSize(); i++)
		cout << dynamic_vector[i].getTitle() << " " << dynamic_vector[i].getDescription() << " " << dynamic_vector[i].getDate() << " " << dynamic_vector[i].getTime() << " " << dynamic_vector[i].getNrPeople() << " " << dynamic_vector[i].getLink();*/
	
	return 0;
}