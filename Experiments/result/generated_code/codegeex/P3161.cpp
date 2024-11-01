#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int t;
    int g;
    int m;
} Order;

int compare(const void *a, const void *b) {
    Order *orderA = (Order *)a;
    Order *orderB = (Order *)b;
    return orderA->t - orderB->t;
}

int main() {
    int n;
    scanf("%d", &n);

    Order orders[n];
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d", &orders[i].t, &orders[i].g, &orders[i].m);
    }

    qsort(orders, n, sizeof(Order), compare);

    int maxProfit = 0;
    int currentProduction = 1;
    int currentGoods = 0;

    for (int i = 0; i < n; i++) {
        int requiredGoods = orders[i].g;
        int profit = orders[i].m;

        while (currentGoods < requiredGoods) {
            currentProduction++;
            currentGoods += currentProduction;
        }

        currentGoods -= requiredGoods;
        maxProfit += profit;
    }

    printf("%d\n", maxProfit);

    return 0;
}