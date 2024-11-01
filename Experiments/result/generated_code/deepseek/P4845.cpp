#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 1005
#define INF 0x3f3f3f3f

typedef struct {
    int to, next;
} Edge;

Edge edges[MAXN * 2];
int head[MAXN], edge_cnt;
int w[MAXN], dist[MAXN][MAXN];
int n, k, r;

void add_edge(int u, int v) {
    edges[edge_cnt].to = v;
    edges[edge_cnt].next = head[u];
    head[u] = edge_cnt++;
}

void bfs(int start, int *d) {
    int queue[MAXN], front = 0, rear = 0;
    memset(d, INF, sizeof(int) * (n + 1));
    d[start] = 0;
    queue[rear++] = start;
    while (front < rear) {
        int u = queue[front++];
        for (int i = head[u]; i != -1; i = edges[i].next) {
            int v = edges[i].to;
            if (d[v] == INF) {
                d[v] = d[u] + 1;
                queue[rear++] = v;
            }
        }
    }
}

int dp[MAXN][MAXN];

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d %d %d", &n, &k, &r);
        for (int i = 1; i <= n; i++) {
            scanf("%d", &w[i]);
        }
        memset(head, -1, sizeof(head));
        edge_cnt = 0;
        for (int i = 1; i < n; i++) {
            int u, v;
            scanf("%d %d", &u, &v);
            add_edge(u, v);
            add_edge(v, u);
        }
        for (int i = 1; i <= n; i++) {
            bfs(i, dist[i]);
        }
        memset(dp, -INF, sizeof(dp));
        for (int i = 1; i <= n; i++) {
            dp[i][0] = 0;
            for (int j = 1; j <= n; j++) {
                if (dist[i][j] <= r) {
                    dp[i][0] += w[j];
                }
            }
        }
        for (int i = 1; i <= k; i++) {
            for (int j = 1; j <= n; j++) {
                dp[j][i] = dp[j][i - 1];
                for (int l = 1; l <= n; l++) {
                    if (dist[j][l] <= r) {
                        dp[j][i] = max(dp[j][i], dp[l][i - 1] + w[j]);
                    }
                }
            }
        }
        int ans = 0;
        for (int i = 1; i <= n; i++) {
            ans = max(ans, dp[i][k]);
        }
        printf("%d\n", ans);
    }
    return 0;
}