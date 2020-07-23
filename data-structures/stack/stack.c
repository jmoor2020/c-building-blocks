// stack.c
// Generic stack (last in, first out) data structure.

#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

// An individual item on the stack.
typedef struct stack_item
{
    // A pointer to the item below this on the stack.
    struct stack_item* below;

    // A pointer to arbitrary user-provided data.
    void* data;
} stack_item_t;

lstack_t* stack_new(void)
{
    stack_t *stack;
    stack = malloc(sizeof(stack_t));
    if (stack == NULL){
      return NULL;
    }
    stack->count = 0;
    stack->top = NULL;
    return stack;
}

bool stack_delete(lstack_t* stack)
{
    if (stack == NULL || stack->count > 0){
      return false;
    }
    free(stack); //free says go to the memory that the address points to stands
    //and free it.  It does NOT free the pointer to the data.  Only the data.
    //Now need to free the pointer by setting it to NULL.
    stack = NULL;
    return true;
}

bool stack_push(lstack_t* stack, void* data)
{
    if (stack == NULL){
      return false;
    }

    stack_item_t *newi = malloc(sizeof(stack_item_t));
    if (newi == NULL){
      return false;
    }
/*    void* tempi = malloc(sizeof(void*)); //don't need to allocate memory
                                           //don't even need a temp var for
                                           //a pointer
    if (tempi == NULL){
      free(newi);
      return false;
    }*/

//    void* tempi = data;  //don't need to do this because pointers are primitive
//types
    newi->data = data;
    if (stack->count == 0){
      newi->below = NULL;
      stack->top=newi;
    }
    else {
      newi->below = stack->top;
      stack->top = newi;
    }
    stack->count++;
    return true;
}

void* stack_pop(lstack_t* stack)
{
    if (stack == NULL){
      return NULL;
    }
    if (stack->count == 0){
      return NULL;
    }

/*    void* item = malloc(sizeof(void*));
    if (item == NULL){
      return NULL;
    }
*/ //Don't need to allocate  memory because the data is in memory
    void* item = stack->top->data; //do it this way
    stack->top = stack->top->below; //why not this way
//    stack_item_t* temp = stack->top->below; //why this way?
//    stack->top = temp;
//    free(temp);//free this memory after it is used.
    stack->count--;
    return item;
}

void* stack_peek(lstack_t* stack)
{
    if (stack == NULL){
      return NULL;
    }
    if (stack->count == 0){
      return NULL;
    }
/*    void* item = malloc(sizeof(void*));
    if (item == NULL){
      return NULL;
    } */
    void* item = stack->top->data;
//    printf("%p", item);
    return item;
}

size_t stack_count(lstack_t* stack)
{
<<<<<<< HEAD
    if (stack == NULL){
      return 0;
    }
    return stack->count;
=======
    return 0;
>>>>>>> upstream/master
}
