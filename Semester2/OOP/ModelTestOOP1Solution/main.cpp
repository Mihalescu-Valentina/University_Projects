#include<iostream>
#include<string>
#include "Repository.h"
#include "Service.h"
#include "UI.h"
using namespace std;
int main() {
	Repository repo{};
	Service s{repo};
	
	UI ui{ s };
	ui.startUI(s);
	_CrtDumpMemoryLeaks();
	return 0;
}