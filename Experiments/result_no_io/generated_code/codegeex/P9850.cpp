#include <stdio.h>
#include <string.h>

const int MAXN = 100005;
const int MAXM = 200005;

int n, m, u, v, res;
int deg[MAXN], e[MAXN];
int vis[MAXN];
int head[MAXN], next[MAXM], ver[MAXM];

void add(int x, int y) {
    ver[++e[0]] = y;
    next[e[0]] = head[x];
    head[x] = e[0];
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
        scanf("%d%d", &u, &v);
        add(u, v);
        add(v, u);
        deg[u]++;
        deg[v]++;
    }
    for (int i = 1; i <= n; i++) {
        memset(vis, 0, sizeof(vis));
        for (int j = head[i]; j; j = next[j]) {
            int y = ver[j];
            vis[deg[y]]++;
        }
        for (int j = 0; j <= n - 1; j++) {
            vis[j] += vis[j - 1];
        }
        for (int j = head[i]; j; j = next[j]) {
            int y = ver[j];
            if (vis[deg[y] - 1] == 0) {
                res++;
            }
        }
    }
    printf("%d\n", res);
    return 0;
}