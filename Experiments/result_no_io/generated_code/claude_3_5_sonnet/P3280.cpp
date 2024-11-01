#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_N 100005
#define MAX_M 200005
#define INF 0x3f3f3f3f

typedef long long ll;

struct Edge {
    int to, next, cap;
} edge[MAX_M * 2];

int head[MAX_N], cnt;
int order[MAX_N], b[MAX_N];
int n, m, q;
int dist[MAX_N], vis[MAX_N];
int que[MAX_N], front, rear;

void add_edge(int u, int v, int w) {
    edge[cnt].to = v;
    edge[cnt].cap = w;
    edge[cnt].next = head[u];
    head[u] = cnt++;
    edge[cnt].to = u;
    edge[cnt].cap = w;
    edge[cnt].next = head[v];
    head[v] = cnt++;
}

void spfa(int s) {
    memset(dist, 0x3f, sizeof(dist));
    memset(vis, 0, sizeof(vis));
    front = rear = 0;
    dist[s] = 0;
    que[rear++] = s;
    vis[s] = 1;
    
    while (front < rear) {
        int u = que[front++];
        vis[u] = 0;
        for (int i = head[u]; ~i; i = edge[i].next) {
            int v = edge[i].to;
            if (dist[v] > dist[u] + 1) {
                dist[v] = dist[u] + 1;
                if (!vis[v]) {
                    que[rear++] = v;
                    vis[v] = 1;
                }
            }
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
    }
    
    int has_station[MAX_N] = {0};
    for (int i = 0; i < q; i++) {
        int x;
        scanf("%d", &x);
        has_station[x] = 1;
    }
    
    ll gold = 0, max_gold = 0;
    for (int i = 1; i <= n; i++) {
        int city = order[i];
        spfa(city);
        
        ll min_cap = INF;
        for (int j = 1; j <= n; j++) {
            if (dist[j] <= dist[city] && has_station[j]) {
                for (int k = head[j]; ~k; k = edge[k].next) {
                    if (dist[edge[k].to] == dist[j] - 1) {
                        min_cap = (min_cap < edge[k].cap) ? min_cap : edge[k].cap;
                        break;
                    }
                }
                break;
            }
        }
        
        if (b[city] > 0) {
            ll buy = (min_cap < b[city]) ? min_cap : b[city];
            gold += buy;
            max_gold = (max_gold > gold) ? max_gold : gold;
        } else {
            ll sell = (-b[city] < gold) ? -b[city] : gold;
            gold -= sell;
            printf("%lld\n", sell);
        }
    }
    
    return 0;
}