#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_N 10
#define MAX_NODES (1 << (MAX_N - 1))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

int n, m;
int w[MAX_NODES][MAX_N], f[MAX_NODES][MAX_N];
long long dp[MAX_NODES][2][MAX_NODES + 1];

long long dfs(int node, int is_war, int war_count) {
    if (node >= (1 << (n - 1))) {
        if (is_war && war_count > 0) return w[node - (1 << (n - 1))][0];
        if (!is_war && war_count <= m) return f[node - (1 << (n - 1))][0];
        return -1e18;
    }

    if (dp[node][is_war][war_count] != -1) return dp[node][is_war][war_count];

    long long res = -1e18;
    for (int lc = 0; lc <= war_count; lc++) {
        int rc = war_count - lc;
        long long left = dfs(node * 2, is_war, lc);
        long long right = dfs(node * 2 + 1, is_war, rc);
        if (left > -1e18 && right > -1e18) {
            res = MAX(res, left + right);
        }
    }

    if (res > -1e18 && node > 1) {
        res += is_war ? w[node - 1][n - 1 - __builtin_ctz(node)] : f[node - 1][n - 1 - __builtin_ctz(node)];
    }

    return dp[node][is_war][war_count] = res;
}

int main() {
    scanf("%d %d", &n, &m);

    for (int i = 0; i < (1 << (n - 1)); i++) {
        for (int j = 0; j < n - 1; j++) {
            scanf("%d", &w[i][j]);
        }
    }

    for (int i = 0; i < (1 << (n - 1)); i++) {
        for (int j = 0; j < n - 1; j++) {
            scanf("%d", &f[i][j]);
        }
    }

    memset(dp, -1, sizeof(dp));

    long long ans = MAX(dfs(1, 0, m), dfs(1, 1, m));
    printf("%lld\n", ans);

    return 0;
}