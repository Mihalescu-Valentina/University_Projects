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
	Appliance* read();
	void addApplianceUI(Service& s);
	void printAllAppliances(Service& s);

	void printEfficientAppliances(Service& s, double consumed);

	

	void saveFile(Service& s);

	void saveFileSpecific(Service& s);





};
