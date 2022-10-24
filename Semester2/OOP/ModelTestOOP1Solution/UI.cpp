#include<iostream>
using namespace std;
#include"Service.h"
#include "UI.h"


void menu()
{
	cout << " 1: Add a player \n";
	cout << " 2: Sort the players of a certain team \n";
	cout << " 3: Remove a player \n";
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

Player UI::read()
{
	string name, nationality, team,space;
	int goals;
	getline(cin, space);
	cout << "The name of the player is: ";
	getline(cin, name);
	cout << "The nationality of the player is: ";
	getline(cin, nationality);
	cout << "The team of the player is: ";
	getline(cin, team);
	cout << "The nr of goals of the player is: ";
	cin >> goals;
	//cin.get();
	Player e = Player(name, nationality, team,goals);
	return e;
}

void UI::addPlayerUI(Service& s)
{
	Player p = this->read();
	int ok = s.add(p);
	if (ok == 1)
		cout << "The player was added!\n";
	else
		cout << "This player already exists!\n";

}

void UI::removeEventUI(Service& s)
{
	Player p = this->read();
	int ok = s.remove(p);
	if (ok == 1)
		cout << "The removal was successful!\n";
	else
		cout << "The element that you want to remove does not exist!\n";

}




void UI::printAllPlayers(Service& s)
{
	for (int i = 0; i < s.getSize(); i++)
		cout << s.getData()[i].getName() << "|" << s.getData()[i].getNationality() << "|" << s.getData()[i].getTeam() << "|" << s.getData()[i].getGoals() << "\n";

}

void UI::printAll(Player list[100], int length)
{
	for (int i = 0; i < length; i++)
		cout << list[i].getName() << "|" << list[i].getNationality() << "|" << list[i].getTeam() << "|" << list[i].getGoals() << "\n";

}

void UI::sort(Player list[100],int l)
{
	Player aux;
	for (int i = 0; i < l - 1; i++)
		for (int j = i + 1; j < l; j++)
			if (list[i].getGoals() >= list[j].getGoals())
			{
				aux = list[i];
				list[i] = list[j];
				list[j] = aux;
			}
    
}

void UI::sortPlayers(Service& s,string team)
{
	Player list[100];
	int l = 0;
	for (int i = 0; i < s.getSize(); i++)
		if (s.getData()[i].getTeam() == team)
		{
			list[l] = s.getData()[i];
			l = l + 1;
		}
	this->sort(list, l);
	this->printAll(list,l);

	


}

UI::UI(Service& s): s{s}
{
}

void UI::startUI(Service& s)
{
	s.addPlayers();
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
			addPlayerUI(s);
			break;
		}

		case 2:
		{   
			string team;
			cin.get();
			getline(cin, team);
			sortPlayers(s, team);
			break;
		}

		case 3:
		{    
			removeEventUI(s);
			
			break;
		}

		case 4:
		{
			printAllPlayers(s);
			break;
		}



		}


	}

}