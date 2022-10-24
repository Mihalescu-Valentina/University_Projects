#include "Event.h"
#include <string>
#include<fstream>
#include "EventsList.h"
#include"Validator.h"
#include<vector>
#include<algorithm>
#include<Windows.h>
using namespace std;

//a function used for returning the events from the month month
std::vector<Event> EventsList::eventsMonth(std::string month)
{
    std::vector<Event> months = this->getElems();
    int count = count_if(months.begin(), months.end(), [month](const Event& event) {return event.getDate().getMonth() == month; });
    std::vector<Event>months2(count);
    copy_if(months.begin(), months.end(),months2.begin(), [month](const Event& event) {return event.getDate().getMonth() == month; });
    int i = 0, j = 0;

    return months2;


}

//a function used for returning the size of the list
int EventsList::getSizeList() const
{
    return this->events.size();
}

//a function used for returning the lst of events
std::vector<Event>& EventsList::getElems() {

    return this->events;
}

//a function used for adding an events to a list
int EventsList::addEventList(Event e)
{
    
    if (std::count(this->events.begin(), this->events.end(), e))
        return 0;
    else
    {
        this->events.push_back(e);
        this->writeinfilelist(this->getElems());
        return 1;
    }
}


//a function used for removing an events from a list
int EventsList::removeEventList(std::string title)
{
    for (int i = 0; i < this->events.size(); i++)
        if (this->events[i].getTitle() == title)
        {
            this->events.erase(this->events.begin() + i);
            this->writeinfilelist(this->getElems());
            return 1;
        }

    return 0;
}


EventsListCsv::EventsListCsv()
{
    this->filename = "C:\\Users\\Valentina\\source\\repos\\a8-9-914-Mihalescu-Valentina\\Homework8-9\\EventsList.csv";
}

//the function used for writing the file
void EventsListCsv::writeinfilelist(std::vector<Event> arr)
{
    std::ofstream file(this->filename);
    int index = 0;
    if (!file.is_open())
        return;

    for (auto& e: arr) {
        if (index != 0)
            file << "\n";
        file <<e;
        index++;
    }
    file.close();
}
//the function used for opening the csv file
void EventsListCsv::open(Event e)
{
    system("notepad.exe EventsList.csv");
}

//the name of the html file
EventsListHtml::EventsListHtml()
{
    this->filename = "Events.htm";
}

//function used for writing to the html file
void EventsListHtml::writeinfilelist(std::vector<Event> arr)
{
    std::ofstream file(this->filename);

    if (!file.is_open())
        return;

    file << "<!DOCTYPE html>\n<html>\n<head>\n    <title>EventsList</title>\n</head>";
    file << "<body>\n<table border=\"1\">\n    <tr>\n        <td>Title</td>\n";
    file << "        <td>Description</td>\n        <td>Data</td>\n        <td>Time</td>\n        <td>Nr of people</td>\n   <td>Link</td>\n    </tr>\n";

    for (auto& t : arr) {
        file << "    <tr>\n";
        file << "        <td>" << t.getTitle() << "</td>";
        file << "        <td>" << t.getDescription() << "</td>";
        file << "        <td>" << t.getDate().getDay() << "-" << t.getDate().getMonth() <<"-"<<t.getDate().getYear()<< "</td>";
        file << "        <td>" << t.getTime() << "</td>";
        file << "        <td>" << t.getNrPeople() << "</td>";
        file << "        <td><a href=" << t.getLink() << ">Link</a></td>";
        file << "</tr>";
    }
    file << "</table>\n</body>\n</html>";
    file.close();
}

void EventsListHtml::open(Event e) {
    ShellExecuteA(NULL, NULL, "chrome.exe", "file:///C:/Users/Valentina/source/repos/a8-9-914-Mihalescu-Valentina/Homework8-9/Events.htm",NULL, SW_SHOWMAXIMIZED);

}