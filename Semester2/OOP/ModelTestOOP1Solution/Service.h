#pragma once
#include "Repository.h"
class Service {
private:Repository repo;
public:
	int add(Player p);
	int remove(Player p);
	int getSize();
	bool findbyTeam(string team,int position);
	Service(Repository repo);
	DynamicVector<Player>& getData();
	void addPlayers();
};