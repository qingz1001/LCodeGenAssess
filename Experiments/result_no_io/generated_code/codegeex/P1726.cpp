#include <stdio.h>
#include <stdlib.h>

#define MAXN 5001
#define MAXM 10001

int n, m;
int head[MAXN], to[MAXM], nxt[MAXM], cnt;
int in[MAXN], out[MAXN];
int scc_id[MAXN], scc_cnt;
int scc_size[MAXN];
int scc_top[MAXN];
int stack[MAXN], top;
int dfn[MAXN], low[MAXN];
int index;

void add_edge(int u, int v) {
    nxt[++cnt] = head[u];
    head[u] = cnt;
    to[cnt] = v;
}

void tarjan(int u) {
    dfn[u] = low[u] = ++index;
    stack[++top] = u;
    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i];
        if (!dfn[v]) {
            tarjan(v);
            low[u] = (low[u] < low[v]) ? low[u] : low[v];
        } else if (!scc_id[v]) {
            low[u] = (low[u] < dfn[v]) ? low[u] : dfn[v];
        }
    }
    if (dfn[u] == low[u]) {
        int v;
        scc_cnt++;
        do {
            v = stack[top--];
            scc_id[v] = scc_cnt;
            scc_size[scc_cnt]++;
        } while (u != v);
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
        int a, b, t;
        scanf("%d%d%d", &a, &b, &t);
        if (t == 1) {
            add_edge(a, b);
            in[b]++;
        } else if (t == 2) {
            add_edge(a, b);
            add_edge(b, a);
        }
    }

    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) {
            tarjan(i);
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = head[i]; j; j = nxt[j]) {
            int v = to[j];
            if (scc_id[i] != scc_id[v]) {
                out[scc_id[i]]++;
            }
        }
    }

    int max_scc = 0, max_size = 0;
    for (int i = 1; i <= scc_cnt; i++) {
        if (!out[i]) {
            if (scc_size[i] > max_size) {
                max_size = scc_size[i];
                max_scc = i;
            }
        }
    }

    printf("%d\n", max_size);
    for (int i = 1; i <= n; i++) {
        if (scc_id[i] == max_scc) {
            printf("%d ", i);
        }
    }
    printf("\n");

    return 0;
}