#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int *)b - *(int *)a);
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    int prices[m];
    for (int i = 0; i < m; i++) {
        scanf("%d", &prices[i]);
    }

    // 对价格进行降序排序
    qsort(prices, m, sizeof(int), compare);

    int max_profit = 0;
    int best_price = 0;

    // 计算每个可能的价格对应的利润
    for (int i = 0; i < m && i < n; i++) {
        int current_profit = prices[i] * (i + 1);
        if (current_profit > max_profit) {
            max_profit = current_profit;
            best_price = prices[i];
        }
    }

    printf("%d %d\n", best_price, max_profit);

    return 0;
}