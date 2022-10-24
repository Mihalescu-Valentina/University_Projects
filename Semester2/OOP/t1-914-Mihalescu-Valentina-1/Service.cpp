#include "Service.h"

int Service::add(Protein p)
{
	return this->repo.add(p);
}

int Service::remove(Protein p)
{
	return this->repo.remove(p);
}

int Service::getSize()
{
	return this->repo.getSize();
}

Service::Service(Repository repo):repo{repo}
{
}

DynamicVector<Protein>& Service::getData()
{
	return this->repo.getData();
}

void Service::addProteins()
{
	Protein p1 = Protein("Human", "Myosin-2", "JD");
	this->add(p1);
	Protein p2 = Protein("Human", "Keratin", "HD");
	this->add(p2);
	Protein p3 = Protein("Mouse", "Keratin", "AD");
	this->add(p3);
	Protein p4 = Protein("E-coli", "tufA", "JS");
	this->add(p4);
	Protein p5 = Protein("E-coli", "cspE", "MS");
	this->add(p5);

}
