#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005
#define MAXM 200005
#define INF 0x3f3f3f3f

typedef struct {
    int v, w;
} Edge;

int t, n, m, k, p;
Edge edges[MAXM];
int head[MAXN], dist[MAXN], cnt[MAXN], f[MAXN][55];
bool inq[MAXN];

void add_edge(int u, int v, int w) {
    edges[cnt[u]].v = v;
    edges[cnt[u]].w = w;
    cnt[u]++;
}

void SPFA(int start) {
    memset(dist, INF, sizeof(dist));
    memset(inq, false, sizeof(inq));
    dist[start] = 0;
    inq[start] = true;
    f[start][0] = 1;
    while (true) {
        int u = -1, min_dist = INF;
        for (int i = 1; i <= n; i++) {
            if (!inq[i] && dist[i] < min_dist) {
                u = i;
                min_dist = dist[i];
            }
        }
        if (u == -1) break;
        inq[u] = false;
        for (int i = head[u]; i != -1; i = edges[i].next) {
            int v = edges[i].v, w = edges[i].w;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                memcpy(f[v], f[u], sizeof(f[u]));
                for (int j = 0; j <= k; j++) {
                    f[v][j] = (f[v][j] + f[v][j-1]) % p;
                }
            } else if (dist[u] + w == dist[v]) {
                for (int j = 0; j <= k; j++) {
                    f[v][j] = (f[v][j] + f[u][j]) % p;
                }
            }
        }
    }
}

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d%d%d", &n, &m, &k, &p);
        memset(head, -1, sizeof(head));
        memset(cnt, 0, sizeof(cnt));
        for (int i = 0; i < m; i++) {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            add_edge(u, v, w);
        }
        SPFA(1);
        int result = (f[n][k] - 1 + p) % p;
        for (int i = 1; i <= k; i++) {
            if (dist[n] + i == dist[n + 1]) {
                result = -1;
                break;
            }
        }
        printf("%d\n", result);
    }
    return 0;
}