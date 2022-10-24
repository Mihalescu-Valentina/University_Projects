#include<iostream>
#include "UI.h"
#include "Event.h"
#include "Service.h"
#include<string.h>
#include <assert.h>
using namespace std;
UI::UI(Service& s) :s{ s }
{}

void menu()
{
	cout<< " 1: Add an event \n";
	cout <<" 2: Remove an event \n";
	cout <<" 3: Update an event \n";
	cout <<" 4: Print all the events \n";
	cout <<" 0: Exit!\n";
	
}

int UI::readOption()
{
	char s;
	cout << "Enter one digit from 0 to 4! ";
	cin >> s;
	int option = -1;
	if (s >= '0' && s <= '9')
		option = s - '0';
	return option;

}

Event UI::read()
{   
	string title, description, link, day,month,year, time, space;
	int nr_people;
	getline(cin, space);
	cout << "The title of the event is: ";
	getline(cin, title);
	cout << "The description of the event is: ";
	getline(cin, description);
	cout << "The day of the event is: ";
	getline(cin, day);
	cout << "The month of the event is: ";
	getline(cin, month);
	cout << "The year of the event is: ";
	getline(cin, year);
	cout << "The time of the event is: ";
	getline(cin, time);
	cout << "The number of people attending is: ";
	cin >> nr_people;
	cout << "The link for this event is: ";
	cin.get();
	getline(cin, link);
	Date d = Date(day, month, year);
	Event e = Event(title, description, d, time, nr_people, link);
	return e;
}

void UI::addEventUI(Service &s)
{
	Event e = this->read();
	int ok=s.addEvent(e);
	if (ok == 1)
		cout << "The event was added!\n";
	else
		cout << "This event already exists!\n";
	
}

void UI::removeEventUI(Service& s)
{
	Event e = this->read();
	int ok=s.remove(e);
	if (ok == 1)
		cout << "The removal was successful!\n";
	else
		cout << "The element that you want to remove does not exist!\n";

}


void UI::updateEventUI(Service& s)
{   
	string old_title, old_descr,space;
	getline(cin, space);
	cout << "The title of the event that you want to change is: ";
	getline(cin, old_title);
	cout << "The description of the event you want to change is: ";
	getline(cin, old_descr);
	string title, description, link, day,month,year, time;
	int nr_people;
	cout << "The title of the event is: ";
	getline(cin, title);
	cout << "The description of the event is: ";
	getline(cin, description);
	cout << "The day of the event is: ";
	getline(cin, day);
	cout << "The month of the event is: ";
	getline(cin, month);
	cout << "The year of the event is: ";
	getline(cin, year);
	cout << "The time of the event is: ";
	getline(cin, time);
	cout << "The number of people attending is: ";
	cin >> nr_people;
	cout << "The link for this event is: ";
	cin.get();
	getline(cin, link);
	Date d = Date(day, month, year);
	Event e = Event(title, description, d, time, nr_people, link);
	int ok = s.update(old_title,old_descr,e);
	if(ok==1)
		cout << "The update was successful!\n";
	else
		cout << "The element that you want to update does not exist!\n";
}


void UI::printAllEvents(Service& s)
{
	for (int i = 0; i < s.getSizeRepo(); i++)
		cout<<s.getElemsRepo()[i].getTitle()<<" "<<s.getElemsRepo()[i].getDescription()<<" "<<s.getElemsRepo()[i].getDate().getDay() <<"-"<<s.getElemsRepo()[i].getDate().getMonth()<<"-"<< s.getElemsRepo()[i].getDate().getYear()<<" "<<s.getElemsRepo()[i].getTime() << " " << s.getElemsRepo()[i].getNrPeople() << " " << s.getElemsRepo()[i].getLink() << "\n";
	    
}


void UI::printEventsList(Service& s)
{
	for (int i = 0; i < s.getSize(); i++)
		cout << s.getElems()[i].getTitle() << " " <<s.getElems()[i].getDescription() << " " << s.getElems()[i].getDate().getDay() << "-" << s.getElems()[i].getDate().getMonth() << "-" << s.getElems()[i].getDate().getYear() << " " << s.getElems()[i].getTime() << " " << s.getElems()[i].getNrPeople() << " " << s.getElems()[i].getLink() << "\n";
}

