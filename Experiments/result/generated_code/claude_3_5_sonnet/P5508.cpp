#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))
#define INF 0x3f3f3f3f3f3f3f3fLL

typedef long long ll;

const int MAXN = 50005;
const int MAXM = 50005;

int n, m;
ll v[MAXN];
int sl[MAXM], sr[MAXM], tl[MAXM], tr[MAXM];
ll w[MAXM];

ll dist[MAXN];
int pre[MAXN];

void dijkstra() {
    int vis[MAXN] = {0};
    for (int i = 1; i <= n; i++) {
        dist[i] = INF;
        pre[i] = -1;
    }
    dist[1] = 0;
    
    for (int i = 1; i <= n; i++) {
        int u = -1;
        ll mindist = INF;
        for (int j = 1; j <= n; j++) {
            if (!vis[j] && dist[j] < mindist) {
                u = j;
                mindist = dist[j];
            }
        }
        if (u == -1) break;
        vis[u] = 1;
        
        // 已有隧道
        for (int j = 0; j < m; j++) {
            if (u >= sl[j] && u <= sr[j]) {
                for (int k = tl[j]; k <= tr[j]; k++) {
                    if (dist[k] > dist[u] + w[j]) {
                        dist[k] = dist[u] + w[j];
                        pre[k] = u;
                    }
                }
            }
            if (u >= tl[j] && u <= tr[j]) {
                for (int k = sl[j]; k <= sr[j]; k++) {
                    if (dist[k] > dist[u] + w[j]) {
                        dist[k] = dist[u] + w[j];
                        pre[k] = u;
                    }
                }
            }
        }
        
        // 挖掘新隧道
        if (v[u]) {
            for (int j = 1; j <= n; j++) {
                ll cost = (ll)abs(j - u) * v[u];
                if (dist[j] > dist[u] + cost) {
                    dist[j] = dist[u] + cost;
                    pre[j] = u;
                }
            }
        }
    }
}

int path[MAXN], path_len;

void print_path() {
    int cur = n;
    path_len = 0;
    while (cur != -1) {
        path[path_len++] = cur;
        cur = pre[cur];
    }
    printf("%d\n", path_len);
    for (int i = path_len - 1; i >= 0; i--) {
        printf("%d ", path[i]);
    }
    printf("\n");
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &v[i]);
    }
    for (int i = 0; i < m; i++) {
        scanf("%d%d%d%d%lld", &sl[i], &sr[i], &tl[i], &tr[i], &w[i]);
    }
    
    dijkstra();
    
    if (dist[n] == INF) {
        printf("-1\n");
    } else {
        printf("%lld\n", dist[n]);
        print_path();
    }
    
    return 0;
}