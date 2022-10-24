#include <sstream>
#include "Appliance.h"

Appliance::Appliance(string _id, double _weight): id{_id},weight{_weight}
{
}

Appliance::~Appliance()
{
}

string Appliance::toString() const
{
	stringstream buffer;
	buffer << "Appliance \n\t id: " << this->id << endl << "\t weight: " << this->weight << " " << endl;
	return buffer.str();
}

string Appliance::getId() const
{
    return this->id;
}

double Appliance::getWeight() const
{
    return this->weight;
}
