#pragma once
#include "Service.h"
class UI {
private:
	Service s;

public:
	UI(Service& s);
	void startUI(Service& s);
	int readOption();
	Player read();
	void addPlayerUI(Service& s);
	void removeEventUI(Service& s);
	void updateEventUI(Service& s);
	void printAllPlayers(Service& s);

	void printAll(Player list[100], int position);

	void sort(Player list[100], int l);

	void sortPlayers(Service& s,string team);

};
