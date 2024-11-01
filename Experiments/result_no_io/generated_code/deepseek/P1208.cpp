#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int price;
    int amount;
} Farmer;

int compare(const void *a, const void *b) {
    return ((Farmer *)a)->price - ((Farmer *)b)->price;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    Farmer farmers[m];
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &farmers[i].price, &farmers[i].amount);
    }

    qsort(farmers, m, sizeof(Farmer), compare);

    int totalCost = 0;
    int remaining = n;

    for (int i = 0; i < m && remaining > 0; i++) {
        int buyAmount = (remaining < farmers[i].amount) ? remaining : farmers[i].amount;
        totalCost += buyAmount * farmers[i].price;
        remaining -= buyAmount;
    }

    printf("%d\n", totalCost);

    return 0;
}