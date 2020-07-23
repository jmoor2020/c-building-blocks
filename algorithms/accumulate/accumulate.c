// accumulate.c
// Accumulate algotithm on integer arrays.

#include "accumulate.h"

int accumulate(
    int array[],
    size_t first,
    size_t last,
    int start,
    binary_op_f op)
{
    if (array == NULL || first >= last){
      return 0;
    }
    int accum = start;
    for (int i=first; i<last; i++){ //declare i in the for loop
      accum = op(accum, array[i]);
    }
    return accum;
}
