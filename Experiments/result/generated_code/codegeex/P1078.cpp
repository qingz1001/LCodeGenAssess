#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAX_N 100
#define MAX_K 100
#define MAX_M 10000

struct Edge {
    int to;
    int weight;
};

int n, k, m, s, t;
int culture[MAX_N + 1];
int dislike[MAX_K + 1][MAX_K + 1];
Edge edges[MAX_M + 1];
int head[MAX_N + 1];
int dist[MAX_N + 1][1 << MAX_K];
bool visited[MAX_N + 1][1 << MAX_K];

void addEdge(int u, int v, int w) {
    static int cnt = 0;
    edges[cnt].to = v;
    edges[cnt].weight = w;
    head[u] = cnt++;
}

void dijkstra() {
    memset(dist, 0x3f, sizeof(dist));
    memset(visited, 0, sizeof(visited));
    dist[s][1 << (culture[s] - 1)] = 0;
    visited[s][1 << (culture[s] - 1)] = true;

    for (int mask = 0; mask < (1 << k); ++mask) {
        for (int u = 1; u <= n; ++u) {
            if (visited[u][mask]) {
                for (int i = head[u]; i != -1; i = edges[i].next) {
                    int v = edges[i].to;
                    int w = edges[i].weight;
                    int new_mask = mask | (1 << (culture[v] - 1));
                    if (!dislike[culture[v]][culture[u]] && dist[u][mask] != 0x3f3f3f3f && dist[u][mask] + w < dist[v][new_mask]) {
                        dist[v][new_mask] = dist[u][mask] + w;
                        if (!visited[v][new_mask]) {
                            visited[v][new_mask] = true;
                            addEdge(mask, new_mask, dist[v][new_mask]);
                        }
                    }
                }
            }
        }
    }
}

int main() {
    scanf("%d%d%d%d%d", &n, &k, &m, &s, &t);
    memset(head, -1, sizeof(head));

    for (int i = 1; i <= n; ++i) {
        scanf("%d", &culture[i]);
    }

    for (int i = 1; i <= k; ++i) {
        for (int j = 1; j <= k; ++j) {
            scanf("%d", &dislike[i][j]);
        }
    }

    for (int i = 0; i < m; ++i) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        addEdge(u, v, w);
        addEdge(v, u, w);
    }

    dijkstra();

    int min_dist = 0x3f3f3f3f;
    for (int mask = 0; mask < (1 << k); ++mask) {
        if (dist[t][mask] < min_dist) {
            min_dist = dist[t][mask];
        }
    }

    if (min_dist == 0x3f3f3f3f) {
        printf("-1\n");
    } else {
        printf("%d\n", min_dist);
    }

    return 0;
}