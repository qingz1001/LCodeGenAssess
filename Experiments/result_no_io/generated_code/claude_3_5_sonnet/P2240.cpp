#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100

typedef struct {
    int weight;
    int value;
    double ratio;
} GoldPile;

int compare(const void *a, const void *b) {
    GoldPile *pileA = (GoldPile *)a;
    GoldPile *pileB = (GoldPile *)b;
    if (pileB->ratio > pileA->ratio) return 1;
    if (pileB->ratio < pileA->ratio) return -1;
    return 0;
}

int main() {
    int N, T;
    GoldPile piles[MAX_N];
    
    scanf("%d %d", &N, &T);
    
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &piles[i].weight, &piles[i].value);
        piles[i].ratio = (double)piles[i].value / piles[i].weight;
    }
    
    qsort(piles, N, sizeof(GoldPile), compare);
    
    double totalValue = 0.0;
    int remainingCapacity = T;
    
    for (int i = 0; i < N && remainingCapacity > 0; i++) {
        if (remainingCapacity >= piles[i].weight) {
            totalValue += piles[i].value;
            remainingCapacity -= piles[i].weight;
        } else {
            totalValue += piles[i].ratio * remainingCapacity;
            remainingCapacity = 0;
        }
    }
    
    printf("%.2f\n", totalValue);
    
    return 0;
}