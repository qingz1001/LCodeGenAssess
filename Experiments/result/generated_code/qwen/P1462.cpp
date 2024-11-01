#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 100005
#define INF INT_MAX

typedef struct {
    int to, cost;
} Edge;

int n, m, b;
int f[MAXN];
Edge edges[MAXN * 2];
int edge_count = 0;

void add_edge(int from, int to, int cost) {
    edges[edge_count].to = to;
    edges[edge_count].cost = cost;
    edge_count++;
}

int dijkstra(int start, int end) {
    int dist[n + 1];
    for (int i = 1; i <= n; i++) {
        dist[i] = INF;
    }
    dist[start] = 0;
    
    int visited[n + 1];
    for (int i = 1; i <= n; i++) {
        visited[i] = 0;
    }
    
    for (int count = 0; count < n - 1; count++) {
        int u = -1;
        for (int v = 1; v <= n; v++) {
            if (!visited[v] && (u == -1 || dist[u] > dist[v])) {
                u = v;
            }
        }
        
        visited[u] = 1;
        
        for (int i = 0; i < edge_count; i++) {
            int v = edges[i].to;
            int weight = edges[i].cost;
            if (dist[u] != INF && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
            }
        }
    }
    
    return dist[end];
}

int main() {
    scanf("%d %d %d", &n, &m, &b);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &f[i]);
    }
    
    for (int i = 0; i < m; i++) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        add_edge(a, b, c);
        add_edge(b, a, c);
    }
    
    int max_fee = -1;
    for (int i = 1; i <= n; i++) {
        int current_blood = b;
        int total_fee = 0;
        for (int j = i; j != n; ) {
            int next_city = -1;
            int min_cost = INF;
            for (int k = 0; k < edge_count; k++) {
                if (edges[k].from == j) {
                    if (current_blood >= edges[k].cost) {
                        if (edges[k].to > j && f[edges[k].to] < min_cost) {
                            min_cost = f[edges[k].to];
                            next_city = edges[k].to;
                        } else if (edges[k].to < j && f[edges[k].to] < min_cost) {
                            min_cost = f[edges[k].to];
                            next_city = edges[k].to;
                        }
                    }
                }
            }
            if (next_city == -1) break;
            current_blood -= edges[next_city - 1][j - 1];
            total_fee += min_cost;
            j = next_city;
        }
        if (current_blood >= 0) {
            max_fee = max_fee == -1 ? total_fee : fmax(max_fee, total_fee);
        }
    }
    
    if (max_fee == -1) {
        printf("AFK\n");
    } else {
        printf("%d\n", max_fee);
    }
    
    return 0;
}