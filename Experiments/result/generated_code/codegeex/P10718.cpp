#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MOD 998244353
#define MAXN 100005

int n, m, k, q;
int x[MAXN], y[MAXN];
int u[3 * MAXN], v[3 * MAXN];
int l[MAXN], c[MAXN][MAXN];
int dp[MAXN][MAXN], sum[MAXN][MAXN];
int f[MAXN], g[MAXN], inv[MAXN];

int cmp(const void *a, const void *b) {
    int xa = x[*(int*)a], ya = y[*(int*)a];
    int xb = x[*(int*)b], yb = y[*(int*)b];
    if (xa != xb) return xa - xb;
    return ya - yb;
}

int main() {
    scanf("%d %d %d", &n, &m, &k);
    for (int i = 1; i <= n; i++) scanf("%d %d", &x[i], &y[i]);
    for (int i = 1; i <= m; i++) scanf("%d %d", &u[i], &v[i]);
    for (int i = 1; i <= k; i++) {
        scanf("%d", &l[i]);
        for (int j = 1; j <= l[i]; j++) scanf("%d", &c[i][j]);
    }
    scanf("%d", &q);

    // 计算逆元
    inv[1] = 1;
    for (int i = 2; i <= k; i++) inv[i] = (MOD - MOD / i) * inv[MOD % i] % MOD;

    // 初始化dp数组
    memset(dp, 0, sizeof(dp));
    memset(sum, 0, sizeof(sum));

    // 计算dp数组和sum数组
    for (int i = 1; i <= k; i++) {
        dp[i][1] = 1;
        for (int j = 2; j <= l[i]; j++) {
            dp[i][j] = dp[i][j-1];
            for (int t = 1; t < j; t++) {
                if (dp[i][t] == 1) {
                    int flag = 0;
                    for (int p = t+1; p < j; p++) {
                        if (dp[i][p] == 1) {
                            if ((x[c[i][p]] - x[c[i][t]]) * (y[c[i][j]] - y[c[i][p]]) != (x[c[i][j]] - x[c[i][p]]) * (y[c[i][t]] - y[c[i][p]])) {
                                flag = 1;
                                break;
                            }
                        }
                    }
                    if (!flag) dp[i][j] = 0;
                }
            }
        }
        for (int j = 1; j <= l[i]; j++) {
            sum[i][j] = (sum[i][j-1] + dp[i][j]) % MOD;
        }
    }

    // 计算f数组
    for (int i = 1; i <= k; i++) {
        f[i] = 1;
        for (int j = 2; j <= l[i]; j++) {
            if (dp[i][j] == 1) f[i] = f[i] * 2 % MOD;
        }
    }

    // 计算g数组
    for (int i = 1; i <= k; i++) {
        g[i] = 1;
        for (int j = 1; j <= i; j++) {
            if (sum[i][l[i]] - sum[i][j-1] == 1) g[i] = g[i] * f[j] % MOD;
        }
    }

    // 处理每个询问
    for (int i = 1; i <= q; i++) {
        int z;
        scanf("%d", &z);
        int ans = 0;
        for (int j = 1; j <= k; j++) {
            if (l[j] <= z) {
                ans = (ans + g[j] * inv[z-l[j]]) % MOD;
            }
        }
        printf("%d\n", ans);
    }

    return 0;
}