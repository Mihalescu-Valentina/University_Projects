#pragma once
#include "Appliance.h"
class DishWasher :public Appliance
{
private:
	double washingCydeLength;
	double consumedElectricityForOneHour;

public:
	DishWasher(string id, double weight,double _washingCydeLength, double _consumedElectricityForOneHour);
	~DishWasher();
	double consumedElectricity() const override;
	string toString() const override;
};
