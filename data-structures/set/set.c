// set.c
// Generic set data structure.

#include <stdlib.h>

#include "set.h"

// An individual set item.
typedef struct set_item
{
    // Pointer to next item in the internal list.
    struct set_item* next;

    // Pointer to user-provided data.
    void* data;
} set_item_t;

set_t* set_new(deleter_f deleter, hasher_f hasher)
{
    //The below checks to see if the functions sent are not NULL
    if (deleter == NULL || hasher == NULL){
      return NULL;
    }

    set_t* set = malloc(sizeof(set_t));
    if (set == NULL){
      return NULL;
    }

    set->head = NULL;
    set->deleter = deleter;
    set->hasher = hasher;
    set->count=0;

    return set;
}

void set_delete(set_t* set)
{
    if (set == NULL){
      return;
    }
    set_item_t* tempC = set->head;
    while (tempC != NULL){
      set_item_t*  temp = tempC->next;

      //need to remove the pointer to the data and the node
      set->deleter(tempC->data);
      free(tempC);

      //advance the list  
      tempC = temp;
    }

    free(set);
    set = NULL;
    return;
}

bool set_add(set_t* set, void* data)
{
    if (set == NULL){
      return false;
    }

    if (!set_contains(set, data)){

      set_item_t* newN = malloc(sizeof(set_item_t));
      if (newN == NULL){
        return false;
      }

      newN->data = data;
      newN->next = set->head;
      set->head = newN;
      set->count++;
    }
    return true;
}

bool set_remove(set_t* set, void* data)
{
    if (set == NULL || set->count == 0){
      return false;
    }
    set_item_t* tempNC = set->head;
    set_item_t* tempNP = NULL;

    if (set_contains(set, data)) {
       while (tempNC != NULL){
         if (set->hasher(tempNC->data) == set->hasher(data)) {
           set_item_t* tempD = tempNC;
           if (tempNP == NULL){
             set->head = tempNC->next;
           }
           else{
             tempNP->next = tempNC->next;
           }
           free(tempD);
           return true;
         }
         else{
           tempNP = tempNC;
           tempNC = tempNC->next;
         }
       }
    }

    return true;
}

bool set_contains(set_t* set, void* data)
{
    if (set == NULL || set->count == 0){
      return false;
    }

    set_item_t* tempN = set->head; //did not need to use malloc, when I can set
    //tempN directly to set->head.
    //In this instance, I do not need to allocate memory to a new node.

    while (tempN != NULL){
      if (set->hasher(tempN->data) == set->hasher(data)){
        return true;
      }
      else {
        tempN = tempN->next;
      }
    }

    return false;
}

size_t set_count(set_t* set)
{
    if (set == NULL){
      return 0;
    }
    return set->count;
}

void set_for_each(set_t* set, iterator_f iterator)
{
    if (set == NULL || set->count == 0){
      return;
    }
    set_item_t* tempN = set->head;
    while(tempN != NULL){
      iterator(tempN->data);
      tempN = tempN->next;
    }
    free(tempN);
    return;
}
