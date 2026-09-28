#ifndef ALGORITHM_H
#define ALGORITHM_H

enum algorithm {
    ALGORITHM_QUICKSORT_NAIVE,
    ALGORITHM_QUICKSORT_MID,
    ALGORITHM_MERGESORT,
    ALGORITHM_HEAPSORT,
    ALGORITHM_COUNT,
};

void algorithm_run(enum algorithm algo, int *v, int n);

#endif // ALGORITHM_H
