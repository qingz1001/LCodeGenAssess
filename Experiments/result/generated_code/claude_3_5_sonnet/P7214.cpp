#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_N 1000000
#define MAX_M 100000

typedef struct {
    int t, l, r, c;
} Plan;

int n, m;
Plan plans[MAX_M];
int dp[MAX_N + 1];

int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int cmp(const void *a, const void *b) {
    return ((Plan*)a)->t - ((Plan*)b)->t;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d %d", &plans[i].t, &plans[i].l, &plans[i].r, &plans[i].c);
    }

    qsort(plans, m, sizeof(Plan), cmp);

    memset(dp, 0x3f, sizeof(dp));
    dp[0] = 0;

    for (int i = 0; i < m; i++) {
        int l = plans[i].l, r = plans[i].r, c = plans[i].c;
        int prev_l = max(0, l - (plans[i].t - (i > 0 ? plans[i-1].t : 0)));
        int prev_r = min(n, r + (plans[i].t - (i > 0 ? plans[i-1].t : 0)));

        for (int j = prev_l; j <= prev_r; j++) {
            int new_l = max(j, l);
            int new_r = min(n, min(j + r - l + 1, r));
            dp[new_r] = min(dp[new_r], dp[j] + c);
        }
    }

    if (dp[n] == 0x3f3f3f3f) {
        printf("-1\n");
    } else {
        printf("%d\n", dp[n]);
    }

    return 0;
}