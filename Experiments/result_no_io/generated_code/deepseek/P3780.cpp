#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 20005
#define MAXK 500005

typedef struct {
    int parent, apples, value;
} Node;

Node nodes[MAXN];
int dp[MAXN][MAXK];

int max(int a, int b) {
    return a > b ? a : b;
}

void dfs(int u, int n, int k) {
    for (int i = 0; i <= k; i++) {
        dp[u][i] = dp[nodes[u].parent][i];
    }
    for (int i = 0; i <= nodes[u].apples; i++) {
        for (int j = i; j <= k; j++) {
            dp[u][j] = max(dp[u][j], dp[nodes[u].parent][j - i] + i * nodes[u].value);
        }
    }
    for (int i = 1; i <= n; i++) {
        if (nodes[i].parent == u) {
            dfs(i, n, k);
        }
    }
}

int main() {
    int Q;
    scanf("%d", &Q);
    while (Q--) {
        int n, k;
        scanf("%d %d", &n, &k);
        memset(dp, 0, sizeof(dp));
        for (int i = 1; i <= n; i++) {
            scanf("%d %d %d", &nodes[i].parent, &nodes[i].apples, &nodes[i].value);
        }
        dfs(1, n, k);
        int max_happiness = 0;
        for (int i = 0; i <= k; i++) {
            max_happiness = max(max_happiness, dp[1][i]);
        }
        printf("%d\n", max_happiness);
    }
    return 0;
}