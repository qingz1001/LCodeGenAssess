#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_N 201
#define MAX_M 2001
#define INF 0x3f3f3f3f

int n, m, x;
int graph[MAX_N][MAX_N];
int flow[MAX_N][MAX_N];
int parent[MAX_N];
bool visited[MAX_N];

bool bfs(int s, int t) {
    memset(visited, false, sizeof(visited));
    memset(parent, -1, sizeof(parent));
    visited[s] = true;
    
    int queue[MAX_N], front = 0, rear = 0;
    queue[rear++] = s;
    
    while (front < rear) {
        int u = queue[front++];
        for (int v = 1; v <= n; v++) {
            if (!visited[v] && graph[u][v] > flow[u][v]) {
                visited[v] = true;
                parent[v] = u;
                queue[rear++] = v;
                if (v == t) return true;
            }
        }
    }
    return false;
}

int ford_fulkerson(int s, int t) {
    int max_flow = 0;
    while (bfs(s, t)) {
        int path_flow = INF;
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            path_flow = (path_flow < graph[u][v] - flow[u][v]) ? path_flow : graph[u][v] - flow[u][v];
        }
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            flow[u][v] += path_flow;
            flow[v][u] -= path_flow;
        }
        max_flow += path_flow;
    }
    return max_flow;
}

int main() {
    scanf("%d %d %d", &n, &m, &x);
    
    memset(graph, 0, sizeof(graph));
    memset(flow, 0, sizeof(flow));
    
    for (int i = 0; i < m; i++) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        graph[a][b] += c;
    }
    
    int max_students = ford_fulkerson(1, n);
    
    if (max_students == 0) {
        printf("Orz Ni Jinan Saint Cow!\n");
    } else {
        int batches = (x + max_students - 1) / max_students;
        printf("%d %d\n", max_students, batches);
    }
    
    return 0;
}