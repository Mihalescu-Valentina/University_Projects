#include "DynamicVector.h"

/*DynamicVector::DynamicVector(int capacity) : capacity{capacity}, size{0}
{
	elems = new TElem[this->capacity];
}

void DynamicVector::resize()
{

	this->capacity *= 2;
	TElem* aux_array = new TElem[this->capacity];
	for (int i = 0; i < this->size; i++) {
		aux_array[i] = this->elems[i];
	}
	delete[] this->elems;
	this->elems = aux_array;

}

DynamicVector::DynamicVector(const DynamicVector&v)
{
	this->capacity = v.capacity;
	this->size = v.size;
	this->elems = new TElem[this->capacity];
	for (int i = 0; i < v.size; i++)
		this->elems[i] = v.elems[i];

}

DynamicVector& DynamicVector::operator=(const DynamicVector& v)
{
	if (this == &v)
		return *this;

	this->capacity = v.capacity;
	this->size = v.size;
	delete[] this->elems;
	this->elems = new TElem[this->capacity];
	for (int i = 0; i < v.size; i++)
		this->elems[i] = v.elems[i];

	return *this;
}



void DynamicVector::add(TElem s)
{
	if (this->size == this->capacity) {
		resize();
	}

	this->elems[size] = s;
	this->size++;
}

int DynamicVector::getSize() const
{
	return this->size;
}

DynamicVector::~DynamicVector()
{
	delete[] this->elems;
}*/