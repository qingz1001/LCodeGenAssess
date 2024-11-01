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
int w[MAXN], dist[MAXN], vis[MAXN];
int n, k, r;

void add_edge(int u, int v) {
    edges[edge_cnt].to = v;
    edges[edge_cnt].next = head[u];
    head[u] = edge_cnt++;
}

void dfs(int u, int fa) {
    for (int i = head[u]; i != -1; i = edges[i].next) {
        int v = edges[i].to;
        if (v == fa) continue;
        dist[v] = dist[u] + 1;
        dfs(v, u);
    }
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
            int x, y;
            scanf("%d %d", &x, &y);
            add_edge(x, y);
            add_edge(y, x);
        }

        int max_sum = 0;
        for (int i = 1; i <= n; i++) {
            memset(dist, INF, sizeof(dist));
            memset(vis, 0, sizeof(vis));
            dist[i] = 0;
            dfs(i, -1);
            int sum = 0;
            for (int j = 1; j <= n; j++) {
                if (dist[j] <= r) {
                    sum += w[j];
                }
            }
            if (sum > max_sum) {
                max_sum = sum;
            }
        }

        printf("%d\n", max_sum);
    }
    return 0;
}