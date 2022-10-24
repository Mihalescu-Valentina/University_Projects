#include<iostream>
using namespace std;
#include"Service.h"
#include "UI.h"


void menu()
{
	cout << " 1: Add a player \n";
	//cout << " 2: Remove a player \n";
	//cout << " 3: Update a player \n";
	cout << " 4: Print all the players \n";
	cout << " 0: Exit!\n";

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

Protein UI::read()
{
	string name, organism, sequence,space;
	getline(cin, space);
	cout << "The organism of the protein is: ";
	getline(cin, organism);
	cout << "The name of the organism is: ";
	getline(cin, name);
	cout << "The sequence of the organism: ";
	getline(cin, sequence);
	
	//cin.get();
	Protein e = Protein(organism,name,sequence);
	return e;
}

void UI::addProteinUI(Service& s)
{
	Protein p = this->read();
	int ok = s.add(p);
	if (ok == 1)
		cout << "The protein was added!\n";
	else
		cout << "This protein already exists!\n";

}

void UI::removeProteinUI(Service& s)
{
	Protein e = this->read();
	int ok = s.remove(e);
	if (ok == 1)
		cout << "The removal was successful!\n";
	else
		cout << "The element that you want to remove does not exist!\n";

}



void UI::printAllProteins(Service& s)
{
	for (int i = 0; i < s.getSize(); i++)
		cout << s.getData()[i].getOrganism() << "|" << s.getData()[i].getName() << "|" << s.getData()[i].getSequence() << "\n";

}

void UI::printAll(Protein list[100], int length)
{
	for (int i = 0; i < length; i++)
		cout << list[i].getOrganism() << "|" << list[i].getName() << "|" << list[i].getSequence() << "\n";

}

/// <summary>
/// paramteres: list which contains the elements
/// this function sorts the elements after their protein name in  descending order
//return type: void
void UI::sort(Protein list[100], int l)
{
	Protein aux;
	for (int i = 0; i < l - 1; i++)
		for (int j = i + 1; j < l; j++)
			if (list[i].getName() <= list[j].getName())
			{
				aux = list[i];
				list[i] = list[j];
				list[j] = aux;
			}

}

void UI::sortProteins(Service& s, string name)
{
	Protein list[100];
	int l = 0;
	for (int i = 0; i < s.getSize(); i++)
		if (s.getData()[i].getName()==name)
		{
			list[l] = s.getData()[i];
			l = l + 1;
		}
	this->sort(list, l);
	this->printAll(list, l);




}

UI::UI(Service& s) : s{ s }
{
}

void UI::startUI(Service& s)
{
	s.addProteins();
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
			addProteinUI(s);
			break;
		}

		case 2:
		{
			string sequence;
			cin.get();
			getline(cin, sequence);
			sortProteins(s, sequence);
			
			break;
		}

		case 3:
		{
			removeProteinUI(s);
			break;
		}

		case 4:
		{
			printAllProteins(s);
			break;
		}



		}


	}

}