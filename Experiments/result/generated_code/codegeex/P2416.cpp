#include <stdio.h>
#include <stdlib.h>

#define MAXN 300005
#define MAXM 600005

int n, m;
int head[MAXN], to[MAXM], nxt[MAXM], cnt;
int dfn[MAXN], low[MAXN], tot, inStack[MAXN], sccId[MAXN], sccCnt;
int stack[MAXN], top;
int edgeInSCC[MAXM];
int q, s, t;

void addEdge(int x, int y) {
    to[cnt] = y;
    nxt[cnt] = head[x];
    head[x] = cnt++;
}

void tarjan(int u) {
    dfn[u] = low[u] = ++tot;
    stack[++top] = u;
    inStack[u] = 1;

    for (int i = head[u]; i != -1; i = nxt[i]) {
        int v = to[i];
        if (!dfn[v]) {
            tarjan(v);
            low[u] = (low[u] < low[v]) ? low[u] : low[v];
        } else if (inStack[v]) {
            low[u] = (low[u] < dfn[v]) ? low[u] : dfn[v];
        }
    }

    if (dfn[u] == low[u]) {
        sccCnt++;
        int v;
        do {
            v = stack[top--];
            inStack[v] = 0;
            sccId[v] = sccCnt;
        } while (u != v);
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < MAXN; i++) head[i] = -1;
    for (int i = 0; i < m; i++) {
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        addEdge(x, y);
        addEdge(y, x);
        if (z == 1) edgeInSCC[i] = 1;
    }

    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) tarjan(i);
    }

    scanf("%d", &q);
    while (q--) {
        scanf("%d%d", &s, &t);
        if (sccId[s] == sccId[t]) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }

    return 0;
}