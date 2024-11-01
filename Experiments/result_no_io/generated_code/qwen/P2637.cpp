#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    int prices[m];
    for (int i = 0; i < m; i++) {
        scanf("%d", &prices[i]);
    }

    qsort(prices, m, sizeof(int), compare);

    int maxProfit = 0;
    int bestPrice = 0;

    for (int i = 0; i < m; i++) {
        int profit = prices[i] * (m - i);
        if (profit > maxProfit) {
            maxProfit = profit;
            bestPrice = prices[i];
        }
    }

    printf("%d %d\n", bestPrice, maxProfit);

    return 0;
}