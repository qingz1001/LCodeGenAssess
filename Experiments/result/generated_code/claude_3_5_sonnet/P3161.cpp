#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 15
#define MAX_T 100001

typedef long long ll;

struct Order {
    int t, g;
    ll m;
};

int n;
struct Order orders[MAX_N];
ll dp[MAX_T];

int cmp(const void *a, const void *b) {
    return ((struct Order*)a)->t - ((struct Order*)b)->t;
}

ll max(ll a, ll b) {
    return a > b ? a : b;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d %lld", &orders[i].t, &orders[i].g, &orders[i].m);
    }

    qsort(orders, n, sizeof(struct Order), cmp);

    memset(dp, 0, sizeof(dp));
    int max_t = orders[n-1].t;
    ll production = 0, productivity = 1;

    for (int t = 1, j = 0; t <= max_t; t++) {
        dp[t] = dp[t-1];
        production += productivity;

        while (j < n && orders[j].t == t) {
            if (production >= orders[j].g) {
                dp[t] = max(dp[t], dp[t] + orders[j].m);
                production -= orders[j].g;
            }
            j++;
        }

        dp[t] = max(dp[t], dp[t-1]);
        if (production < productivity) {
            productivity++;
        } else {
            production -= productivity;
            productivity++;
        }
    }

    printf("%lld\n", dp[max_t]);
    return 0;
}