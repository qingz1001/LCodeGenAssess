#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXN 201
#define INF 1000000

int capacity[MAXN][MAXN];
int adj[MAXN][MAXN];
int parent[MAXN];
int N, M, c1, c2;

// BFS to find augmenting path
int bfs(int s, int t) {
    memset(parent, -1, sizeof(int) * (MAXN));
    int queue[MAXN], front = 0, rear = 0;
    queue[rear++] = s;
    while (front < rear) {
        int u = queue[front++];
        for (int v = 1; v <= 2*N; v++) {
            if (capacity[u][v] > 0 && parent[v] == -1) {
                parent[v] = u;
                queue[rear++] = v;
                if (v == t) return 1;
            }
        }
    }
    return 0;
}

int max_flow(int s, int t) {
    int flow = 0;
    while (bfs(s, t)) {
        int path_flow = INF;
        int v = t;
        while (v != s) {
            int u = parent[v];
            if (capacity[u][v] < path_flow)
                path_flow = capacity[u][v];
            v = u;
        }
        flow += path_flow;
        v = t;
        while (v != s) {
            int u = parent[v];
            capacity[u][v] -= path_flow;
            capacity[v][u] += path_flow;
            v = u;
        }
    }
    return flow;
}

int main(){
    scanf("%d %d %d %d", &N, &M, &c1, &c2);
    // Initialize capacity
    memset(capacity, 0, sizeof(capacity));
    // Node mapping:
    // For nodes != c1 and c2, split into in and out
    // in: i
    // out: i + N
    for(int i=1;i<=N;i++){
        if(i != c1 && i != c2){
            capacity[i][i+N] = 1;
        }
    }
    // Read edges
    for(int i=0;i<M;i++){
        int u, v;
        scanf("%d %d", &u, &v);
        // Connect u to v
        if(u != c1 && u != c2){
            u = u + N;
        }
        if(v != c1 && v != c2){
            v = v;
        }
        capacity[u][v] = INF;
        // Connect v to u
        if(v != c1 && v != c2){
            v = v + N;
        }
        if(u != c1 && u != c2){
            u = u - N;
        }
        capacity[v][u] = INF;
    }
    int s = c1;
    int t = c2;
    printf("%d\n", max_flow(s, t));
    return 0;
}