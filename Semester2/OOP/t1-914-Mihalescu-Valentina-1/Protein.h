#pragma once
#pragma once
#include <string>
using namespace std;
class Protein
{
private:
	string name, sequence, organism;
	int goals;
public:
	Protein(const string& organism, const string& name, const string& sequence);
	Protein();
	const inline string getName() { return this->name; };
	const inline string getOrganism() { return this->organism; };
	const inline string getSequence() { return this->sequence; };
	


};