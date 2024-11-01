#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_N 10005
#define MAX_M 50005
#define INF 0x3f3f3f3f

typedef struct {
    int v, next, w;
} Edge;

Edge edge[MAX_M * 2];
int head[MAX_N], cnt;
int n, m, b;
int f[MAX_N];
int dist[MAX_N];
bool vis[MAX_N];

void add_edge(int u, int v, int w) {
    edge[++cnt].v = v;
    edge[cnt].w = w;
    edge[cnt].next = head[u];
    head[u] = cnt;
}

bool check(int mid) {
    memset(dist, 0x3f, sizeof(dist));
    memset(vis, 0, sizeof(vis));
    dist[1] = 0;

    for (int i = 1; i <= n; i++) {
        int u = 0;
        for (int j = 1; j <= n; j++) {
            if (!vis[j] && (u == 0 || dist[j] < dist[u])) {
                u = j;
            }
        }
        if (u == 0 || dist[u] > b) break;
        vis[u] = true;
        
        for (int e = head[u]; e; e = edge[e].next) {
            int v = edge[e].v;
            if (f[v] <= mid && dist[v] > dist[u] + edge[e].w) {
                dist[v] = dist[u] + edge[e].w;
            }
        }
    }
    
    return dist[n] <= b;
}

int main() {
    scanf("%d%d%d", &n, &m, &b);
    
    int max_f = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &f[i]);
        if (f[i] > max_f) max_f = f[i];
    }
    
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        add_edge(u, v, w);
        add_edge(v, u, w);
    }
    
    int l = 0, r = max_f, ans = -1;
    while (l <= r) {
        int mid = l + (r - l) / 2;
        if (check(mid)) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    
    if (ans == -1) {
        printf("AFK\n");
    } else {
        printf("%d\n", ans);
    }
    
    return 0;
}