#pragma once
#include <string>
#include"Event.h"
#include<vector>

template <typename T>
class DynamicVector
{
private:
	T* elems;
	int size;
	int capacity;

public:
	// default constructor for a DynamicVector
	DynamicVector(int capacity = 10);

	// copy constructor for a DynamicVector
	DynamicVector(const DynamicVector& v);
	~DynamicVector();

	// assignment operator for a DynamicVector
	DynamicVector& operator=(const DynamicVector& v);
	//DynamicVector& operator+(T& elem);

	/*
		Overloading the subscript operator
		Input: pos - a valid position within the vector.
		Output: a reference to the element o position pos.
	*/
	T& operator[](int pos);

	void operator+(T& e);

	//void operator+(Event elem);

	//int& operator==(const DynamicVector& v);

	// Adds an element to the current DynamicVector.
	int add(T e);

	int getSize() const;
	int remove(T e);
	int update(const std::string& old_title, const std::string& old_descr,T e);
	int equal(T v, int pos);
	
	

private:
	// Resizes the current DynamicVector, multiplying its capacity by a given factor (real number).
	void resize(int factor = 2);
};


///this function is the constructor of the dynamic vector
/// <param name="capacity"> the capacity of the dynamic vector
template <typename T>
DynamicVector<T>::DynamicVector(int capacity)
{
	this->size = 0;
	this->capacity = capacity;
	this->elems = new T[capacity];
}

//the copy contructor of the dynamic vector
template <typename T>
DynamicVector<T>::DynamicVector(const DynamicVector<T>& v)
{
	this->size = v.size;
	this->capacity = v.capacity;
	this->elems = new T[this->capacity];
	for (int i = 0; i < this->size; i++)
		this->elems[i] = v.elems[i];
}

//the destructor
template <typename T>
DynamicVector<T>::~DynamicVector()
{
	delete[] this->elems;
}

//the overloaded equality operator
template <typename T>
DynamicVector<T>& DynamicVector<T>::operator=(const DynamicVector<T>& v)
{
	if (this == &v)
		return *this;

	this->size = v.size;
	this->capacity = v.capacity;

	T* aux = new T[this->capacity];

	delete[] this->elems;

	this->elems = aux;
	for (int i = 0; i < this->size; i++)
		this->elems[i] = v.elems[i];

	return *this;
}

//the overloaded dereferencing operator
template <typename T>
T& DynamicVector<T>::operator[](int pos)
{
	return this->elems[pos];
}

template <typename T>
void DynamicVector<T>::operator+(T& e)
{
	if (this->size == this->capacity)
		resize();

	this->size++;
	this->elems[this->size - 1] = e;
}





/*template<typename T>
bool & DynamicVector<T>::operator==(const DynamicVector& v)
{
	for(int i=0;i<this->size;i++)
	if (this->elems[i].date== v.getDate() && this->elems[i].time == v.getTime() && this->elems[i].getDescription == v.getDescripion() && this->elems[i].getTitle() == v.getTitle() && this->elems[i].getLink() == v.getLink() && this->elems[i].getPeople() == v.getPeople())
		return true;
	return false;
}*/


//this function adds the element to the dynamic vector
template <typename T>
int DynamicVector<T>::add(T e)
{
	int ok = 1;
	for (int i = 0; i < this->size&&ok==1; i++)
		if (equal(e, i) == 1)
		{
			ok = 0;
		}
	if (ok == 1)
	{
		if (this->size == this->capacity)
			this->resize(2);
		this->elems[this->size] = e;
		this->size++;
		ok = 1;
	}
	return ok;
}

//this function resizes the dynamic vector
template <typename T>
void DynamicVector<T>::resize(int factor)
{
	this->capacity *= factor;

	T* els = new T[this->capacity];
	for (int i = 0; i < this->size; i++)
		els[i] = this->elems[i];

	delete[] this->elems;
	this->elems = els;
}

//this function returns the size of the dynamic vector
template <typename T>
int DynamicVector<T>::getSize() const
{
	return this->size;
}

//this function checks if two elements of type Event are equal
template<typename T>
int DynamicVector<T>::equal(T v, int pos)
{
	
	if (this->elems[pos].getDate() == v.getDate() && this->elems[pos].getTime() == v.getTime() && this->elems[pos].getDescription() == v.getDescription() && this->elems[pos].getTitle() == v.getTitle() && this->elems[pos].getLink() == v.getLink() && this->elems[pos].getNrPeople() == v.getNrPeople())
			return 1;
	return 0;
}

//this function removes an element T from the dynamic vector
template<typename T>
int DynamicVector<T>::remove(T e)
{
	
	int i = 0, ok = 0;
	for (i = 0; i < this->size && ok == 0; i++)
		if (equal(e, i) == 1)
			ok = 1;
	if (ok == 1)
	{
		this->elems[i - 1] = this->elems[this->size - 1];
		this->size--;
	}
	return ok;

}

//this function updates an element from the dynamic vector
template <typename T>
int DynamicVector<T>::update(const std::string& old_title, const std::string& old_descr,T e)
{
	for (int i = 0; i < this->size; i++)
		if (this->elems[i].getTitle()==old_title && this->elems[i].getDescription()==old_descr)
		{
			this->elems[i] = e;
			return 1;

		}
	return 0;
}






