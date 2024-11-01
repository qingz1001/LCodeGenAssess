#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_N 10
#define MAX_NODES (1 << MAX_N)
#define MAX(a, b) ((a) > (b) ? (a) : (b))

int n, m;
int w[MAX_NODES][MAX_N], f[MAX_NODES][MAX_N];
long long dp[MAX_NODES][2][MAX_NODES];

void dfs(int node, int depth) {
    if (node >= (1 << (n - 1))) {
        dp[node][0][0] = 0;
        dp[node][1][1] = 0;
        return;
    }

    int left = node * 2, right = node * 2 + 1;
    dfs(left, depth + 1);
    dfs(right, depth + 1);

    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= i; j++) {
            long long max_val = 0;
            for (int k = 0; k <= j; k++) {
                long long left_val = dp[left][0][k] + dp[right][0][j - k];
                long long right_val = dp[left][1][k] + dp[right][1][j - k];
                max_val = MAX(max_val, MAX(left_val, right_val));
            }
            dp[node][0][i] = max_val;
            dp[node][1][i] = max_val;
        }
    }

    for (int i = 0; i <= m; i++) {
        for (int j = 1; j <= n - depth; j++) {
            for (int k = 0; k < (1 << (n - 1)); k++) {
                if (k >= (1 << (n - j - 1)) && k < (1 << (n - j))) {
                    dp[node][0][i] += f[k][j - 1];
                    dp[node][1][i] += w[k][j - 1];
                }
            }
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);

    for (int i = 0; i < (1 << (n - 1)); i++) {
        for (int j = 0; j < n - 1; j++) {
            scanf("%d", &w[i + (1 << (n - 1))][j]);
        }
    }

    for (int i = 0; i < (1 << (n - 1)); i++) {
        for (int j = 0; j < n - 1; j++) {
            scanf("%d", &f[i + (1 << (n - 1))][j]);
        }
    }

    dfs(1, 1);

    long long result = 0;
    for (int i = 0; i <= m; i++) {
        result = MAX(result, MAX(dp[1][0][i], dp[1][1][i]));
    }

    printf("%lld\n", result);

    return 0;
}