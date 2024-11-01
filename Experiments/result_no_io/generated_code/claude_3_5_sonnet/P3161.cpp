#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 15
#define MAX_T 100000

typedef struct {
    int t, g, m;
} Order;

int cmp(const void *a, const void *b) {
    return ((Order*)a)->t - ((Order*)b)->t;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    int n;
    scanf("%d", &n);

    Order orders[MAX_N];
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d", &orders[i].t, &orders[i].g, &orders[i].m);
    }

    qsort(orders, n, sizeof(Order), cmp);

    long long dp[MAX_T + 1] = {0};
    int max_t = orders[n-1].t;
    int production = 1;
    int goods = 0;

    for (int t = 1; t <= max_t; t++) {
        dp[t] = dp[t-1];
        
        if (goods < production) {
            goods += production;
        } else {
            production++;
        }

        for (int i = 0; i < n; i++) {
            if (orders[i].t == t && goods >= orders[i].g) {
                dp[t] = max(dp[t], dp[t-1] + orders[i].m);
                goods -= orders[i].g;
            }
        }
    }

    printf("%lld\n", dp[max_t]);

    return 0;
}