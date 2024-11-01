#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 10
#define MAXM (1 << (MAXN - 1))
#define MAXNODE (1 << MAXN)

int n, m;
int w[MAXM][MAXN], f[MAXM][MAXN];
int dp[MAXNODE][MAXM];

void dfs(int node, int depth, int war_count, int total_count) {
    if (depth == n - 1) {
        for (int i = 0; i < (1 << (n - 1)); i++) {
            int contribution = 0;
            for (int j = 0; j < n - 1; j++) {
                if (i & (1 << j)) {
                    contribution += w[node - (1 << (n - 1))][j];
                } else {
                    contribution += f[node - (1 << (n - 1))][j];
                }
            }
            dp[node][war_count] = contribution;
        }
        return;
    }

    dfs(node * 2, depth + 1, war_count, total_count / 2);
    dfs(node * 2 + 1, depth + 1, war_count, total_count / 2);

    for (int i = 0; i <= war_count; i++) {
        for (int j = 0; j <= i; j++) {
            dp[node][i] = dp[node][i] > dp[node * 2][j] + dp[node * 2 + 1][i - j] ? dp[node][i] : dp[node * 2][j] + dp[node * 2 + 1][i - j];
        }
    }
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

    memset(dp, 0, sizeof(dp));
    dfs(1, 0, m, 1 << (n - 1));

    printf("%d\n", dp[1][m]);

    return 0;
}