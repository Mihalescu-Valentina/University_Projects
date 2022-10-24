#include "Service.h"
#include "Repository.h"


int Service::add(Player p)
{
	return this->repo.add(p);
}

int Service::remove(Player p)
{
	return this->repo.remove(p);
}

int Service::getSize()
{
	return this->repo.getSize();
}

bool Service::findbyTeam(string team,int position)
{
	
	
	if (this->getData()[position].getTeam() == team)
		return true;
	
	return false;
}

Service::Service(Repository repo) : repo{repo}
{

}

DynamicVector<Player>&Service::getData ()
{
	return this->repo.getData();
}

void Service::addPlayers()
{
	Player p1=Player("Nora", "NOR", "Larvik", 101);
	this->add(p1);
	Player p2 = Player("Isabelle_Guilden", "SWE", "CSM_Bucuresti", 80);
	this->add(p2);
	Player p3 = Player("Cristina_Neagu", "ROU", "Buducnost", 63);
	this->add(p3);
	Player p4 = Player("Ana_Minskova", "RUS", "Larvik", 90);
	this->add(p4);
	Player p5 = Player("Mihalescu_Valentina", "ROU", "Rustov-Don", 1);
	this->add(p5);
}
