#pragma once
#include<string>
#include<sstream>
class Star {
private:
	std::string name;
	std::string constellation;
	int ra, dec, diameter;

public:
	Star();
	Star(std::string _name, std::string _constellation,int _ra,int _dec,int _diameter);
	~Star();
	inline std::string getName() const {
		return this->name;
	}

	inline std::string getConstellation() const {
		return this->constellation;
	}
	

	inline int getRa() const {
		return this->ra;
	}

	inline int getDec() const {
		return this->dec;
	}

	inline int getDiameter() const {
		return this->diameter;
	}
	

	void setName(std::string name);

	void setDiameter(int diameter);

	void setRa(int ra);

	void setDec(int dec);

	friend std::istream& operator>>(std::istream& is, Star& s);

	friend std::ostream& operator<<(std::ostream& os, Star& s);

	

};