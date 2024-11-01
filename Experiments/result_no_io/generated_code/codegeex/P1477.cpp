#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 100005
#define MAXM 1000005

int n, m;
int head[MAXN], to[MAXM], nxt[MAXM], tot;
int in[MAXN], out[MAXN];
int vis[MAXN], color[MAXN], cnt;

void add(int u, int v) {
    to[tot] = v;
    nxt[tot] = head[u];
    head[u] = tot++;
}

void dfs(int u) {
    vis[u] = 1;
    for (int i = head[u]; i != -1; i = nxt[i]) {
        int v = to[i];
        if (!vis[v]) {
            color[v] = (color[u] + 1) % 3;
            dfs(v);
        } else if (color[v] == color[u]) {
            cnt++;
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    memset(head, -1, sizeof(head));
    tot = 0;
    cnt = 0;

    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        add(u, v);
        in[v]++;
        out[u]++;
    }

    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            color[i] = 0;
            dfs(i);
        }
    }

    int max = INT_MIN, min = INT_MAX;
    for (int i = 1; i <= n; i++) {
        if (in[i] != out[i]) {
            cnt++;
        }
        max = fmax(max, in[i] + out[i]);
        min = fmin(min, in[i] + out[i]);
    }

    if (cnt > 0) {
        printf("-1 -1\n");
    } else {
        if (max < 3) {
            printf("-1 -1\n");
        } else {
            printf("%d %d\n", max, min);
        }
    }

    return 0;
}