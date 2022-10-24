#include "Repository.h"

int Repository::remove(Protein p)
{
    return this->elems.remove(p);
}

int Repository::add(Protein p)
{
    return this->elems.add(p);
}

DynamicVector<Protein>& Repository::getData()
{
    return this->elems;
}
