#pragma once
#include "Appliance.h"
class Refrigerator :public Appliance
{
private:
	string electricitUsageClass;
	bool hasFreezer;
public:
	Refrigerator(string id,double weight,string _electricityUsageClass,bool _hasFreezer);
	virtual ~Refrigerator();
	double consumedElectricity() const override;
	string toString() const;
};