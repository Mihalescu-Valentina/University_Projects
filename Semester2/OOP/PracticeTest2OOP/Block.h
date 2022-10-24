#pragma once
#include "Building.h"
class Block :public Building
{
private:
	int totalApartments;
	int occupiedApartments;

public:
	Block(string _adress, int _constructionYear, int _totalApartments, int _occupiedApartments);
	~Block();
	bool mustBeRestored() const override;
	bool canBeDemolished() const override;
	string toString() const override;
};
