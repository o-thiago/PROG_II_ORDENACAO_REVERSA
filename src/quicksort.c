#include "quicksort.h"
#include "utils.h"

static int get_pivot_index(const int l, const int r,
                           const enum pivot_method pivot_method)
{
    switch (pivot_method) {
    case PIVOT_METHOD_NAIVE:
        return r;
    case PIVOT_METHOD_MID:
        return l + ((r - l) / 2);
    default:
        __builtin_unreachable();
    };
}

static int partition(int *v, const int l, const int r,
                     const enum pivot_method pivot_method)
{
    if (l >= r || l < 0) return l;

    if (pivot_method != PIVOT_METHOD_NAIVE)
        swap(&v[get_pivot_index(l, r, pivot_method)], &v[r]);

    const int pivot = v[r];
    int i = l;

    for (int j = l; j < r; j++)
        if (v[j] >= pivot) swap(&v[i++], &v[j]);

    swap(&v[i], &v[r]);
    return i;
}

static void quick_sort_internal(int *v, const int l, const int r,
                                const enum pivot_method pivot_method)
{
    if (l >= r || l < 0) return;

    const int j = partition(v, l, r, pivot_method);

    if (j > l) quick_sort_internal(v, l, j - 1, pivot_method);
    if (j < r) quick_sort_internal(v, j + 1, r, pivot_method);
}

bool quicksort(int *v, const int n, const enum pivot_method pivot_method)
{
    if (!v || n < 0) return false;
    if (n <= 1) return true;

    quick_sort_internal(v, 0, n - 1, pivot_method);
    return true;
}
