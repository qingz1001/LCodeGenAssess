#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005
#define MAXM 200005

int n, m;
int head[MAXN], to[MAXM], next[MAXM];
int deg[MAXN];

void add_edge(int u, int v) {
    static int cnt = 0;
    to[cnt] = v, next[cnt] = head[u], head[u] = cnt++;
    deg[v]++;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        add_edge(u, v);
        add_edge(v, u);
    }

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        if (deg[i] == 1) {
            int j = to[head[i]];
            if (deg[j] == 1 && head[j] != -1) {
                ans += deg[j];
            }
        }
    }

    printf("%d\n", ans);
    return 0;
}