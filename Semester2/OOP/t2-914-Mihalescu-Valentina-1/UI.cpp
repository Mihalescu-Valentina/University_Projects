#include "Appliance.h"
#include "Refrigerator.h"
#include "DishWasher.h"
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
	cout << " 1: Add an appliance \n";
	cout << " 2: Display all the appliances \n";
	cout << " 3: Display all the efficient appliances \n";
	cout << " 4: Save the specific appliances in a file \n";
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

Appliance* UI::read()
{
	string id, space,type;
	double weight;

	getline(cin, space);
	cout << "The id of the appliance is: ";
	getline(cin,id);
	cout << "The weight of the appliance is: ";
	cin >> weight;
	cin.get();
	cout << "Refrigerator or DishWasher?";
	getline(cin, type);
	if (type == "dishwasher")
	{
		Appliance* b;
		double washingCydeCycle, consumedElectricityForOneHour;
		cout << "The washing cyde cicle is: ";
		cin >> washingCydeCycle;
		cin.get();
		cout << "The consumed electricity for one hour is: ";
		cin >> consumedElectricityForOneHour;
		cin.get();
		b = new DishWasher{ id,weight,washingCydeCycle,consumedElectricityForOneHour };
		return b;


	}
	else if (type == "refrigerator")
	{
		Appliance* b;
		string electricityUsageClass;
		bool hasFreezer = false;
		cout << "Enter the electricity usage class ";
		getline(cin,electricityUsageClass);
		cout << "Has freezer?";
		cin >> hasFreezer;
		cin.get();

		b = new Refrigerator{ id,weight,electricityUsageClass,hasFreezer };
		return b;
	}
	

}

void UI::addApplianceUI(Service& s)
{
	Appliance* b = this->read();
	s.addAppliance(b);

}



void UI::printAllAppliances(Service& s)
{
	for (auto elem : s.getAllAppliances())
		cout << elem->toString();

}

void UI::printEfficientAppliances(Service& s,double consumed)
{
	for (auto elem : s.getAllWithConsumedElectricityLessThan(consumed))
		if (elem->consumedElectricity() < consumed)
			cout << elem->toString();
}

void UI::saveFile(Service& s) {
	string file;
	cout << "File" << " ";
	cin >> file;
	auto a = s.getAllAppliances();
	s.writeToFile(file, a);

}

void UI::saveFileSpecific(Service& s) {
	string file;
	double value;
	cout << "File" << " ";
	cin >> file;
	cout << "value";
	cin >> value;
	auto a = s.getAllWithConsumedElectricityMoreThan(value);
	s.writeToFile(file, a);

}



UI::~UI()
{
}

void UI::startUI(Service& s)
{

	s.appliances(s);

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
			addApplianceUI(s);
			break;
		}


		case 2:
		{
			s.sort_by_id();
			printAllAppliances(s);
			break;
		}

		case 3:
		{
			int value;
			cout << "Enter a value: ";
			cin >> value;
			cin.get();
			printEfficientAppliances(s, value);
			break;
		}

		case 4:
		{
			this->saveFile(s);
		}

		case 5:
		{
			this->saveFileSpecific(s);
		}

		



		
		}

	}


}



