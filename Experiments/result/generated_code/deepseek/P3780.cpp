#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 20005
#define MAXK 500005

typedef struct {
    int parent, a, v;
} Node;

Node nodes[MAXN];
int dp[MAXN][MAXK];

int max(int a, int b) {
    return a > b ? a : b;
}

void dfs(int u, int n, int k) {
    for (int i = 0; i <= k; i++) {
        dp[u][i] = 0;
    }
    for (int i = 1; i <= nodes[u].a; i++) {
        if (i <= k) {
            dp[u][i] = i * nodes[u].v;
        }
    }
    for (int v = 2; v <= n; v++) {
        if (nodes[v].parent == u) {
            dfs(v, n, k);
            for (int j = k; j >= 1; j--) {
                for (int l = 1; l <= j; l++) {
                    dp[u][j] = max(dp[u][j], dp[u][j - l] + dp[v][l]);
                }
            }
        }
    }
}

int main() {
    int Q;
    scanf("%d", &Q);
    while (Q--) {
        int n, k;
        scanf("%d %d", &n, &k);
        for (int i = 1; i <= n; i++) {
            scanf("%d %d %d", &nodes[i].parent, &nodes[i].a, &nodes[i].v);
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