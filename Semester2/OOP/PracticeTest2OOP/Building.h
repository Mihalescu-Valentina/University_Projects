#pragma once
#include <string>
using namespace std;
class Building
{
protected:
	string adress;
	int constructionYear;
public:
	Building(string _adress, int _constructionYear);
	virtual ~Building();
	virtual bool mustBeRestored() const = 0;
	virtual bool canBeDemolished() const= 0;
	virtual string toString() const;
	string getAdress()  const;
	int getConstructionYear() const;
};
