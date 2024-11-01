#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXN 100005
#define MAXM 500005
#define INF 0x3f3f3f3f

struct Edge {
    int to, next;
} edge[MAXM * 2];

int head[MAXN], cnt;
int n, m, price[MAXN];
int min_price[MAXN], max_profit[MAXN];
int queue[MAXN * 10], front, rear;
int vis[MAXN];

void add_edge(int u, int v) {
    edge[++cnt].to = v;
    edge[cnt].next = head[u];
    head[u] = cnt;
}

void spfa(int start, int *dist, int flag) {
    memset(vis, 0, sizeof(vis));
    front = rear = 0;
    queue[rear++] = start;
    vis[start] = 1;
    
    while (front < rear) {
        int u = queue[front++];
        vis[u] = 0;
        
        for (int i = head[u]; i; i = edge[i].next) {
            int v = edge[i].to;
            if (flag && dist[v] > (dist[u] < price[v] ? dist[u] : price[v])) {
                dist[v] = (dist[u] < price[v] ? dist[u] : price[v]);
                if (!vis[v]) {
                    queue[rear++] = v;
                    vis[v] = 1;
                }
            }
            if (!flag && dist[v] < (dist[u] > price[v] ? dist[u] : price[v])) {
                dist[v] = (dist[u] > price[v] ? dist[u] : price[v]);
                if (!vis[v]) {
                    queue[rear++] = v;
                    vis[v] = 1;
                }
            }
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &price[i]);
    }
    
    for (int i = 1; i <= m; i++) {
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        add_edge(x, y);
        if (z == 2) add_edge(y, x);
    }
    
    memset(min_price, 0x3f, sizeof(min_price));
    memset(max_profit, 0, sizeof(max_profit));
    min_price[1] = price[1];
    max_profit[n] = price[n];
    
    spfa(1, min_price, 1);
    spfa(n, max_profit, 0);
    
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        if (max_profit[i] - min_price[i] > ans) {
            ans = max_profit[i] - min_price[i];
        }
    }
    
    printf("%d\n", ans);
    return 0;
}