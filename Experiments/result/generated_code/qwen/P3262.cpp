#include <stdio.h>
#include <stdlib.h>

#define MAXN 1024
#define INF 1e9

int n, m;
int w[MAXN][MAXN];
int f[MAXN][MAXN];

int dp[MAXN][MAXN];

int max(int a, int b) {
    return (a > b) ? a : b;
}

int min(int a, int b) {
    return (a < b) ? a : b;
}

void dfs(int u, int cnt) {
    if (u >= (1 << n)) return;
    if (cnt == m) {
        for (int i = u; i < (1 << n); i++) {
            dp[u][cnt] += max(w[i][u / 2], f[i][u / 2]);
        }
        return;
    }
    dfs(2 * u, cnt + 1);
    dfs(2 * u + 1, cnt);
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < (1 << (n - 1)); i++) {
        for (int j = 0; j < (n - 1); j++) {
            scanf("%d", &w[(1 << (n - 1)) - 1 + i][j]);
        }
    }
    for (int i = 0; i < (1 << (n - 1)); i++) {
        for (int j = 0; j < (n - 1); j++) {
            scanf("%d", &f[(1 << (n - 1)) - 1 + i][j]);
        }
    }

    dfs(1, 0);

    printf("%d\n", dp[1][0]);

    return 0;
}