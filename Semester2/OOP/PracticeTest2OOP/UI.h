#pragma once
#include "Service.h"
#pragma once
#include "Service.h"
class UI
{
private:
	Service& s;

public:
	UI(Service& s);
	~UI();
	void startUI(Service& s);
	int readOption();
	Building* read();
	void addBuildingUI(Service& s);
	void removeEventUI(Service& s);
	void updateEventUI(Service& s);
	//void removeEventUI(Service& s);
	//void updateEventUI(Service& s);
	void printAllBuildings(Service& s);

	void printAllToBeRestored(Service &s,int year);

	void saveFileRestored(Service& s);

	void saveFileDemolish(Service& s);
	
	



};
