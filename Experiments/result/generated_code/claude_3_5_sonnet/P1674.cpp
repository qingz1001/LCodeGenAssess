#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 201
#define MAX_P 40001
#define INF 1000000001

int N, P, T;
int graph[MAX_N][MAX_N];
int dist[MAX_N];
int visited[MAX_N];
int parent[MAX_N];

void initialize_graph() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            graph[i][j] = INF;
        }
    }
}

int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int dijkstra(int max_len) {
    memset(dist, INF, sizeof(dist));
    memset(visited, 0, sizeof(visited));
    memset(parent, -1, sizeof(parent));
    
    dist[0] = 0;
    
    for (int i = 0; i < N; i++) {
        int u = -1;
        for (int j = 0; j < N; j++) {
            if (!visited[j] && (u == -1 || dist[j] < dist[u])) {
                u = j;
            }
        }
        
        if (dist[u] == INF) break;
        
        visited[u] = 1;
        
        for (int v = 0; v < N; v++) {
            if (graph[u][v] <= max_len) {
                int new_dist = dist[u] + 1;
                if (new_dist < dist[v]) {
                    dist[v] = new_dist;
                    parent[v] = u;
                }
            }
        }
    }
    
    return dist[N-1] < INF;
}

void remove_path() {
    int v = N - 1;
    while (parent[v] != -1) {
        int u = parent[v];
        graph[u][v] = graph[v][u] = INF;
        v = u;
    }
}

int solve() {
    int left = 0, right = 1000000;
    while (left < right) {
        int mid = left + (right - left) / 2;
        int count = 0;
        
        for (int i = 0; i < T; i++) {
            if (dijkstra(mid)) {
                count++;
                remove_path();
            } else {
                break;
            }
        }
        
        if (count == T) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    
    return left;
}

int main() {
    scanf("%d %d %d", &N, &P, &T);
    
    initialize_graph();
    
    for (int i = 0; i < P; i++) {
        int a, b, l;
        scanf("%d %d %d", &a, &b, &l);
        a--; b--;
        graph[a][b] = graph[b][a] = min(graph[a][b], l);
    }
    
    printf("%d\n", solve());
    
    return 0;
}