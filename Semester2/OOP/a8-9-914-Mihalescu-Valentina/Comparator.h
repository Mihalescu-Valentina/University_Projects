/*#pragma once
#include <string.h>
#include"Event.h"
#include <vector>
#include<assert.h>
#include<iostream>
using namespace std;
template <typename T>
class Comparator
{
public:
	virtual bool compare(T a, T b) = 0;
	void test_sort_comparator();


};

class CompareNumbers : public Comparator<int>
{
public:
	bool compare(int a, int b)
	{
		if (a < b)
			return 0;
		else return 1;
	}


};

class CompareStrings : public Comparator<char*>
{
public:
	bool compare(char* a, char* b)
	{
		if (strcmp(a,b) < 0)
			return 0;
		else return 1;
	}


};

template <typename T>
void sort(std::vector<T> v,Comparator<T> *c)
{
	T aux;
	int j;
	for(int i=0;i<v.size-1;i++)
	  for(j=i+1;j<v.size;j++)
		if (c->compare(v[i], v[j]) == 0)
		{
			aux=v[i];
			v[i]=v[j];
			v[j]=aux;

		}

}

template<typename T>
void Comparator<T>::test_sort_comparator()
{
	std::vector<int> v{ 4,1,2,3 };
	Comparator *c;
	sort<int>(v, c);

	assert(v[0] == 1);
	assert(v[1] == 2);
	assert(v[2] == 3);
	assert(v[3] == 4);
}


template<typename T>
class Comparator {
public:
	virtual bool operator() (
		const T& a, const T& b
		) = 0;
	void TestComparator();
};

template<typename T>
class CompareAscendingByTitle : public Comparator<T>
{
public:
	bool operator()(const T& a, const T& b) override;
};

template<typename T>
bool CompareAscendingByTitle<T>::operator()(const T& a, const T& b) {
	return a.getTitle() < b.getTitle();
}

template<typename T>
class CompareDescendingByYear : public Comparator<T>
{
	bool operator()(const T& a, const T& b) override;
};

template<typename T>
bool CompareDescendingByYear<T>::operator() (const T& a, const T& b) {
	return a.getYear() > b.getYear();
};

template<typename T>
void sort(std::vector<T>v, Comparator<T>& c)
{
	for (int i = 0; i < v.size - 1; i++)
		for (j = i + 1; j < v.size; j++)
			if (c->operator(v[i], v[j]) == 0)
			{
				aux = v[i];
				v[i] = v[j];
				v[j] = aux;

			}
}

template<typename T>
void Comparator<T>::TestComparator() {
	std::vector<Event> events;
	Date d1 = Date("01", "01", "2022");
	Event e1 = Event("Title", "description", d1, "20:30", 100, "https://www.linkedin.com/home/?originalSubdomain=ro");
	events.push_back(e1);
	Date d2 = Date("12", "04", "2023");
	Event e2 = Event("Title", "nostalgia", d2, "20:45", 2500, "https://disneyland.disney.go.com/");
	events.push_back(e2);
	Date d3 = Date("01", "01", "2023");
	Event e3 = Event("Title", "European tour", d3, "21:00", 9000, "https://www.bmthofficial.com/live/");
	events.push_back(e3);
	CompareAscendingByTitle<Event> c;
	c.sort(events,c);
	assert(events[0].getTitle() == "Title");
	assert(events[1].getTitle() == "Title");
	assert(events[2].getTitle() == "Title");
	assert(events[3].getTitle() == "Title");


}


template <typename T>
class Comparator {
public:
	virtual bool compare(T& elem1, T& elem2) = 0;
};

template <typename Video>
class ComparatorAscTitle : public Comparator<Event> {
public:
	bool compare(Event& elem1,Event& elem2) override {

		return elem1.getTitle() < elem2.getTitle();
	}
};

template <typename Video>
class ComparatorDescYear : public Comparator<Event> {
public:
	bool compare(Event elem1, Event elem2) override {

		return elem1.getYear() >= elem2.getYear();
	}
};

template <typename Event>
void sortVec(std::vector<Event>& arr, Comparator<Event>& cmp_class) {

	int ok = 0;
	while (!ok) {

		ok = 1;
		for (auto i = arr.begin(); i < arr.end() - 1; i++) {

			if (!cmp_class.compare(*i, *(i + 1))) {
				std::swap(*i, *(i + 1));
				ok = 0;
			}
		}
	}
}

void testSort() {

	std::vector<Event> events;
	Date d1 = Date("01", "01", "2022");
	Event e1 = Event("Title", "description", d1, "20:30", 100, "https://www.linkedin.com/home/?originalSubdomain=ro");
	events.push_back(e1);
	Date d2 = Date("12", "04", "2023");
	Event e2 = Event("Title", "nostalgia", d2, "20:45", 2500, "https://disneyland.disney.go.com/");
	events.push_back(e2);
	Date d3 = Date("01", "01", "2023");
	Event e3 = Event("Title", "European tour", d3, "21:00", 9000, "https://www.bmthofficial.com/live/");
	events.push_back(e3);
	Comparator<Event*> c;
	sortVec(events, c);
	assert(events[0].getTitle() == "Title");
	assert(events[1].getTitle() == "Title");
	assert(events[2].getTitle() == "Title");
	assert(events[3].getTitle() == "Title");
}*/

