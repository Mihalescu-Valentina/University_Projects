#pragma once
#include <string>
using namespace std;
class Appliance
{
protected:
	string id;
	double weight;
public:
	Appliance(string _id, double _weight);
	virtual ~Appliance();
	virtual double consumedElectricity() const = 0;
	virtual string toString() const;
	string getId()  const;
	double getWeight() const;

};
