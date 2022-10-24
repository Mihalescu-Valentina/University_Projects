#pragma once
#pragma once
#include<string>
#include "Appliance.h"
#include "Refrigerator.h"
#include "DishWasher.h"
#include <vector>
#include<algorithm>
using namespace std;
class Service {
private:
	vector<Appliance*> elems;
public:
	Service(vector<Appliance*>appliances);
	~Service();
	void sort_by_id();
	void addAppliance(Appliance* a);
	vector<Appliance*>getAllAppliances();
	vector<Appliance*>getAllWithConsumedElectricityLessThan(double value);
	vector<Appliance*> getAllWithConsumedElectricityMoreThan(double value);
	void writeToFile(std::string file, std::vector<Appliance*> appliances);
	void appliances(Service& s);


};
