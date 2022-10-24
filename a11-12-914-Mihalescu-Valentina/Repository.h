#pragma once
#include "DynamicVector.h"
#include "Event.h"
#include <vector>

class Repository {
private: 
	  
	std::vector<Event> elems;
public:

	virtual int getSize() const;
	virtual int addEvent(Event e);
	virtual std::vector<Event>& getElemsRepo();
	virtual int remove(std::string title);
	virtual int update(const std::string& old_title, const std::string& old_descr,Event e);

};

class Repository_file :public Repository {
protected:
	std::string filename;
public:
	///create the file repository
	Repository_file();
	///write the tutorials in a file
	void writeinfile(std::vector<Event> arr);
	///read the tutorials from a file
	std::vector<Event> readfromfile();
};

	