void UI::startUI(Service &s)
{     
	  
	  s.events(s);
	  string decision;
	  cout << "Input user if you want to enter the user mode or administrator otherwise ";
	  getline(cin, decision);
	  if (decision == "administrator")
		  while (1)
		  {
			  menu();
			  int option = readOption();
			  if (option == -1)
				  cout << "Error printing number!";

			  else
				  if (option == 0)
					  return;
			  switch (option)
			  {
			  case 1:
			  {
				  addEventUI(s);
				  break;
			  }

			  case 2:
			  {
				  removeEventUI(s);
				  break;
			  }

			  case 3:
			  {
				  updateEventUI(s);
				  break;
			  }

			  case 4:
			  {
				  printAllEvents(s);
				  break;
			  }



			  }


		  }
	  else
	  {
		  while (true)
		  {
			  string option;
			  cout << "Your option is: ";
			  getline(cin, option);
			  ///validations to do
			  int i = 0, j = 0;
			  int k = 0, l = 0;
			  if (option == "a")
			  {
				  string month;
				  cout << "The month is: ";
				  getline(cin, month);
				  string opt;

				  if (month == "")
				  {
					  s.sortCronologically();
					  int ok = 1;
					  for (i = j; i < s.getSizeRepo() && ok == 1; i++)
					  {
						  cout << s.getElemsRepo()[i].getTitle() << " " << s.getElemsRepo()[i].getDescription() << " " << s.getElemsRepo()[i].getDate().getDay() << "-" << s.getElemsRepo()[i].getDate().getMonth() << "-" << s.getElemsRepo()[i].getDate().getYear() << " " << s.getElemsRepo()[i].getTime() << " " << s.getElemsRepo()[i].getNrPeople() << " " << s.getElemsRepo()[i].getLink() << "\n";
						  s.getElemsRepo()[i].play();
						  cout << "Do you want to add this event to your list? Y/N\n";
						  getline(cin, opt);
						  if (opt == "Y")

						  {
							  s.addEventList(s.getElemsRepo()[i]);
							  s.getElems()[i].setNrPeople();
							  cout << "Do you want to keep looking through the events? Y/N\n";
							  getline(cin, opt);
							  if (opt == "N")
							  {
								  ok = 0;
								  j = i - 1;
							  }
						  }


					  }
				  }
				  else
				  {
					  Event list[20];
					  int length = s.eventsMonth(month, list);
					  int ok = 1;
					  for (k = l; k < length && ok == 1; k++)
					  {
						  cout << list[k].getTitle() << " " << list[k].getDescription() << " " << list[k].getDate().getDay() << "-" << list[k].getDate().getMonth() << "-" << list[k].getDate().getYear() << " " << list[k].getTime() << " " << list[k].getNrPeople() << " " << list[k].getLink() << "\n";
						  list[k].play();
						  cout << "Do you want to add this event to your list? Y/N\n";
						  getline(cin, opt);
						  if (opt == "Y")
						  {
							  int res = s.addEventList(list[k]);
							  if (res == 1)
								  s.getElems()[k].setNrPeople();
							  else
								  cout << "The eveniment was already added to your list\n!";

							  if (k != length - 1)
							  {
								  cout << "Do you want to keep looking through the events? Y/N\n";
								  getline(cin, opt);
								  if (opt == "N")
								  {
									  ok = 0;
								  }
							  }
							  else
							  {
								  cout << "There are no events left for this month. Do you want to go back to the beginning Y/N?\n";
								  getline(cin, opt);
								  if (opt == "Y")
								  {
									  l = -1;
									  k = -1;
								  }
							  }
						  }


					  }



				  }

			  }

			  if (option == "b")
			  {

				  printEventsList(s);

			  }

			  if (option == "c")
			  {
				  Event e=read();
				  int res=s.removeEventList(e);
				  if (res == 1)
					  cout << "The event was successfully deleted from your list.\n";
				  else
					  cout << "The event that you want to delete does not exist.\n";

			  }

			  if (option == "x")
				  return;

			  //TODO Specifications+coverage+add 4 more entities

		  }
	  }
}
