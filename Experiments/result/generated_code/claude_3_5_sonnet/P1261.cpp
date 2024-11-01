#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 30000
#define MAX_M 150000
#define INF 0x3f3f3f3f

typedef struct {
    int to, next, weight;
} Edge;

Edge edges[MAX_M * 2];
int head[MAX_N], cnt;
int n, m;
int rank[MAX_N];
int dist[MAX_N];
int vis[MAX_N];
int B[MAX_N];

void add_edge(int u, int v, int w) {
    edges[cnt].to = v;
    edges[cnt].weight = w;
    edges[cnt].next = head[u];
    head[u] = cnt++;
}

void dijkstra(int start) {
    memset(dist, 0x3f, sizeof(dist));
    memset(vis, 0, sizeof(vis));
    dist[start] = 0;

    for (int i = 0; i < n; i++) {
        int u = -1, min_dist = INF;
        for (int j = 0; j < n; j++) {
            if (!vis[j] && dist[j] < min_dist) {
                u = j;
                min_dist = dist[j];
            }
        }
        if (u == -1) break;
        vis[u] = 1;

        for (int e = head[u]; e != -1; e = edges[e].next) {
            int v = edges[e].to;
            int w = edges[e].weight;
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
            }
        }
    }
}

int cmp(const void *a, const void *b) {
    int u = *(int*)a, v = *(int*)b;
    if (dist[u] != dist[v]) return dist[u] - dist[v];
    return rank[v] - rank[u];
}

int main() {
    scanf("%d %d", &n, &m);
    memset(head, -1, sizeof(head));

    for (int i = 0; i < n; i++) {
        scanf("%d", &rank[i]);
    }

    for (int i = 0; i < m; i++) {
        int a, b, t;
        scanf("%d %d %d", &a, &b, &t);
        a--; b--;
        add_edge(a, b, t);
        add_edge(b, a, t);
    }

    int result = 0;
    int order[MAX_N];

    for (int i = 0; i < n; i++) {
        dijkstra(i);
        for (int j = 0; j < n; j++) order[j] = j;
        qsort(order, n, sizeof(int), cmp);

        int max_rank = -1;
        for (int j = 0; j < n; j++) {
            int v = order[j];
            if (rank[v] > max_rank) {
                B[i]++;
                max_rank = rank[v];
            }
        }
        result += B[i];
    }

    printf("%d\n", result);
    return 0;
}