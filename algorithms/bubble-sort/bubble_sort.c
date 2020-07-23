// bubble_sort.c
// Bubble sort sorting algorithm.

#include "bubble_sort.h"
#include <stdio.h>

void bubble_sort(
    int array[],
    size_t begin,
    size_t end,
    policy_f should_swap)
{
    if (array == NULL || begin >= end){
      return;
    }

    for(int i=begin; i < end; i++){
      for(int j = begin; j< end; j++){
        if (should_swap(array[j], array[j+1])){
//          printf("%d - %d,", array[j],array[j+1]);
          int temp = array[j+1];
          array[j+1]=array[j];
          array[j]=temp;
//          printf("%d - %d \n", array[j], array[j+1]);
        }

      }
//      printf("end of list \n");
    }

    return;
}
