#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 20010
#define MAXK 500010
#define MAXV 10010

int dp[MAXN][MAXK][MAXV];
int n, k;
int a[MAXN], v[MAXN], fa[MAXN], s[MAXN];
int l[MAXN], r[MAXN], w[MAXN];
int cnt;
int f[MAXN];

void dfs(int u) {
    int i, j, m, mm, t;
    l[u] = cnt;
    for (i = fa[u]; i; i = fa[i]) {
        if (l[i] > l[u]) l[u] = l[i];
    }
    cnt++;
    w[cnt] = v[u];
    r[u] = cnt;
    s[u] = 1;
    for (i = fa[u]; i; i = fa[i]) {
        if (r[i] < r[u]) r[u] = r[i];
    }
    for (i = fa[u]; i; i = fa[i]) {
        dfs(i);
        s[u] += s[i];
        m = r[i];
        mm = r[u];
        if (m < mm) {
            m ^= mm;
            mm ^= m;
            m ^= mm;
        }
        for (j = 0; j <= k; j++) {
            for (t = 0; t <= s[i]; t++) {
                if (dp[u][j][t] < dp[i][j][t] + dp[u][j - t][m - l[u] + 1]) {
                    dp[u][j][t] = dp[i][j][t] + dp[u][j - t][m - l[u] + 1];
                }
            }
        }
    }
    for (i = 0; i <= k; i++) {
        dp[u][i][s[u]] = dp[u][i][s[u] - 1] + w[cnt];
    }
    for (i = 0; i <= k; i++) {
        for (j = 1; j <= s[u]; j++) {
            if (dp[u][i][j] < dp[u][i][j - 1]) {
                dp[u][i][j] = dp[u][i][j - 1];
            }
        }
    }
    for (i = 0; i <= k; i++) {
        for (j = s[u] - 1; j >= 0; j--) {
            if (dp[u][i][j] < dp[u][i][j + 1]) {
                dp[u][i][j] = dp[u][i][j + 1];
            }
        }
    }
    for (i = s[u] - 1; i >= 0; i--) {
        for (j = k; j >= 0; j--) {
            if (dp[u][j][i] < dp[u][j][i + 1] + (j - (k - (i + 1)) + 1) * w[cnt]) {
                dp[u][j][i] = dp[u][j][i + 1] + (j - (k - (i + 1)) + 1) * w[cnt];
            }
        }
    }
    for (i = 0; i <= k; i++) {
        for (j = 0; j <= s[u]; j++) {
            f[i] = max(f[i], dp[u][i][j]);
        }
    }
}

int main() {
    int i, j, T, t;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &k);
        for (i = 1; i <= n; i++) {
            scanf("%d%d%d", &fa[i], &a[i], &v[i]);
        }
        cnt = 0;
        memset(dp, 0, sizeof(dp));
        dfs(1);
        for (i = 1; i <= n; i++) {
            for (j = 0; j <= k; j++) {
                f[j] = max(f[j], dp[i][j][s[i]]);
            }
        }
        t = 0;
        for (i = 0; i <= k; i++) {
            t = max(t, f[i]);
        }
        printf("%d\n", t);
    }
    return 0;
}