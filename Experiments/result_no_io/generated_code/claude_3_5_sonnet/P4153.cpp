#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_N 150005
#define MAX_M 300005

typedef long long ll;

int n, m, s, t, k;
int head[MAX_N], ver[MAX_M], edge[MAX_M], next[MAX_M], tot;
int d[MAX_N], vis[MAX_N], incf[MAX_N], pre[MAX_N];
ll dist[MAX_N];
ll ans[MAX_M];
int cnt;

void add(int x, int y, int z) {
    ver[++tot] = y, edge[tot] = z, next[tot] = head[x], head[x] = tot;
}

int cmp(const void *a, const void *b) {
    return *(ll*)a > *(ll*)b ? 1 : -1;
}

int spfa() {
    for (int i = 1; i <= n; i++) d[i] = 0, vis[i] = 0;
    int q[MAX_N], hh = 0, tt = -1;
    q[++tt] = s; d[s] = INT_MAX; vis[s] = 1;
    while (hh <= tt) {
        int x = q[hh++];
        vis[x] = 0;
        for (int i = head[x]; i; i = next[i]) {
            int y = ver[i], z = edge[i];
            if (d[y] < (d[x] < z ? d[x] : z)) {
                d[y] = d[x] < z ? d[x] : z;
                incf[y] = x; pre[y] = i;
                if (!vis[y]) q[++tt] = y, vis[y] = 1;
            }
        }
    }
    return d[t] > 0;
}

void dijkstra() {
    for (int i = 1; i <= n; i++) dist[i] = LLONG_MAX, vis[i] = 0;
    dist[s] = 0;
    for (int i = 1; i < n; i++) {
        int x = 0;
        for (int j = 1; j <= n; j++)
            if (!vis[j] && (!x || dist[j] < dist[x])) x = j;
        vis[x] = 1;
        for (int j = head[x]; j; j = next[j]) {
            int y = ver[j], z = edge[j];
            if (dist[y] > dist[x] + z) dist[y] = dist[x] + z;
        }
    }
}

void solve() {
    dijkstra();
    while (spfa()) {
        ll sum = 0;
        for (int x = t; x != s; x = incf[x]) {
            sum += edge[pre[x]];
            edge[pre[x]] = 0;
        }
        ans[cnt++] = dist[t] + sum;
        if (cnt == k) return;
    }
}

int main() {
    scanf("%d%d%d%d%d", &n, &m, &s, &t, &k);
    for (int i = 1; i <= m; i++) {
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        add(x, y, z);
    }
    solve();
    qsort(ans, cnt, sizeof(ll), cmp);
    for (int i = 0; i < cnt; i++) printf("%lld\n", ans[i]);
    if (cnt < k) printf("-1\n");
    return 0;
}