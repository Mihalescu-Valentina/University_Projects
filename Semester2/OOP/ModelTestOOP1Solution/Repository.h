#pragma once
#include"DynamicVector.h"
#include "Player.h"
class Repository
{
private: DynamicVector<Player> elems{20};

public:
	const inline int getSize() { return this->elems.getSize(); };
	int remove(Player e);
	int add(Player e);
	int update(int position, Player p);

	DynamicVector<Player>& getData();
	


};