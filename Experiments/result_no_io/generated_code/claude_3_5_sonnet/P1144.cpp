#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 1000005
#define MAX_M 2000005
#define MOD 100003

int head[MAX_N], to[MAX_M * 2], nxt[MAX_M * 2], cnt;
int dist[MAX_N], ways[MAX_N];
int queue[MAX_N], front, rear;

void add_edge(int u, int v) {
    to[++cnt] = v;
    nxt[cnt] = head[u];
    head[u] = cnt;
}

void bfs() {
    memset(dist, -1, sizeof(dist));
    dist[1] = 0;
    ways[1] = 1;
    
    front = rear = 0;
    queue[rear++] = 1;
    
    while (front < rear) {
        int u = queue[front++];
        for (int i = head[u]; i; i = nxt[i]) {
            int v = to[i];
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                ways[v] = ways[u];
                queue[rear++] = v;
            } else if (dist[v] == dist[u] + 1) {
                ways[v] = (ways[v] + ways[u]) % MOD;
            }
        }
    }
}

int main() {
    int n, m, x, y;
    scanf("%d %d", &n, &m);
    
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &x, &y);
        add_edge(x, y);
        add_edge(y, x);
    }
    
    bfs();
    
    for (int i = 1; i <= n; i++) {
        printf("%d\n", dist[i] == -1 ? 0 : ways[i]);
    }
    
    return 0;
}