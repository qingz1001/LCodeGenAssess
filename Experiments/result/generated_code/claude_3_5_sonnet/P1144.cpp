#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 1000001
#define MAX_M 2000001
#define MOD 100003

int n, m;
int head[MAX_N], to[MAX_M * 2], next[MAX_M * 2], edge_cnt;
int dist[MAX_N], count[MAX_N];
int queue[MAX_N], front, rear;

void add_edge(int u, int v) {
    to[edge_cnt] = v;
    next[edge_cnt] = head[u];
    head[u] = edge_cnt++;
}

void bfs() {
    memset(dist, -1, sizeof(dist));
    dist[1] = 0;
    count[1] = 1;
    
    front = rear = 0;
    queue[rear++] = 1;
    
    while (front < rear) {
        int u = queue[front++];
        for (int i = head[u]; i != -1; i = next[i]) {
            int v = to[i];
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                count[v] = count[u];
                queue[rear++] = v;
            } else if (dist[v] == dist[u] + 1) {
                count[v] = (count[v] + count[u]) % MOD;
            }
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    
    memset(head, -1, sizeof(head));
    edge_cnt = 0;
    
    for (int i = 0; i < m; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        add_edge(x, y);
        add_edge(y, x);
    }
    
    bfs();
    
    for (int i = 1; i <= n; i++) {
        printf("%d\n", count[i]);
    }
    
    return 0;
}