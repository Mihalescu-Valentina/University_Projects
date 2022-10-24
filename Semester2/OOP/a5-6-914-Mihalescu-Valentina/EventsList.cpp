#include "Event.h"
#include <string>
#include "EventsList.h"

//creates a list just with elements of certain months
void EventsList::eventsMonth(std::string month, Event list[100])
{
    int i = 0, j = 0;
    for (i = 0; i < this->events.getSize(); i++)
        if (this->events[i].getDate().getMonth() == month)
        {
            list[j] = this->events[i];
            j++;
        }

}

//returns an integer,the size of the list of the user
int EventsList::getSizeList() const
{
    return this->events.getSize();
}

//returns the array  of events from the users's list
DynamicVector<Event>& EventsList::getElems() {

    return this->events;
}

//adds an event to the list of the user
int EventsList::addEventList(Event e)
{
    return this->events.add(e);
}

//removes an element from the list of the user
int EventsList::removeEventList(Event e)
{
    return this->events.remove(e);
}