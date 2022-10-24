#include "Repository.h"
#include<string.h>
#include "DynamicVector.h"
#include "Offer.h"
#include<assert.h>
#include<stdlib.h>

Repository* create_repo()
{

    Repository* repo = (Repository*)(malloc(sizeof(Repository)));
    if (repo == NULL)
        return NULL;

    repo->v = create_vector(100);
    
    
    return repo;



}




void destroy_repo(Repository* repo)
{
  if (repo == NULL)
     return;
  
  if (repo->v != NULL)
      destroy_vector(repo->v);

  free(repo);
  //repo = NULL;


}

int length_repo(Repository* repo)
{
    if (repo == NULL)
        return -1;
    return length_vector(repo->v);
}

void sort_vector(DynamicVector* v)
{
    Offer* aux;
    for (int i = 0; i < v->size - 1; i++)
        for (int j = i + 1; j < v->size; j++)
            if (get_price(v->elems[i])> get_price(v->elems[j])) {
                aux = v->elems[i];
                v->elems[i] =v->elems[j];
                v->elems[j] = aux;
            }

}

Offer* get_offer_on_pos(Repository *repo,int position)
{
    if (repo == NULL)
        return NULL;
    return get(repo->v, position);

}

int add_offer_repo(Repository* repo, Offer* o)
{   
    Offer* current_o;
    if (o == NULL)
        return 0;

    for (int i = 0; i < length_vector(repo->v); i++)
    {
        current_o = get_offer_on_pos(repo, i);
        // printf("%s", current_o->type);
        if (current_o == NULL)
            return 0;
        if ((strcmp(current_o->destination, o->destination) == 0) && (strcmp(current_o->date,o->date)==0))
            return 0;
    }
    Offer* cpy_offer = copy_offer(o);
    if (cpy_offer == NULL)
        return 0;

    add_element(repo->v, cpy_offer);

    return 1;
        

}

Offer* find_by_destination_date(Repository* repo, char* destination, char* date)
{
    if (repo == NULL || destination == NULL || date == NULL)
        return NULL;

    for (int i = 0; i < length_vector(repo->v); i++) {
        Offer* o = get_offer_on_pos(repo, i);
        if (strcmp(get_destination(o), destination) == 0 && strcmp(get_date(o), date) == 0) {
            return o;
        }
    }
    return NULL;

}


int delete_offer_repo(Repository* repo, char* destination, char* date)
{
    if (repo == NULL || destination==NULL || date == NULL)
        return -1;

    Offer* o = find_by_destination_date(repo, destination, date);
    for (int i = 0; i < length_vector(repo->v); i++)
    {
        Offer* current_offer = get(repo->v, i);
        if (current_offer == o)
        {
            delete(repo->v, i);
            return 0;
        }
    }
    return -1;
    
}





int update_offer_repo(Repository* repo, char* destination_init, char* date_init, char* type, char* destination, char* date, int price)
{
    if (repo == NULL || destination_init == NULL || date_init == NULL || type == NULL || destination == NULL || date == NULL)
        return 0;

    for (int i = 0; i < length_repo(repo); i++)

    {
        //Offer* current_offer = get_offer_on_pos(repo, i);
        Offer* current_offer = get(repo->v, i);
        if (strcmp(get_destination(current_offer), destination_init) == 0 && strcmp(get_date(current_offer), date_init) == 0)
        {
            strcpy(current_offer->date , date);
            strcpy(current_offer->destination ,destination);
            strcpy(current_offer->type , type);
            current_offer->price = price;
            return 1;

        }

    }
    return 0;
    
}

void test_repo()
{
    Repository* repo = create_repo();
    Offer* o1 = create_offer("seaside", "Malibu", "12-12-2022", 1000);
    Offer* o2 = create_offer("mountain", "Everest", "12-07-2022", 900);
    Offer* o3 = create_offer("city - break", "Verona", "01-01-2023", 850);
    add_offer_repo(repo, o1);
    add_offer_repo(repo, o2);
    add_offer_repo(repo, o3);
    assert(length_repo(repo) == 3);
    assert(strcmp(get_type(get_offer_on_pos(repo, 1)), "mountain") == 0);
    assert(delete_offer_repo(repo, "Turkey", "09-09-2002") == -1);
    assert(delete_offer_repo(repo, "Everest", "12 - 07 - 2022") == 0);
    assert(find_by_destination_date(repo, "Malibu", "12-12-2022") == get_offer_on_pos(repo, 0));
    update_offer_repo(repo, "Verona", "01-01-2023", "seaside", "Antalya", "03-05-2022", 150000);
    assert((strcmp(get_type(get_offer_on_pos(repo, 1)), "seaside") == 0));
    assert((strcmp(get_destination(get_offer_on_pos(repo, 1)), "Antalya") == 0));
    destroy_repo(repo);




}

