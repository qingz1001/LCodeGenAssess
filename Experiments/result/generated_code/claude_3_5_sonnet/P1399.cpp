#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_N 100005
#define INF 1e18

typedef long long ll;

struct Edge {
    int to, next;
    ll len;
} edge[MAX_N * 2];

int head[MAX_N], cnt;
ll dis[MAX_N], max_dis[MAX_N];
int n;

void add_edge(int u, int v, ll w) {
    edge[cnt].to = v;
    edge[cnt].len = w;
    edge[cnt].next = head[u];
    head[u] = cnt++;
}

void dfs(int u, int fa) {
    ll max1 = 0, max2 = 0;
    for (int i = head[u]; ~i; i = edge[i].next) {
        int v = edge[i].to;
        if (v == fa) continue;
        dfs(v, u);
        ll d = max_dis[v] + edge[i].len;
        if (d > max1) {
            max2 = max1;
            max1 = d;
        } else if (d > max2) {
            max2 = d;
        }
    }
    max_dis[u] = max1;
    dis[u] = max1 + max2;
}

void dfs2(int u, int fa, ll up) {
    ll max1 = up, max2 = 0;
    for (int i = head[u]; ~i; i = edge[i].next) {
        int v = edge[i].to;
        if (v == fa) continue;
        ll d = max_dis[v] + edge[i].len;
        if (d > max1) {
            max2 = max1;
            max1 = d;
        } else if (d > max2) {
            max2 = d;
        }
    }
    
    for (int i = head[u]; ~i; i = edge[i].next) {
        int v = edge[i].to;
        if (v == fa) continue;
        ll d = max_dis[v] + edge[i].len;
        ll new_up = (d == max1) ? max2 : max1;
        new_up = (new_up > up) ? new_up : up;
        dfs2(v, u, new_up + edge[i].len);
    }
    
    dis[u] = (dis[u] > max1 + max2) ? dis[u] : max1 + max2;
}

int main() {
    scanf("%d", &n);
    memset(head, -1, sizeof(head));
    
    for (int i = 1; i < n; i++) {
        int u, v;
        ll w;
        scanf("%d %d %lld", &u, &v, &w);
        add_edge(u, v, w);
        add_edge(v, u, w);
    }
    
    dfs(1, 0);
    dfs2(1, 0, 0);
    
    ll ans = INF;
    for (int i = 1; i <= n; i++) {
        if (dis[i] < ans) ans = dis[i];
    }
    
    printf("%.1f\n", ans / 2.0);
    
    return 0;
}