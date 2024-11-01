#include <stdio.h>
#include <string.h>

#define MAXN 105
#define MAXM 610

int n, m, c1, c2;
int g[MAXN][MAXN];
int vis[MAXN];
int cnt[MAXN];
int q[MAXN];
int head, tail;

void bfs(int s) {
    head = tail = 1;
    q[1] = s;
    vis[s] = 1;
    while (head <= tail) {
        int x = q[head++];
        for (int i = 1; i <= n; i++) {
            if (g[x][i] && !vis[i]) {
                vis[i] = 1;
                q[++tail] = i;
                cnt[i] = cnt[x] + 1;
            }
        }
    }
}

int main() {
    scanf("%d%d%d%d", &n, &m, &c1, &c2);
    memset(g, 0, sizeof(g));
    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        g[a][b] = g[b][a] = 1;
    }

    memset(vis, 0, sizeof(vis));
    memset(cnt, 0, sizeof(cnt));
    bfs(c1);
    int max = 0;
    for (int i = 1; i <= n; i++) {
        if (cnt[i] > max && i != c2) {
            max = cnt[i];
        }
    }

    memset(vis, 0, sizeof(vis));
    memset(cnt, 0, sizeof(cnt));
    bfs(c2);
    for (int i = 1; i <= n; i++) {
        if (cnt[i] > max && i != c1) {
            max = cnt[i];
        }
    }

    printf("%d\n", max);
    return 0;
}