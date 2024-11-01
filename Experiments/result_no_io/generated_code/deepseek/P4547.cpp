#include <stdio.h>
#include <stdlib.h>

#define MOD 1000000007
#define MAXN 15

typedef long long ll;

int n, m;
int edges[MAXN * MAXN][4];
int dp[1 << MAXN];

int mod(ll x) {
    return (x % MOD + MOD) % MOD;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++) {
        int t;
        scanf("%d", &t);
        if (t == 0) {
            scanf("%d %d", &edges[i][0], &edges[i][1]);
            edges[i][2] = edges[i][3] = -1;
        } else {
            scanf("%d %d %d %d", &edges[i][0], &edges[i][1], &edges[i][2], &edges[i][3]);
        }
    }

    dp[0] = 1;
    for (int mask = 0; mask < (1 << n); mask++) {
        if (dp[mask] == 0) continue;
        for (int i = 0; i < m; i++) {
            int a1 = edges[i][0] - 1, b1 = edges[i][1] - 1;
            int a2 = edges[i][2] - 1, b2 = edges[i][3] - 1;
            if ((mask & (1 << a1)) || (mask & (1 << b1))) continue;
            if (a2 != -1 && ((mask & (1 << a2)) || (mask & (1 << b2)))) continue;
            int new_mask = mask | (1 << a1) | (1 << b1);
            if (a2 != -1) new_mask |= (1 << a2) | (1 << b2);
            dp[new_mask] = mod(dp[new_mask] + dp[mask]);
        }
    }

    int E = dp[(1 << (2 * n)) - 1];
    int result = mod((1LL << n) * E);
    printf("%d\n", result);

    return 0;
}