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

    long long dp[n + 1];
    dp[0] = 0;
    for (int i = 1; i <= n; i++) {
        dp[i] = dp[i - 1];
        for (int j = i - 1; j >= 0; j--) {
            if (orders[i - 1].t - orders[j].t >= orders[i - 1].g) {
                dp[i] = (dp[i] > dp[j] + orders[i - 1].m) ? dp[i] : dp[j] + orders[i - 1].m;
            } else {
                break;
            }
        }
    }

    long long max_profit = 0;
    for (int i = 1; i <= n; i++) {
        max_profit = (max_profit > dp[i]) ? max_profit : dp[i];
    }

    printf("%lld\n", max_profit);
    return 0;
}