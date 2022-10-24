#pragma once
#include "DynamicVector.h"
#include "Event.h"

class Repository {
private: 
	  DynamicVector<Event> elems{ 20 };
public:

	int getSize() const;
	int addEvent(Event e);
	DynamicVector<Event>& getElemsRepo();
	int remove(Event e);
	int update(const std::string& old_title, const std::string& old_descr,Event e);

};

	

