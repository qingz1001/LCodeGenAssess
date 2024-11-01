#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double weight;
    double value;
} Item;

int compare(const void *a, const void *b) {
    return ((Item *)b)->value / ((Item *)b)->weight - ((Item *)a)->value / ((Item *)a)->weight;
}

double fractionalKnapsack(int N, int T, Item items[]) {
    qsort(items, N, sizeof(Item), compare);
    double totalValue = 0.0;
    for (int i = 0; i < N && T > 0; i++) {
        if (items[i].weight <= T) {
            totalValue += items[i].value;
            T -= items[i].weight;
        } else {
            totalValue += items[i].value * (double)T / items[i].weight;
            break;
        }
    }
    return totalValue;
}

int main() {
    int N, T;
    scanf("%d %d", &N, &T);
    Item items[N];
    for (int i = 0; i < N; i++) {
        scanf("%lf %lf", &items[i].weight, &items[i].value);
    }
    printf("%.2f\n", fractionalKnapsack(N, T, items));
    return 0;
}