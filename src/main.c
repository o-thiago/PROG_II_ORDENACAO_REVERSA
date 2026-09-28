/*
 * RESULTADOS PIOR CASO (16 rodadas, 32768 elementos por rodada, conjunto já
 * ordenado decrescente): Quicksort (pivô ingenuo)  | Tempo Medio: 1.438310 s |
 * Tempo Total: 23.012968 s Quicksort (pivô central)  | Tempo Medio: 0.000776 s
 * | Tempo Total:  0.012408 s Mergesort                 | Tempo Medio: 0.000180
 * s | Tempo Total:  0.002875 s Heapsort                  | Tempo Medio:
 * 0.003455 s | Tempo Total:  0.055286 s
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "algorithm.h"

enum {
    SHIFT_MAX = 15,
    NUMERO_MAXIMO = (int)(1U << (unsigned int)SHIFT_MAX),
    NUM_RODADAS = 16,
    TABELA_TAMANHO = 63,
};

static void print_separator(void)
{
    for (int i = 0; i < TABELA_TAMANHO; i++) (void)putchar('=');
    (void)putchar('\n');
}

static double get_elapsed_seconds(const struct timespec *start,
                                  const struct timespec *end)
{
    return (double)(end->tv_sec - start->tv_sec) +
           ((double)(end->tv_nsec - start->tv_nsec) / 1e9);
}

int main(void)
{
    constexpr int n = NUMERO_MAXIMO;

    int *work = malloc((size_t)(n + 1) * sizeof(int));
    if (!work) {
        (void)fprintf(stderr, "Erro ao alocar memoria para %d elementos.\n", n);
        return 1;
    }

    const char *nomes[ALGORITHM_COUNT] = {
        [ALGORITHM_QUICKSORT_NAIVE] = "Quicksort (pivô ingenuo)",
        [ALGORITHM_QUICKSORT_MID] = "Quicksort (pivô central)",
        [ALGORITHM_MERGESORT] = "Mergesort",
        [ALGORITHM_HEAPSORT] = "Heapsort",
    };

    double tempo_total[ALGORITHM_COUNT] = {0};

    printf("Elementos por rodada: %d (1 << %d)\n", n, SHIFT_MAX);
    printf("Numero de rodadas:    %d\n\n", NUM_RODADAS);

    for (int r = 0; r < NUM_RODADAS; r++) {
        printf("Rodada %2d/%d: ", r + 1, NUM_RODADAS);
        (void)fflush(stdout);

        for (int a = 0; a < ALGORITHM_COUNT; a++) {
            const auto algo = (enum algorithm)a;

            if (algo == ALGORITHM_HEAPSORT)
                for (int i = 1; i <= n; i++) work[i] = n - i + 1;
            else
                for (int i = 0; i < n; i++) work[i] = n - i;

            struct timespec start;
            struct timespec end;

            (void)timespec_get(&start, TIME_UTC);
            algorithm_run(algo, work, n);
            (void)timespec_get(&end, TIME_UTC);

            tempo_total[a] += get_elapsed_seconds(&start, &end);
        }

        printf("concluida\n");
    }

    (void)putchar('\n');

    print_separator();
    puts("RESULTADOS MEDIOS:");
    printf("%-26s | %-16s | %-16s\n", "Algoritmo", "Tempo Medio (s)",
           "Tempo Total (s)");

    for (int a = 0; a < ALGORITHM_COUNT; a++) {
        const double media = tempo_total[a] / (double)NUM_RODADAS;
        printf("%-26s | %13.6f s  | %13.6f s\n", nomes[a], media,
               tempo_total[a]);
    }

    print_separator();

    free(work);
    return 0;
}
