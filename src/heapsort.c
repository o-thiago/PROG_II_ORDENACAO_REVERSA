#include "heapsort.h"

#include "utils.h"

static void build_heap(int *v, const int m)
{
    if (!v || m <= 1) return;

    for (int k = 1; k < m; k++) {
        int f = k + 1;
        while (f > 1 && v[f / 2] > v[f]) {
            swap(&v[f], &v[f / 2]);
            f /= 2;
        }
    }
}

static void heapify(int *v, const int m)
{
    if (!v || m <= 1) return;

    int f = 2;
    while (f <= m) {
        if (f < m && v[f] > v[f + 1]) f++;
        if (v[f / 2] <= v[f]) break;

        swap(&v[f], &v[f / 2]);
        if (f > m / 2) break;
        f *= 2;
    }
}

void heapsort(int *v, const int n)
{
    if (!v || n <= 1) return;

    build_heap(v, n);

    for (int m = n; m >= 2; m--) {
        swap(&v[1], &v[m]);
        heapify(v, m - 1);
    }
}
