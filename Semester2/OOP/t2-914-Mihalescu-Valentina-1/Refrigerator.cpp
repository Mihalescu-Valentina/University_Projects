#include "Refrigerator.h"
#include <sstream>

Refrigerator::Refrigerator(string id, double weight, string _electricityUsageClass, bool _hasFreezer): Appliance{id,weight},electricitUsageClass{_electricityUsageClass},hasFreezer{_hasFreezer}
{
}

Refrigerator::~Refrigerator()
{
}

double Refrigerator::consumedElectricity() const
{
	double x=1.0;
	if (this->electricitUsageClass == "A")
	{
		x = 3;

	}
	else
		if (this->electricitUsageClass == "A+")
		{
			x = 2, 5;
		}

		else
			if (this->electricitUsageClass == "A++")
			{
				x = 2;
			}
	return x * 30;


}

string Refrigerator::toString() const
{
	stringstream buffer;
	buffer << "Refrigerator \n\t id: " << this->id << endl << "\t weight: " << this->weight << " " << endl<<this->electricitUsageClass<<" "<<this->hasFreezer<<" "<<endl;
	return buffer.str();
}
