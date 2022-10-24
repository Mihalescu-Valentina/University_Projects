#include "Service.h"
#include<iostream>
#include<algorithm>
#include<iterator>
using namespace std;
Service::Service(Repository_file* repository,EventsList *eventslist): repo{ repository },eventslist{eventslist}
{}

//this function adds an event to the dynamic vector 
int Service::addEvent(Event e)
{
    return this->repo->addEvent(e);
}

//the function returns the size of the dynamic vector
int Service::getSizeRepo() const
{
    return this->repo->getSize();
}

int Service::getSize() const
{
    return this->eventslist->getSizeList();
}




//this function return the dynamic vector as a reference
std::vector<Event>& Service::getElemsRepo()
{
    return this->repo->getElemsRepo();
}

std::vector <Event>& Service::getElems()
{
    return this->eventslist->getElems();
}

//this function removes the the event e from the dynamic vector
int Service::remove(std::string title)
{
    return this->repo->remove(title);
}

//the function updates the dynamic vector
int Service::update(const std::string& old_title, const std::string& old_descr, Event e)
{
    return this->repo->update(old_title,old_descr,e);
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
}


std::vector<Event> Service::eventsMonth(const std::string& month)
{
    
    /*int i = 0, j = 0;
    for(auto elem:this->getElemsRepo())
        if (elem.getDate().getMonth() == month)
        {
            list[j] = elem;
            j++;
        }*/
    std::vector<Event> months = this->getElemsRepo();
    int count = count_if(months.begin(), months.end(), [&month](const Event& event) {return event.getDate().getMonth() == month; });
    std::vector<Event>months2(count);
    copy_if(months.begin(), months.end(), months2.begin(), [&month](const Event& event) {return event.getDate().getMonth() == month; });
    return months2;
}

void swap(Event &a, Event &b)
{
    Event temp = a;
    a = b;
    b = temp;
}

void Service::sortCronologically()
{
    
    int i, j;
    bool swapped;
    for (i = 0; i < this->repo->getSize(); i++)
    {
        swapped = false;
        for (j = 0; j < this->repo->getSize() - i - 1; j++)
        {
            if (this->repo->getElemsRepo()[j].getDate() > this->repo->getElemsRepo()[j + 1].getDate())
            {
                swap(this->repo->getElemsRepo()[j], this->repo->getElemsRepo()[j + 1]);
                swapped = true;
            }
        }

        // IF no two elements were swapped by inner loop, then break
        if (swapped == false)
            break;
    }
}

vector<Event> Service::sortCron()
{   
    vector<Event> v = this->getElemsRepo();

    sort(v.begin(), v.end(), [](const Event& e1, const Event& e2) { return e1.getDate() > e2.getDate(); });
   

    return v;
}

int Service::addEventList(Event e)
{
    return this->eventslist->addEventList(e);
}

int Service::removeEventList(std::string title)
{
    return this->eventslist->removeEventList(title);
}

void Service::read()
{
    this->repo->getElemsRepo() = this->repo->readfromfile();
}

void Service::open(Event e)
{
    this->eventslist->open(e);
}

int Service::findEventList(string title, string description)
{
    for (auto& e : this->getElems())
        if (e.getTitle() == title && e.getDescription() == description)
            return -1;
    return 1;
}

int Service::findEventRepo(string title, string description)
{
    for (auto& e : this->getElemsRepo())
        if (e.getTitle() == title && e.getDescription() == description)
            return -1;
    return 1;
}
