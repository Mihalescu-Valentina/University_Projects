#include "Building.h"
#include "Block.h"
#include "House.h"
#include<iostream>
#include<string>
using namespace std;
#include<iostream>
#include "UI.h"
#include "Service.h"
#include<string.h>
#include <fstream>
using namespace std;
UI::UI(Service& s) :s{ s }
{}





void menu()
{
	cout << " 1: Add a building \n";
	cout << " 2: Display all the buildings \n";
	cout << " 3: Display all the buildings that must be restored \n";
	cout << " 4: Save the buildings to be restored in a file \n";
	cout << " 5: Save the buildings to be demolished in a file!\n";
	cout << " 0: Exit \n";

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

Building* UI::read()
{
	string adress,space,type;
	int constructionYear;
	
	getline(cin, space);
	cout << "The adress of the building is: ";
	getline(cin, adress);
	cout << "The construction year of the event is: ";
	cin>>constructionYear;
	cin.get();
	cout << "House or block?";
	getline(cin, type);
	if (type == "block")
	{   
		Building* b;
		int totalApartments, occupiedApartments;
		cout << "The number of total apartments in the block is: ";
		cin >> totalApartments;
		cin.get();
		cout << "The number of occupied apartments in the block is: ";
		cin >> occupiedApartments;
		cin.get();
		b = new Block{ adress,constructionYear,totalApartments,occupiedApartments };
		return b;
		
		
	}
	else if (type == "house")
	{   
		Building* b;
		string isHist;
		bool isHistorical=false;
		cout << "If your house is historical please enter true else false ";
		cin >> isHist;
		cin.get();
		if (isHist == "yes")
			isHistorical = true;
		else
			if (isHist == "no")
				isHistorical = false;

		b = new House{ adress,constructionYear,isHistorical };
		return b;
	}
	return new Block{ "null",0,0,0 };
	
}

void UI::addBuildingUI(Service& s)
{
	Building* b = this->read();
	s.addBuilding(b);
	
}

void UI::removeEventUI(Service& s)
{
	Building* b = this->read();
	s.removeBuilding(b);

}


void UI::updateEventUI(Service& s)
{
	Building* b = this->read();
	cout<<"Enter the data for the updated building: "<< " ";
	Building* b1 = this->read();
	s.updateBuilding(b,b1);
}


void UI::printAllBuildings(Service& s)
{
	for (auto elem : s.getAllBuildings())
		cout<<elem->toString();

}

void UI::printAllToBeRestored(Service &s,int year)
{
	for (auto elem : s.getAllToBeRestored())
		if(elem->getConstructionYear()>year)
			cout << elem->toString();
}

void UI::saveFileRestored(Service &s) {
	string file_for_restored;
	cout << "File for restored"<<" ";
	cin >> file_for_restored;
	auto a = s.getAllToBeRestored();
	s.writeToFile(file_for_restored, a);

}

void UI::saveFileDemolish(Service& s) {
	string file_for_demolish;
	cout << "File for demolishing"<<" ";
	cin >> file_for_demolish;
	auto a = s.getAllToBeDemolished();
	s.writeToFile(file_for_demolish, a);

}



UI::~UI()
{
}

void UI::startUI(Service& s)
{

	s.buildings(s);

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
			addBuildingUI(s);
			break;
		}


		case 2:
		{   
			s.sort_by_adress();
			printAllBuildings(s);
			break;
		}

		case 3:
		{
			int year;
			cout << "Enter a year: ";
			cin >> year;
			cin.get();
			printAllToBeRestored(s, year);
			break;
		}

		case 4:
		{
			this->saveFileRestored(s);
		}

		case 5:
		{
			this->saveFileDemolish(s);
		}

		case 6:
		{
			this->removeEventUI(s);
		}



		case 7:
		{
			this->updateEventUI(s);
		}

		}

	}


}
		
	

