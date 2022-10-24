#include"Event.h"
#include "Repository.h"
#include "DynamicVector.h"
#include "Service.h"
#include<assert.h>


void testEvent()
{
	Event e;
	assert(e.getTitle() == "");
	Date d1=Date("01", "01", "2022");
	e = Event("title", "description", d1, "20:30", 200, "link");
	assert(e.getTitle() == "title");
	assert(e.getDescription() == "description");
	assert(e.getTime() == "20:30");
	assert(e.getNrPeople() == 200);
	assert(e.getDate().getDay() == "01");
}

void testDynamicVector()
{
	DynamicVector<Event>v;
	Date d1 = Date("01","01","2022");
	Event e = Event("title", "description", d1, "20:30", 200, "link");
	assert(v.add(e)==1);
	assert(v.getSize() == 1);
	Date d2 = Date("01", "01", "2022");
	Event e1 = Event("tilu", "description", d2, "20:30", 200, "link");
	assert(v.remove(e1) == 0);
	assert(v.update("title", "description", e1)==1);
	assert(v.equal(e1, 0));

}

void testRepository()
{   
	Date d2 = Date("01", "01", "2022");
	Event e = Event("title", "description", d2, "20:30", 200, "link");
	Repository r;
	assert(r.addEvent(e) == 1);
	assert(r.remove("title") == 1);
	assert(r.getSize() == 0);

	Date d1 = Date("01", "01", "2022");
	Event e1= Event("titlu", "description", d1, "20:30", 200, "link");
	assert(r.addEvent(e1)==1);
	assert(r.update("titlu", "description", e)==1);
	assert(r.getElemsRepo()[0].getTitle() == "title");
	
}

/*void testService()
{
	Date d1 = Date("01", "01", "2022");
	Event *e = Event("title", "description", d1, "20:30", 200, "link");
	Repository_file repo;
	EventsList eventslist;
	Service s(repo,eventslist);
	assert(s.addEvent(e) == 1);
	assert(s.remove("title") == 1);
	assert(s.getSizeRepo() == 0);
	Event e1 = Event("titlu", "description", d1, "20:30", 200, "link");
	assert(s.addEvent(e1) == 1);
	assert(s.update("titlu", "description", e) == 1);
	assert(s.getElemsRepo()[0].getTitle() == "title");
	Date d6 = Date("09", "04", "2022");
	Event e6 = Event("Save the children", "volunteering activity", d6, "20:35", 900, "http:save-the-children");
	s.addEventList(e6);
	Date d5 = Date("01", "03", "2022");
	Event e5 = Event("Treasure hunt", "students", d5, "20:45", 200, "https");
	s.addEventList(e5);
	Date d4 = Date("05", "04", "2022");
	Event e4 = Event("Treasure hunt", "students", d4, "20:45", 200, "https");
	assert(s.addEventList(e4)==1);
	s.sortCronologically();
	assert(s.getElems()[1].getDate().getDay() == "05");
	Event list[3];
	//int len = s.eventsMonth("04");
	//assert(len == 2);
	assert(list[1].getDescription() == "students");
	assert(s.removeEventList(e4.getTitle()) == 1);
	
}*/

void testAll()
{
	testEvent();
	testDynamicVector();
	testRepository();
}



