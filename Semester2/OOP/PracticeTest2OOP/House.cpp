#include "House.h"
#include <string>
#include<sstream>



House::House(string _adress,int _constructionYear,bool _isHistorical): Building{_adress,_constructionYear},isHistorical{_isHistorical}
{
}

House::~House()
{
}

bool House::mustBeRestored() const
{
    if (2022 - this->constructionYear > 100)
        return true;
    return false;
}

bool House::canBeDemolished() const
{
    return !this->isHistorical;
}

string House::toString() const
{
    stringstream buffer;
    buffer << "Home \n\t adress: " << this->adress << endl << "\t construction year: " << this->constructionYear << endl << "\t is historical: " << this->isHistorical<<endl;
    return buffer.str();
}
