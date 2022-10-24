#pragma once
#include<string>
#include "Building.h"
#include "Block.h"
#include "House.h"
#include <vector>
#include<algorithm>
using namespace std;
class Service {
private:
	vector<Building*> elems;
public:
   Service(vector<Building*>buildings);
   ~Service();
   void sort_by_adress();
   void addBuilding(Building* building);
   void removeBuilding(Building* b);
   void updateBuilding(Building* b,Building* b1);
   vector<Building*>getAllBuildings();
   vector<Building*>getAllToBeDemolished();
   vector<Building*>getAllToBeRestored();
   void writeToFile(std::string file, std::vector<Building*> buildings);
   void buildings(Service& s);


};