#include <stdio.h>
#include <stdlib.h>

#define MAXN 50010
#define INF 0x3f3f3f3f

typedef struct {
    int to, next, weight;
} Edge;

Edge edges[MAXN * 2];
int head[MAXN], edge_count = 0;
int dist[MAXN][2];

void add_edge(int from, int to, int weight) {
    edges[edge_count].to = to;
    edges[edge_count].next = head[from];
    edges[edge_count].weight = weight;
    head[from] = edge_count++;
}

void dijkstra(int start, int end) {
    for (int i = 1; i <= end; i++) {
        dist[i][0] = dist[i][1] = INF;
    }
    dist[start][0] = dist[start][1] = 0;
    
    for (int i = 1; i <= end; i++) {
        int min_dist = INF, min_pos = -1;
        for (int j = 1; j <= end; j++) {
            if (dist[j][0] < min_dist || (dist[j][0] == min_dist && dist[j][1] > dist[j][0])) {
                min_dist = dist[j][0];
                min_pos = j;
            }
        }
        
        for (int e = head[min_pos]; e != -1; e = edges[e].next) {
            int to = edges[e].to, weight = edges[e].weight;
            if (min_dist + weight < dist[to][0]) {
                dist[to][1] = dist[to][0];
                dist[to][0] = min_dist + weight;
            } else if (min_dist + weight < dist[to][1] && min_dist + weight >= dist[to][0]) {
                dist[to][1] = min_dist + weight;
            }
        }
    }
}

int main() {
    int n, m, S, T;
    scanf("%d %d %d %d", &n, &m, &S, &T);
    
    for (int i = 1; i <= n; i++) {
        head[i] = -1;
    }
    
    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        add_edge(u, v, w);
        add_edge(v, u, w);
    }
    
    dijkstra(S, T);
    
    int count = 0;
    for (int i = 1; i <= n; i++) {
        if (i != S && i != T && dist[S][0] + dist[T][0] - dist[i][0] == dist[S][1] + dist[T][1] - dist[i][1] &&
            dist[S][0] + dist[T][1] - dist[i][0] == dist[S][1] + dist[T][0] - dist[i][1] &&
            dist[S][0] + dist[T][0] - dist[i][0] == dist[S][0] + dist[T][1] - dist[i][1] &&
            dist[S][1] + dist[T][0] - dist[i][1] == dist[S][1] + dist[T][1] - dist[i][0]) {
            count++;
        }
    }
    
    printf("%d\n", count / 2);
    
    return 0;
}