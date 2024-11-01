#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_N 10001
#define MAX_M 20001

typedef struct {
    int v, w, next;
} Edge;

Edge edges[MAX_M * 2];
int head[MAX_N], cnt;
int n, m, s, t;
int vis[MAX_N], dist[MAX_N];

void add_edge(int u, int v, int w) {
    edges[cnt].v = v;
    edges[cnt].w = w;
    edges[cnt].next = head[u];
    head[u] = cnt++;
}

int dfs(int u, int max_w) {
    if (u == t) return 1;
    vis[u] = 1;
    
    for (int i = head[u]; i != -1; i = edges[i].next) {
        int v = edges[i].v;
        int w = edges[i].w;
        
        if (!vis[v] && w <= max_w) {
            if (dfs(v, max_w)) return 1;
        }
    }
    
    return 0;
}

int binary_search() {
    int left = 0, right = 10000, mid;
    
    while (left < right) {
        mid = left + (right - left) / 2;
        memset(vis, 0, sizeof(vis));
        
        if (dfs(s, mid)) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    
    return left;
}

int main() {
    scanf("%d %d %d %d", &n, &m, &s, &t);
    
    memset(head, -1, sizeof(head));
    
    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        add_edge(u, v, w);
        add_edge(v, u, w);
    }
    
    int result = binary_search();
    printf("%d\n", result);
    
    return 0;
}