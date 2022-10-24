#include <crtdbg.h>
#include <string>
#include <iostream>
#include <assert.h>
#include "Service.h"
#include "UI.h"
#include "Building.h"
#include "Block.h"
#include "House.h"
#include<vector>


using namespace std;
int main()
{

	vector<Building*> buildings{};
	Service s{ buildings };
	UI ui{ s };
	ui.startUI(s);
	_CrtDumpMemoryLeaks();


	return 0;
}