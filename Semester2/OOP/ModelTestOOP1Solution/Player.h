#pragma once
#include <string>
using namespace std;
class Player
{
private:
	string name, nationality, team;
	int goals;
public:
	Player(const string& name,const string& nationality,const string& team,int goals);
	Player();
	const inline string getName() { return this->name; };
	const inline string getNationality() { return this->nationality; };
	const inline string getTeam(){ return this->team; };
	const inline int getGoals() { return this->goals; };


};