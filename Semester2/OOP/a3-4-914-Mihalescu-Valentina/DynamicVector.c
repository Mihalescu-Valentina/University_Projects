#include "DynamicVector.h"
#include<assert.h>
#include"Offer.h"
#include<string.h>

DynamicVector* create_vector(int capacity)
{
    DynamicVector* v=(DynamicVector*)malloc(sizeof(DynamicVector));
    if (v == NULL)
        return NULL;
    v->capacity = capacity;
    v->size = 0;
    v->elems = (Telem*)malloc(sizeof(Telem) * capacity);
    if (v->elems == NULL)
    {
        free(v);
        return NULL;
    }

    return v;
}

void destroy_vector(DynamicVector* v)
{
    if (v == NULL)
        return;

    if (v->elems == NULL)
        return;
     

    for (int i = 0; i < v->size; i++)
        destroy_offer(v->elems[i]);
       
    free(v->elems);
    v->elems = NULL;
    free(v);
    v = NULL;
}

void resize(DynamicVector* v)
{
    if (v == NULL) 
        return;
    v->capacity*= 2;
    Telem* new_elems = (Telem*)malloc(sizeof(Telem) * v->capacity);
    
    for (int i = 0; i < v->size; i++)
        new_elems[i] = v->elems[i];
    
    free(v->elems);
    v->elems = new_elems;
    

}

int add_element(DynamicVector* v, Telem elem)
{   
    

    if (v == NULL)
        return 0;

    int old_capacity = v->capacity;
    if (v->size == v->capacity)

    {
        resize(v);
        if (old_capacity == v->capacity)
            return 0 ;
    }
    
    
      
    
    v->elems[v->size++] = elem;
    return 1;

    
    
    
}



int length_vector(DynamicVector* v)
{   
    if (v == NULL)
        return -1;

    return v->size;
}

Telem get(DynamicVector* v, int position)
{
    if (v == NULL || position < 0)
        return NULL;
    return v->elems[position];

}

void delete(DynamicVector* arr, int pos)
{
    if (arr == NULL || pos < 0 || pos >= arr->size)
        return;

    destroy_offer(arr->elems[pos]);

    // !!! Do this only if we delete any element but the last
    if (pos != arr->size - 1)
        arr->elems[pos] = arr->elems[arr->size - 1];
    arr->size--;

}

void test_dynamic_vector()
{
    DynamicVector* v = create_vector(2);
    assert(v->size == 0);
    Offer* o1 = create_offer("seaside", "Malibu", "12 - 12 - 2022", 1000);
    Offer* o2 = create_offer("mountain", "Everest", "12-07-2022", 900);
    Offer* o3 = create_offer("city - break", "Verona", "01 - 01 - 2023", 850);
    add_element(v, o1);
    add_element(v, o2);
    assert(v->capacity == 2);
    add_element(v, o3);
    assert(v->size == 3);
    assert(v->capacity == 4);
    destroy_vector(v);
    v = create_vector(3);
    o1 = create_offer("seaside", "Malibu", "12 - 12 - 2022", 1000);
    assert(add_element(v, o1)==1);
   
    destroy_vector(v);

    
    


}