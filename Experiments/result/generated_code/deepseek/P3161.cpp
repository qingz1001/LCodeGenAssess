#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int t, g, m;
} Order;

int compareOrders(const void *a, const void *b) {
    return ((Order *)a)->t - ((Order *)b)->t;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    int n;
    scanf("%d", &n);
    Order orders[n];
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d", &orders[i].t, &orders[i].g, &orders[i].m);
    }

    // Sort orders by time
    qsort(orders, n, sizeof(Order), compareOrders);

    int dp[n + 1];
    dp[0] = 0;

    for (int i = 1; i <= n; i++) {
        int production = 1;
        int goods = 0;
        dp[i] = dp[i - 1];

        for (int j = i - 1; j >= 0; j--) {
            int time_diff = orders[i - 1].t - (j > 0 ? orders[j - 1].t : 0);
            goods += production * time_diff;
            production++;

            if (goods >= orders[i - 1].g) {
                dp[i] = max(dp[i], dp[j] + orders[i - 1].m);
            }
        }
    }

    printf("%d\n", dp[n]);
    return 0;
}