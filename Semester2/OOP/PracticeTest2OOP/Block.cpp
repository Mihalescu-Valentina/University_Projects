#include "Block.h"
#include <sstream>


Block::Block(string _adress, int _constructionYear, int _totalApartments, int _occupiedApartments) : Building{ _adress,_constructionYear }, occupiedApartments{ _occupiedApartments }, totalApartments{ _totalApartments }
{
}

Block::~Block()
{
}

bool Block::mustBeRestored() const
{
    if (2022 - this->getConstructionYear() > 40 && ((this->occupiedApartments * 100) / this->totalApartments) > 80)
        return true;
    return false;
}

bool Block::canBeDemolished() const
{
    if (((this->occupiedApartments * 100) / this->totalApartments) < 5)
        return true;
    return false;
}

string Block::toString() const
{
    stringstream buffer;
    buffer << "Block \n\t adress: " << this->adress << endl << "\t construction year: " << this->constructionYear <<endl<<"\t total apartments number: "<<this->totalApartments<<endl<<"\t occupied apartments number: "<<this->occupiedApartments<<endl;
    return buffer.str();
}
