#include "algorithm.h"

#include "heapsort.h"
#include "mergesort.h"
#include "quicksort.h"

void algorithm_run(const enum algorithm algo, int *v, const int n)
{
    switch (algo) {
    case ALGORITHM_QUICKSORT_NAIVE:
        (void)quicksort(v, n, PIVOT_METHOD_NAIVE);
        break;
    case ALGORITHM_QUICKSORT_MID:
        (void)quicksort(v, n, PIVOT_METHOD_MID);
        break;
    case ALGORITHM_MERGESORT:
        (void)mergesort(v, n);
        break;
    case ALGORITHM_HEAPSORT:
        heapsort(v, n);
        break;
    case ALGORITHM_COUNT:
    default:
        break;
    }
}
