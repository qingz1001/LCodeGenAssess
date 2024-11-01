#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 100005
#define MAX_M 1000005
#define INF 0x3f3f3f3f3f3f3f3fLL

typedef long long ll;

int n, m;
int h[MAX_N];
int head[MAX_N], to[MAX_M], nxt[MAX_M], w[MAX_M], cnt;
ll dist[MAX_N];
int que[MAX_N], inq[MAX_N];
int ord[MAX_N], id[MAX_N];

void add_edge(int u, int v, int k) {
    to[++cnt] = v;
    w[cnt] = k;
    nxt[cnt] = head[u];
    head[u] = cnt;
}

int cmp(const void *a, const void *b) {
    return h[*(int*)b] - h[*(int*)a];
}

void spfa(int s) {
    memset(dist, 0x3f, sizeof(dist));
    dist[s] = 0;
    int hh = 0, tt = 1;
    que[0] = s;
    inq[s] = 1;
    
    while (hh != tt) {
        int u = que[hh++];
        if (hh == MAX_N) hh = 0;
        inq[u] = 0;
        
        for (int i = head[u]; i; i = nxt[i]) {
            int v = to[i];
            if (dist[v] > dist[u] + w[i]) {
                dist[v] = dist[u] + w[i];
                if (!inq[v]) {
                    inq[v] = 1;
                    que[tt++] = v;
                    if (tt == MAX_N) tt = 0;
                }
            }
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &h[i]);
        id[i] = i;
    }
    
    qsort(id + 1, n, sizeof(int), cmp);
    
    for (int i = 1; i <= m; i++) {
        int u, v, k;
        scanf("%d%d%d", &u, &v, &k);
        add_edge(u, v, k);
        add_edge(v, u, k);
    }
    
    spfa(1);
    
    int ans = 0;
    ll min_dist = INF;
    
    for (int i = 1; i <= n; i++) {
        int u = id[i];
        if (dist[u] == INF) continue;
        ans++;
        if (dist[u] < min_dist) min_dist = dist[u];
    }
    
    printf("%d %lld\n", ans, min_dist);
    
    return 0;
}