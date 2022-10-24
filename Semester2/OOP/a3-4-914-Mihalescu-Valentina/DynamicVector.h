#pragma once
#include "Offer.h"
#include<stdlib.h>

typedef void* Telem;


typedef struct
{
	int size, capacity;
	Telem* elems;



} DynamicVector;

DynamicVector* create_vector(int capacity);
void destroy_vector(DynamicVector* v);

int add_element(DynamicVector* v,Telem elem);
void test_dynamic_vector();
int length_vector(DynamicVector* v);
Telem get(DynamicVector* v,int position);
void delete(DynamicVector* arr, int pos);