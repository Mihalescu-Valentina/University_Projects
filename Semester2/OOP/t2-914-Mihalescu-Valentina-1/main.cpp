#include <crtdbg.h>
#include <string>
#include <iostream>
#include <assert.h>
#include "Service.h"
#include "UI.h"
#include "Appliance.h"
#include "Refrigerator.h"
#include "DishWasher.h"
#include<vector>


using namespace std;
int main()
{

	vector<Appliance*> appliances{};
	Service s{ appliances };
	UI ui{ s };
	ui.startUI(s);
	


	return 0;
}