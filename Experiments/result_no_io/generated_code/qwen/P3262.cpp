#include <stdio.h>
#include <stdlib.h>

#define MAXN 1024
#define INF 1e9

int dp[MAXN][MAXN];
int w[MAXN][MAXN], f[MAXN][MAXN];

void dfs(int node, int m) {
    if (node >= MAXN) return;
    if (dp[node][m] != -1) return;

    int left = node * 2;
    int right = node * 2 + 1;

    if (m == 0) {
        dp[node][m] = f[node][0];
        for (int i = 1; i <= m; i++) {
            dp[node][m] += INF;
        }
    } else {
        dp[node][m] = -INF;
        for (int i = 0; i <= m; i++) {
            int sum_w = 0, sum_f = 0;
            for (int j = 0; j < i; j++) {
                sum_w += w[left][j];
            }
            for (int j = i; j < m; j++) {
                sum_f += f[right][j - i];
            }
            dp[node][m] = f[node][i] + sum_w + sum_f;
            dfs(left, i);
            dfs(right, m - i);
            dp[node][m] = dp[node][m] > dp[left][i] + dp[right][m - i] ? dp[node][m] : dp[left][i] + dp[right][m - i];
        }
    }
}

int main() {
    int n, m;
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

    for (int i = 0; i < MAXN; i++) {
        for (int j = 0; j <= m; j++) {
            dp[i][j] = -1;
        }
    }

    dfs(1, m);
    printf("%d\n", dp[1][m]);

    return 0;
}