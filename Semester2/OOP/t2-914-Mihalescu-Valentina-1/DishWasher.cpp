#include "DishWasher.h"
#include <sstream>

DishWasher::DishWasher(string id, double weight, double _washingCydeLength, double _consumedElectricityForOneHour) : Appliance{ id, weight}, washingCydeLength{ _washingCydeLength }, consumedElectricityForOneHour{ _consumedElectricityForOneHour }
{
}

DishWasher::~DishWasher()
{
}

double DishWasher::consumedElectricity() const
{
	return this->consumedElectricityForOneHour * this->washingCydeLength * 20;
}

string DishWasher::toString() const
{
	stringstream buffer;
	buffer << "DishWasher \n\t id: " << this->id << endl << "\t weight: " << this->weight << endl << "\t washing cyde length: " << this->washingCydeLength << endl << "\t consumed electricity for one Hour: " << this->consumedElectricityForOneHour << endl;
	return buffer.str();
}
