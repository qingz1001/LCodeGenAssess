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
    
    int max_profit = 0;
    int best_price = 0;
    for (int i = 0; i < m; i++) {
        int profit = prices[i] * (m - i);
        if (profit > max_profit) {
            max_profit = profit;
            best_price = prices[i];
        } else {
            break;
        }
    }
    
    printf("%d %d\n", best_price, max_profit);
    
    return 0;
}