#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int t, g, m;
} Order;

int compare(const void *a, const void *b) {
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

    qsort(orders, n, sizeof(Order), compare);

    int dp[n + 1][101];
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= 100; j++) {
            dp[i][j] = -1;
        }
    }
    dp[0][1] = 0;

    for (int i = 0; i < n; i++) {
        for (int p = 1; p <= 100; p++) {
            if (dp[i][p] == -1) continue;
            int current_time = orders[i].t;
            int current_production = p;
            int current_goods = dp[i][p];

            // Option 1: Increase production
            int new_production = current_production + 1;
            int new_time = current_time + 1;
            if (new_time <= orders[i].t) {
                dp[i + 1][new_production] = max(dp[i + 1][new_production], current_goods);
            }

            // Option 2: Produce goods
            int new_goods = current_goods + current_production;
            new_time = current_time + 1;
            if (new_time <= orders[i].t) {
                dp[i + 1][current_production] = max(dp[i + 1][current_production], new_goods);
            }

            // Option 3: Accept order
            if (current_goods >= orders[i].g) {
                int new_goods_after_order = current_goods - orders[i].g;
                dp[i + 1][current_production] = max(dp[i + 1][current_production], new_goods_after_order + orders[i].m);
            }
        }
    }

    int max_income = 0;
    for (int p = 1; p <= 100; p++) {
        max_income = max(max_income, dp[n][p]);
    }

    printf("%d\n", max_income);
    return 0;
}