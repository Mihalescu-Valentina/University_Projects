#pragma once
#include <string>
class Disorder {
private:
	std::string category, name, symptoms;

public:
	Disorder(const std::string category, std::string name,std::string symptoms);

	Disorder();
	~Disorder();

	inline std::string getCategory() const { return this->category; }

	inline std::string getName() const { return this->name; }

	inline std::string getSymptoms() const { return this->symptoms; };

	bool operator==(const Disorder&);
	friend std::istream& operator>>(std::istream& is, Disorder& ti);
	friend std::ostream& operator<<(std::ostream& os, const Disorder& to);


};