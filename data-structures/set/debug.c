#include "set.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

typedef struct point {
  uint64_t x;
  uint64_t y;
} point_t;

typedef uint64_t hash_t; //allows me to change what hash_t is in once place.

void deleter(void* data){
  free(data);
  return;
}

hash_t hasher(void* data){
  point_t* as_point = (point_t*)data;
  return (as_point->x);
}

void iterator(void* data){
  point_t* as_point = (point_t*)data;
  as_point->x += 1;
  as_point->y += 1;
  return;
}

int main(){
  set_t* set = set_new(deleter, hasher);
  point_t* p1 = malloc(sizeof(point_t));
  p1->x = 5;
  p1->y = 5;
  point_t* p2 = malloc(sizeof(point_t));
  p2->x = 7;
  p2->y = 7;
  point_t* p3 = malloc(sizeof(point_t));
  p3->x = 5;
  p3->y = 5;

  set_add(set, p1);
  set_contains(set, p3);
  set_add(set, p2);
  set_for_each(set, iterator);
  set_add(set, p3);
  set_remove(set, p2);
  free(p2);
  set_remove(set, p1);
  free(p1);
  set_delete(set);
}
