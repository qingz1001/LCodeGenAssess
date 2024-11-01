#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_N 100005
#define MAX_M 200005
#define INF 1000000000

int n, m, q;
int order[MAX_N], b[MAX_N];
int train[MAX_N];
bool has_train[MAX_N];

struct Edge {
    int to, next, weight;
} edge[MAX_M * 2];

int head[MAX_N], cnt;

void add_edge(int u, int v, int w) {
    edge[cnt].to = v;
    edge[cnt].weight = w;
    edge[cnt].next = head[u];
    head[u] = cnt++;
}

int dis[MAX_N];
bool vis[MAX_N];

void dijkstra(int s) {
    memset(dis, 0x3f, sizeof(dis));
    memset(vis, false, sizeof(vis));
    dis[s] = 0;
    
    for (int i = 1; i <= n; i++) {
        int u = 0, min_dis = INF;
        for (int j = 1; j <= n; j++) {
            if (!vis[j] && dis[j] < min_dis) {
                u = j;
                min_dis = dis[j];
            }
        }
        if (u == 0) break;
        vis[u] = true;
        
        for (int e = head[u]; e != -1; e = edge[e].next) {
            int v = edge[e].to;
            if (dis[v] > dis[u] + edge[e].weight) {
                dis[v] = dis[u] + edge[e].weight;
            }
        }
    }
    
    for (int i = 1; i <= n; i++) {
        if (has_train[i]) {
            dis[i] = 0;
        }
    }
}

int main() {
    scanf("%d%d%d", &n, &m, &q);
    
    for (int i = 1; i <= n; i++) {
        scanf("%d", &order[i]);
    }
    
    for (int i = 1; i <= n; i++) {
        scanf("%d", &b[i]);
    }
    
    memset(head, -1, sizeof(head));
    
    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        add_edge(u, v, w);
        add_edge(v, u, w);
    }
    
    memset(has_train, false, sizeof(has_train));
    for (int i = 0; i < q; i++) {
        int x;
        scanf("%d", &x);
        has_train[x] = true;
    }
    
    int cur = 0, pos = order[1];
    for (int i = 1; i <= n; i++) {
        dijkstra(pos);
        int to = order[i];
        int max_load = dis[to];
        
        if (b[to] > 0) {
            cur += b[to];
            if (cur > max_load) cur = max_load;
        } else {
            int sell = -b[to];
            if (sell > cur) sell = cur;
            printf("%d\n", sell);
            cur -= sell;
        }
        
        pos = to;
    }
    
    return 0;
}