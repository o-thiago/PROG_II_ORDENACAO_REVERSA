#include "mergesort.h"

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/*
 * Para reduzir a sobrecarga de chamadas recursivas nos níveis mais profundos
 * da árvore de recursão, adotei a técnica descrita no livro de Cormen et al.
 * (Algoritmos: Teoria e Prática): subvetores com tamanho menor ou igual a
 * INSERTION_SORT_CUTOFF são ordenados via Insertion Sort, que apresenta menor
 * constante multiplicativa e melhor localidade de referência para entradas
 * pequenas.
 *
 * Nota: vi isso enquanto estava estudando, mas visto que esta abordagem se
 * diverge da implementação do slide decidi por deixar comentada apenas para
 * fins de comprovação.
 */
// enum { INSERTION_SORT_CUTOFF = 32 };
//
// static void insertion_sort(const int p, const int r, int *v)
// {
//     for (int i = p + 1; i < r; ++i) {
//         const int key = v[i];
//         int j = i;
//
//         while (j > p && v[j - 1] < key) {
//             v[j] = v[j - 1];
//             --j;
//         }
//
//         v[j] = key;
//     }
// }

static void merge(const int l, const int mid, const int r, int *v, int *aux)
{
    if (l < 0 || mid < l || r < mid) return;

    int i = l;
    int j = mid;
    int k = 0;

    while (i < mid && j < r) aux[k++] = (v[i] >= v[j]) ? v[i++] : v[j++];
    while (i < mid) aux[k++] = v[i++];
    while (j < r) aux[k++] = v[j++];

    memcpy(&v[l], aux, (size_t)(r - l) * sizeof(int));
}

static void mergesort_internal(const int l, const int r, int *v, int *aux)
{
    if (r - l <= 1) return;
    // if (r - l <= INSERTION_SORT_CUTOFF) {
    //     insertion_sort(l, r, v);
    //     return;
    // }

    const int mid = l + ((r - l) / 2);

    mergesort_internal(l, mid, v, aux);
    mergesort_internal(mid, r, v, aux);

    /*
     * Se v[mid - 1] >= v[mid], as partições [l, mid) e [mid, r) já estão
     * ordenadas de forma contígua em ordem decrescente.
     *
     * Como v[mid - 1] é o menor elemento de [l, mid) e v[mid] é o maior
     * elemento de [mid, r), por transitividade qualquer elemento de [l, mid)
     * é maior ou igual a qualquer elemento de [mid, r), tornando o merge
     * redundante.
     */
    if (v[mid - 1] >= v[mid]) return;
    merge(l, mid, r, v, aux);
}

bool mergesort(int *v, const int n)
{
    if (!v || n < 0) return false;
    if (n <= 1) return true;
    // if (n <= INSERTION_SORT_CUTOFF) {
    //     insertion_sort(0, n, v);
    //     return true;
    // }

    if ((size_t)n > SIZE_MAX / sizeof(int)) return false;

    /**
     * Ao invés de alocarmos um VLA que vive na stack para cada call recursiva
     * de mergesort, aloquei um array auxiliar com o número exato de elementos
     * necessários.
     *
     * Além disso, enquanto pesquisava, notei que com algumas mudanças ainda
     * seria possível fazer uma implementação mais robusta usando espaço
     * auxiliar O(n / 2), mas esta se distanciaria muito do modelo mental dos
     * códigos do slide.
     *
     * A versão deste código mantém a mesma lógica central dos algoritmos dos
     * slides, mas usa alguns pequenos truques de otimização com memcpy e afins.
     */
    int *aux = malloc((size_t)n * sizeof(int));
    if (!aux) return false;

    mergesort_internal(0, n, v, aux);

    free(aux);
    return true;
}
