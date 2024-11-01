#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int weight;
    int value;
    double unit_value;
} CoinPile;

int compare(const void *a, const void *b) {
    CoinPile *pileA = (CoinPile *)a;
    CoinPile *pileB = (CoinPile *)b;
    if (pileA->unit_value < pileB->unit_value) return 1;
    if (pileA->unit_value > pileB->unit_value) return -1;
    return 0;
}

int main() {
    int N, T;
    scanf("%d %d", &N, &T);

    CoinPile *piles = (CoinPile *)malloc(N * sizeof(CoinPile));
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &piles[i].weight, &piles[i].value);
        piles[i].unit_value = (double)piles[i].value / piles[i].weight;
    }

    qsort(piles, N, sizeof(CoinPile), compare);

    double total_value = 0.0;
    for (int i = 0; i < N && T > 0; i++) {
        if (T >= piles[i].weight) {
            total_value += piles[i].value;
            T -= piles[i].weight;
        } else {
            total_value += T * piles[i].unit_value;
            T = 0;
        }
    }

    printf("%.2f\n", total_value);

    free(piles);
    return 0;
}