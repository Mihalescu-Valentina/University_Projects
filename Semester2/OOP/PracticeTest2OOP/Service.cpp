#include "Service.h"
#include <fstream>
using namespace std;
Service::Service(vector<Building*> buildings) : elems{ buildings }
{
}

Service::~Service()
{
	for (auto& i : this->elems)
		delete i;
}

void Service::sort_by_adress()
{
	Building* aux;
	for (int i = 0; i < this->elems.size()-1; i++)
		for (int j = i + 1; j < this->elems.size(); j++)
			if (this->elems[i]->getAdress() > this->elems[j]->getAdress())
			{
				aux = this->elems[i];
				this->elems[i] = this->elems[j];
				this->elems[j] = aux;
			
			}

}

void Service::addBuilding(Building* b)
{
	if (count(this->elems.begin(), this->elems.end(), b))
		return;
	else
	{
		this->elems.push_back(b);
		
	}

}

void Service::removeBuilding(Building* b)
{
	
	for(int i=0;i<this->elems.size();i++)
		if (this->elems[i]->getAdress() == b->getAdress())
		{
			this->elems.erase(this->elems.begin() + i);
			break;
		}
	
}

void Service::updateBuilding(Building* b,Building* b1)
{
	for (int i = 0; i < this->elems.size(); i++)
		if (this->elems[i]->getAdress() == b->getAdress())
		{
			this->elems[i]=b1;
			break;

		}
	
}




vector<Building*> Service::getAllBuildings()
{
	return this->elems;
}

void Service::buildings(Service& s)
{
	Building* b1 = new Block{ "Principal Street nr 1000",1900,100,90 };
	Building* b2 = new House{ "Principal Street nr 2222",1910,false };
	Building* b3 = new Block{ "Principal Street nr 4560",1905,200,100 };
    this->addBuilding(b1);
	this->addBuilding(b2);
	this->addBuilding(b3);
	
}



vector<Building*> Service::getAllToBeDemolished()
{
	vector<Building*>demolished;
	for (auto elem : this->elems)
		if (elem->canBeDemolished() == true)
			demolished.push_back(elem);
	return demolished;
	
}

vector<Building*> Service::getAllToBeRestored()
{
	vector<Building*>restored;
	for (auto elem : this->elems)
		if (elem->mustBeRestored() == true)
			restored.push_back(elem);
	return restored;

}

void Service::writeToFile(std::string file, std::vector<Building*> buildings) {
	std::ofstream fout(file);
	for (auto& i : buildings)
		fout << i->toString();
}
