#include "Service.h"
#include<iostream>
using namespace std;
Service::Service(Repository repository,EventsList eventslist): repo{ repository },eventslist{eventslist}
{}

//this function adds an event to the dynamic vector 
int Service::addEvent(Event e)
{
    return this->repo.addEvent(e);
}

//the function returns the size of the dynamic vector
int Service::getSizeRepo() const
{
    return this->repo.getSize();
}

int Service::getSize() const
{
    return this->eventslist.getSizeList();
}



/*Service& Service::getService()
{
    return *this;
}*/

//this function return the dynamic vector as a reference
DynamicVector<Event>& Service::getElemsRepo()
{
    return this->repo.getElemsRepo();
}

DynamicVector <Event>& Service::getElems()
{
    return this->eventslist.getElems();
}

//this function removes the the event e from the dynamic vector
int Service::remove(Event e)
{
    return this->repo.remove(e);
}

//the function updates the dynamic vector
int Service::update(const std::string& old_title, const std::string& old_descr, Event e)
{
    return this->repo.update(old_title,old_descr,e);
}

//this function adds 5 events to the dynamic vector
void Service::events(Service &s)
{   
    Date d1 = Date("01", "01", "2022");
    Event e1 = Event("Title", "description", d1, "20:30", 100, "https://www.linkedin.com/home/?originalSubdomain=ro");
    s.addEvent(e1);
    Date d2 = Date("12", "04", "2023");
    Event e2= Event("Disneyland tour", "nostalgia", d2, "20:45", 2500, "https://disneyland.disney.go.com/");
    s.addEvent(e2);
    Date d3=Date("01","01","2023");
    Event e3= Event("BMTH tour","European tour",d3,"21:00",9000, "https://www.bmthofficial.com/live/");
    s.addEvent(e3);
    Date d4 = Date("12", "02", "2022");
    Event e4 = Event("LM5 tour", "concert", d4, "20:30", 1000, "https://www.little-mix.com/events/");
    s.addEvent(e4);
    Date d5 = Date("09","04","2022");
    Event e5 = Event("Treasure hunt", "students", d5 ,"20:45", 200, "https://www.thespruce.com/indoor-treasure-hunt-for-children-1695332");
    s.addEvent(e5);
    Date d6 = Date("01", "02", "2022");
    Event e6 = Event("Save the children", "volunteering activity", d6, "20:35", 900, "https://www.savethechildren.org/");
    s.addEvent(e6);
    Date d7 = Date("05", "08", "2022");
    Event e7 = Event("Olivia Rodrigo tour", "concert", d7, "21:00",10000, "https://www.ticketmaster.com/olivia-rodrigo-tickets/artist/2836194");
    Date d8 = Date("01", "11", "2021");
    Event e8 = Event("Google code", "Jam", d8, "20:37", 9000, "https://codingcompetitions.withgoogle.com/codejam");
    s.addEvent(e8);
    Date d9 = Date("09","09","2022");
    Event e9=Event("Untold","concert",d9,"20:09",100000, "https://untold.com/");
    s.addEvent(e9);
    Date d10 = Date("08", "07", "2023");
    Event e10 = Event("Neversea", "concert", d10, "10:45", 670, "https://neversea.com/");
    s.addEvent(e10);
}

//returns a list with the events having their month equal to month(the given string)
int Service::eventsMonth(const std::string& month,Event list[100])
{
    int i = 0, j = 0;
    for (i = 0; i < this->repo.getElemsRepo().getSize(); i++)
        if (this->repo.getElemsRepo()[i].getDate().getMonth() == month)
        {
            list[j] = this->repo.getElemsRepo()[i];
            j++;
        }
    return j;
}

void swap(Event &a, Event &b)
{
    Event temp = a;
    a = b;
    b = temp;
}

//a function that sorts the events cronologically
void Service::sortCronologically()
{
    
    int i, j;
    bool swapped;
    for (i = 0; i < this->repo.getSize(); i++)
    {
        swapped = false;
        for (j = 0; j < this->repo.getSize() - i - 1; j++)
        {
            if (this->repo.getElemsRepo()[j].getDate() > this->repo.getElemsRepo()[j + 1].getDate())
            {
                swap(this->repo.getElemsRepo()[j], this->repo.getElemsRepo()[j + 1]);
                swapped = true;
            }
        }

        // IF no two elements were swapped by inner loop, then break
        if (swapped == false)
            break;
    }
}

//a function that adds an event to the list of the user
int Service::addEventList(Event e)
{
    return this->eventslist.addEventList(e);
}

//a function that removes an element from the list of the user
int Service::removeEventList(Event e)
{
    return this->eventslist.removeEventList(e);
}



