#include <stdio.h>
#include <stdlib.h>

#define MAXN 15
#define MAXM 1000000000

typedef struct {
    int t, g, m;
} Order;

int main() {
    int n;
    scanf("%d", &n);
    Order orders[MAXN];
    for (int i = 0; i < n; ++i) {
        scanf("%d %d %d", &orders[i].t, &orders[i].g, &orders[i].m);
    }

    // Sort orders by time
    qsort(orders, n, sizeof(Order), [](const void *a, const void *b) {
        return ((Order *)a)->t - ((Order *)b)->t;
    });

    int dp[MAXM + 1];
    for (int i = 0; i <= MAXM; ++i) {
        dp[i] = -1;
    }
    dp[0] = 0;

    for (int i = 0; i < n; ++i) {
        int t = orders[i].t;
        int g = orders[i].g;
        int m = orders[i].m;
        for (int j = MAXM; j >= 0; --j) {
            if (dp[j] != -1 && j + g <= MAXM) {
                dp[j + g] = dp[j] + m;
            }
        }
    }

    int max_income = 0;
    for (int i = 0; i <= MAXM; ++i) {
        if (dp[i] != -1) {
            max_income = dp[i];
        }
    }

    printf("%d\n", max_income);
    return 0;
}