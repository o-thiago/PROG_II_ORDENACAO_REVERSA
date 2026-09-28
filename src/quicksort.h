#ifndef QUICKSORT_H
#define QUICKSORT_H

#include <stdbool.h>

enum pivot_method {
    PIVOT_METHOD_NAIVE,
    PIVOT_METHOD_MID,
};

bool quicksort(int *v, int n, enum pivot_method pivot_method);

#endif // QUICKSORT_H
