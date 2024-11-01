#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005
#define MAXM 200005

int n, m;
int tot, head[MAXN], to[MAXM], next[MAXM];
int cnt, dfn[MAXN], low[MAXN], sccno[MAXN], belong[MAXN];
int sta[MAXN], top;
bool vis[MAXN];

void add(int u, int v) {
    to[tot] = v;
    next[tot] = head[u];
    head[u] = tot++;
}

void tarjan(int u) {
    dfn[u] = low[u] = ++cnt;
    sta[++top] = u;
    vis[u] = true;
    for (int i = head[u]; i != -1; i = next[i]) {
        int v = to[i];
        if (!dfn[v]) {
            tarjan(v);
            low[u] = (low[u] < low[v]) ? low[u] : low[v];
        } else if (vis[v]) {
            low[u] = (low[u] < dfn[v]) ? low[u] : dfn[v];
        }
    }
    if (dfn[u] == low[u]) {
        int j;
        sccno[u] = ++cnt;
        belong[u] = cnt;
        vis[u] = false;
        while ((j = sta[top--]) != u) {
            sccno[j] = cnt;
            belong[j] = cnt;
            vis[j] = false;
        }
    }
}

int main() {
    int u, v;
    scanf("%d%d", &n, &m);
    memset(head, -1, sizeof(head));
    tot = 0;
    cnt = 0;
    top = 0;
    memset(vis, false, sizeof(vis));
    memset(dfn, 0, sizeof(dfn));
    memset(low, 0, sizeof(low));
    memset(sccno, 0, sizeof(sccno));
    memset(belong, 0, sizeof(belong));

    for (int i = 0; i < m; i++) {
        scanf("%d%d", &u, &v);
        add(u, v);
        add(v, u);
    }

    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) {
            tarjan(i);
        }
    }

    int ans = 0;
    for (int i = 1; i <= cnt; i++) {
        if (belong[i] == i) {
            ans++;
        }
    }

    printf("%d\n", ans);
    return 0;
}