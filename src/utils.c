#include "utils.h"

void swap(int *a, int *b)
{
    const int tmp = *a;
    *a = *b;
    *b = tmp;
}
