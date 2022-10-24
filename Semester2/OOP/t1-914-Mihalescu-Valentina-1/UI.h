#pragma once
#include "Service.h"
class UI {
private:
	Service s;

public:
	UI(Service& s);
	void startUI(Service& s);
	int readOption();
	Protein read();
	void addProteinUI(Service& s);
	void removeProteinUI(Service& s);
	
	void printAllProteins(Service& s);

	void printAll(Protein list[100], int position);

	void sort(Protein list[100], int l);

	void sortProteins(Service& s, string team);

};
