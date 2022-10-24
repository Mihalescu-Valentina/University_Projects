#include "Offer.h"
#include <stdlib.h>
#include<string.h>
#include<assert.h>
#include<stdio.h>


Offer* create_offer(char* type, char* destination, char* date, int price)
{
	Offer *o = malloc(sizeof(Offer));
	if (o == NULL)
		return NULL;

	o->type=malloc(sizeof(char) * (1+strlen(type)));
	if (o->type == NULL) //this means there is not enough space for type
	{
		free(o); //I deallocated the space previously allocated(p) to make space for the type
		return NULL;
	}

	o->destination= malloc(sizeof(char) * (1 + strlen(destination)));
	if (o->destination == NULL)
	{
		free(o->type);
		free(o);
		return NULL;
	}


	o->date= malloc(sizeof(char)*(1+strlen(date)));
	
	if (o->date == NULL)
	{
		free(o->type);
		free(o->destination);
		free(o);
		return NULL;
	}
	strcpy(o->type, type);
	strcpy(o->destination, destination);
	strcpy(o->date, date);
	o->price  = price;
	
	return o;

	
}

void destroy_offer(Offer* o)
{   
	if (o == NULL)
		return;
	free(o->type);
	free(o->destination);
	free(o->date);
	free(o);

}

Offer* copy_offer(Offer* o) {
	if (o == NULL)
		return NULL;
	return create_offer(o->type, o->destination, o->date,o->price);
}

char* get_type(Offer *o)
{
	if (o == NULL)
		return NULL;
	return o->type;


}

char* get_destination(Offer* o)
{
	if (o == NULL)
		return NULL;
	return o->destination;

}

char* get_date(Offer* o)
{
	if (o == NULL)
		return NULL;
	return o->date;

}

int get_price(Offer* o)
{
	if (o == NULL)
		return -1;
	return o->price;
}

void test_offer()
{
	Offer *o1 = create_offer("seaside", "Malibu", "12 - 12 - 2022", 1000);
	Offer *o2 = create_offer("mountain", "Everest", "12-07-2022", 900);
	assert(strcmp(get_type(o1), "seaside") == 0);
	assert(strcmp(get_date(o2), "12-07-2022") == 0);
	assert(strcmp(get_destination(o1), "Malibu") == 0);
	assert(get_price(o2) == 900);
}

void toString(Offer* o, char str[])
{
	if (o== NULL)
		return;
	printf("here");
	printf("%s , %s , %s" , o->type,o->destination, o->date);
	//sprintf(str, "Offer has the type %s , destination %s , departure date %s and its price is %d.", o->type, o->destination, o->date ,o->price);

}