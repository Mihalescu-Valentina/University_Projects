#pragma once
#include "Building.h"
class House :public Building
{
private: 
	bool isHistorical;
public:
	House(string adress,int constructionYear,bool _isHistorical);
	virtual ~House();
	bool mustBeRestored()  const override;
	bool canBeDemolished() const override;
	string toString() const;
};