#include <stdio.h>
#include <stdlib.h>

#define MAXN 10005
#define INF 0x3f3f3f3f

typedef struct {
    int to, weight;
} Edge;

int n, m, s, t;
Edge edges[2 * MAXM];
int degree[MAXN];
int dist[MAXN];
int max_dist[MAXN];

void add_edge(int u, int v, int w) {
    edges[m++] = (Edge){v, w};
    degree[u]++;
}

int main() {
    scanf("%d %d %d %d", &n, &m, &s, &t);
    
    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        add_edge(u, v, w);
        add_edge(v, u, w); // Assuming the graph is undirected
    }
    
    for (int i = 1; i <= n; i++) {
        dist[i] = INF;
        max_dist[i] = -1;
    }
    
    dist[s] = 0;
    max_dist[s] = 0;
    
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int u = edges[j].to, w = edges[j].weight;
            if (dist[u] > dist[edges[j].to] + w) {
                dist[u] = dist[edges[j].to] + w;
                max_dist[u] = max(max_dist[u], max_dist[edges[j].to]);
            } else if (dist[u] == dist[edges[j].to] + w) {
                max_dist[u] = max(max_dist[u], max(max_dist[edges[j].to], w));
            }
        }
    }
    
    printf("%d\n", max_dist[t]);
    
    return 0;
}