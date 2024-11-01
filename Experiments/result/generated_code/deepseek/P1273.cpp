#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 3005
#define INF 0x3f3f3f3f

typedef struct {
    int to, cost;
} Edge;

Edge edges[MAXN][MAXN];
int edge_count[MAXN];
int cost[MAXN];
int dp[MAXN][MAXN];
int size[MAXN];

void add_edge(int u, int v, int c) {
    edges[u][edge_count[u]].to = v;
    edges[u][edge_count[u]].cost = c;
    edge_count[u]++;
}

void dfs(int u) {
    dp[u][0] = 0;
    if (u >= MAXN - edge_count[u]) {
        dp[u][1] = cost[u];
        size[u] = 1;
        return;
    }
    for (int i = 0; i < edge_count[u]; i++) {
        int v = edges[u][i].to;
        int c = edges[u][i].cost;
        dfs(v);
        size[u] += size[v];
        for (int j = size[u]; j >= 1; j--) {
            for (int k = 1; k <= size[v] && k <= j; k++) {
                dp[u][j] = (dp[u][j] == INF) ? dp[u][j] : dp[u][j];
                dp[u][j] = (dp[v][k] == INF) ? dp[u][j] : dp[u][j];
                if (dp[u][j - k] != INF && dp[v][k] != INF) {
                    dp[u][j] = (dp[u][j] == INF) ? dp[u][j - k] + dp[v][k] + c :
                              (dp[u][j] < dp[u][j - k] + dp[v][k] + c) ? dp[u][j] : dp[u][j - k] + dp[v][k] + c;
                }
            }
        }
    }
}

int main() {
    int N, M;
    scanf("%d %d", &N, &M);
    memset(dp, INF, sizeof(dp));
    for (int i = 1; i <= N - M; i++) {
        int K;
        scanf("%d", &K);
        for (int j = 0; j < K; j++) {
            int A, C;
            scanf("%d %d", &A, &C);
            add_edge(i, A, C);
        }
    }
    for (int i = N - M + 1; i <= N; i++) {
        scanf("%d", &cost[i]);
    }
    dfs(1);
    for (int i = M; i >= 0; i--) {
        if (dp[1][i] <= 0) {
            printf("%d\n", i);
            break;
        }
    }
    return 0;
}