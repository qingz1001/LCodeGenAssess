#include <stdio.h>
#include <stdlib.h>

#define MAXN 1024
#define MAXM 2001

int n, m;
int w[MAXN][MAXN], f[MAXN][MAXN];
int dp[MAXN][MAXN][MAXM];

int max(int a, int b) {
    return a > b ? a : b;
}

void solve(int node, int depth, int max_warriors) {
    if (depth == 0) {
        for (int i = 0; i <= max_warriors; i++) {
            dp[node][depth][i] = i * f[node][0];
        }
        return;
    }

    solve(node * 2, depth - 1, max_warriors);
    solve(node * 2 + 1, depth - 1, max_warriors);

    for (int i = 0; i <= max_warriors; i++) {
        for (int j = 0; j <= max_warriors - i; j++) {
            dp[node][depth][i + j] = max(dp[node][depth][i + j], dp[node * 2][depth - 1][i] + dp[node * 2 + 1][depth - 1][j]);
        }
    }

    for (int i = 0; i <= max_warriors; i++) {
        for (int j = 0; j <= i; j++) {
            for (int k = 0; k <= max_warriors - i - j; k++) {
                dp[node][depth][i + j + k] = max(dp[node][depth][i + j + k], dp[node * 2][depth - 1][i] + dp[node * 2 + 1][depth - 1][j] + w[node][0] * k);
            }
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    int num_leafs = (1 << (n - 1));

    for (int i = 0; i < num_leafs; i++) {
        for (int j = 0; j < n - 1; j++) {
            scanf("%d", &w[num_leafs - 1 + i][j]);
        }
    }

    for (int i = 0; i < num_leafs; i++) {
        for (int j = 0; j < n - 1; j++) {
            scanf("%d", &f[num_leafs - 1 + i][j]);
        }
    }

    solve(1, n - 1, m);

    int result = 0;
    for (int i = 0; i <= m; i++) {
        result = max(result, dp[1][n - 1][i]);
    }

    printf("%d\n", result);
    return 0;
}