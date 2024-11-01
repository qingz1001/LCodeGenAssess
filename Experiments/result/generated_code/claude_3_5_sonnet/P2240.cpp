#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int weight;
    int value;
    double ratio;
} Item;

int compare(const void* a, const void* b) {
    Item* itemA = (Item*)a;
    Item* itemB = (Item*)b;
    if (itemB->ratio > itemA->ratio) return 1;
    if (itemB->ratio < itemA->ratio) return -1;
    return 0;
}

int main() {
    int N, T;
    scanf("%d %d", &N, &T);

    Item items[100];
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &items[i].weight, &items[i].value);
        items[i].ratio = (double)items[i].value / items[i].weight;
    }

    qsort(items, N, sizeof(Item), compare);

    double totalValue = 0.0;
    int remainingWeight = T;

    for (int i = 0; i < N && remainingWeight > 0; i++) {
        if (items[i].weight <= remainingWeight) {
            totalValue += items[i].value;
            remainingWeight -= items[i].weight;
        } else {
            totalValue += items[i].ratio * remainingWeight;
            remainingWeight = 0;
        }
    }

    printf("%.2f\n", totalValue);

    return 0;
}