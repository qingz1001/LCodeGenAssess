#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int price;
    int amount;
} Farmer;

int compare(const void *a, const void *b) {
    return ((Farmer *)b)->price - ((Farmer *)a)->price;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    Farmer farmers[m];
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &farmers[i].price, &farmers[i].amount);
    }

    qsort(farmers, m, sizeof(Farmer), compare);

    int total_cost = 0;
    for (int i = 0; i < m && n > 0; i++) {
        if (n >= farmers[i].amount) {
            total_cost += farmers[i].price * farmers[i].amount;
            n -= farmers[i].amount;
        } else {
            total_cost += farmers[i].price * n;
            n = 0;
        }
    }

    printf("%d\n", total_cost);

    return 0;
}