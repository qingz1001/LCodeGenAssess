#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int*)b - *(int*)a);
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    int prices[1000];
    for (int i = 0; i < m; i++) {
        scanf("%d", &prices[i]);
    }

    qsort(prices, m, sizeof(int), compare);

    int max_revenue = 0;
    int best_price = 0;

    for (int i = 0; i < m && i < n; i++) {
        int current_revenue = prices[i] * (i + 1);
        if (current_revenue > max_revenue) {
            max_revenue = current_revenue;
            best_price = prices[i];
        }
    }

    printf("%d %d\n", best_price, max_revenue);

    return 0;
}