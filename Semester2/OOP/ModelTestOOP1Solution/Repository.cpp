#include "Repository.h"

int Repository::remove(Player p)
{
    return this->elems.remove(p);
}

int Repository::add(Player p)
{
    return this->elems.add(p);
}


int Repository::update(int position, Player p)
{
    return this->elems.update(position,p);
}

DynamicVector<Player>& Repository::getData()
{
    return this->elems;
}