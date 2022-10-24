#include "Service.h"
#include <fstream>
#include "Refrigerator.h"
#include "DishWasher.h"
using namespace std;
Service::Service(vector<Appliance*> appliances) : elems{ appliances }
{
}

Service::~Service()
{
	for (auto& i : this->elems)
		delete i;
}

void Service::sort_by_id()
{
	Appliance* aux;
	for (int i = 0; i < this->elems.size() - 1; i++)
		for (int j = i + 1; j < this->elems.size(); j++)
			if (this->elems[i]->getId() > this->elems[j]->getId())
			{
				aux = this->elems[i];
				this->elems[i] = this->elems[j];
				this->elems[j] = aux;

			}

}

void Service::addAppliance(Appliance* a)
{
	if (count(this->elems.begin(), this->elems.end(), a))
		return;
	else
	{
		this->elems.push_back(a);

	}

}





void Service::appliances(Service& s)
{
	Appliance* b1 = new DishWasher{ "234",24,56.0,100};
	Appliance* b2 = new Refrigerator{ "123",56,"A",true};
	Appliance* b3 = new Refrigerator{ "125",58,"A+",false };
	this->addAppliance(b1);
	this->addAppliance(b2);
	this->addAppliance(b3);

}







vector<Appliance*> Service::getAllAppliances()
{
	return this->elems;
}

vector<Appliance*> Service::getAllWithConsumedElectricityLessThan(double value)
{
	vector<Appliance*>app;
	for (auto elem : this->elems)
		if (elem->consumedElectricity()<value)
			app.push_back(elem);
	return app;

}

vector<Appliance*> Service::getAllWithConsumedElectricityMoreThan(double value)
{
	vector<Appliance*>app;
	for (auto elem : this->elems)
		if (elem->consumedElectricity() > value)
			app.push_back(elem);
	return app;

}

void Service::writeToFile(std::string file, std::vector<Appliance*>appliances) {
	std::ofstream fout(file);
	for (auto& i : appliances)
		fout << i->toString();
}
