#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_N 202
#define INF 0x3f3f3f3f

int N, M, c1, c2;
int graph[MAX_N][MAX_N];
int flow[MAX_N][MAX_N];
int parent[MAX_N];
bool visited[MAX_N];

bool bfs() {
    memset(visited, 0, sizeof(visited));
    memset(parent, -1, sizeof(parent));
    
    int queue[MAX_N], front = 0, rear = 0;
    queue[rear++] = c1;
    visited[c1] = true;
    
    while (front < rear) {
        int u = queue[front++];
        for (int v = 1; v <= 2*N; v++) {
            if (!visited[v] && graph[u][v] - flow[u][v] > 0) {
                queue[rear++] = v;
                parent[v] = u;
                visited[v] = true;
                if (v == c2) return true;
            }
        }
    }
    return false;
}

int ford_fulkerson() {
    int max_flow = 0;
    while (bfs()) {
        int path_flow = INF;
        for (int v = c2; v != c1; v = parent[v]) {
            int u = parent[v];
            path_flow = (graph[u][v] - flow[u][v] < path_flow) ? graph[u][v] - flow[u][v] : path_flow;
        }
        for (int v = c2; v != c1; v = parent[v]) {
            int u = parent[v];
            flow[u][v] += path_flow;
            flow[v][u] -= path_flow;
        }
        max_flow += path_flow;
    }
    return max_flow;
}

int main() {
    scanf("%d %d %d %d", &N, &M, &c1, &c2);
    
    for (int i = 1; i <= N; i++) {
        graph[i][i+N] = 1;
    }
    
    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        graph[u+N][v] = graph[v+N][u] = INF;
    }
    
    c2 += N;
    
    printf("%d\n", ford_fulkerson());
    
    return 0;
}