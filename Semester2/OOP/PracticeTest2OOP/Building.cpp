#include "Building.h"
#include <sstream>



Building::Building(string _adress, int _constructionYear): adress{_adress},constructionYear{_constructionYear}
{
}

Building::~Building()
{
}

string Building::toString() const
{
    stringstream buffer;
    buffer << "Building \n\t adress: " << this->adress << endl << "\t construction year: " << this->constructionYear << endl;
    return buffer.str();
}

string Building::getAdress() const
{
    return this->adress;
}

int Building::getConstructionYear() const
{
    return this->constructionYear;
}
