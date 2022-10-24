#pragma once
#include "DynamicVector.h"
typedef struct {

	DynamicVector* v;
	

}Repository;

Repository* create_repo();

void destroy_repo(Repository* repo);



int delete_offer_repo(Repository* repo, char *destination, char *date);

int update_offer_repo(Repository* repo,char *destination_init,char *date_init, char* type, char* destination, char* date, int price);

int length_vector(DynamicVector* v);
Offer* get_offer_on_pos(Repository* repo, int position);
int add_offer_repo(Repository* repo, Offer* o);

Offer* find_by_destination_date(Repository* repo, char* destination, char* date);
int length_repo(Repository* repo);
void sort_vector(DynamicVector* v);
