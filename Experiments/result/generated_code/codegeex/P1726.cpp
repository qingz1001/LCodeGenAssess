#include <stdio.h>
#include <stdlib.h>

#define MAXN 5001
#define MAXM 50001

int n, m;
int head[MAXN], to[MAXM], next[MAXM], tot;
int head2[MAXN], to2[MAXM], next2[MAXM], tot2;
int dfn[MAXN], low[MAXN], sccno[MAXN], scc_cnt, index;
int belong[MAXN], r[MAXN], size[MAXN];
int st[MAXN], top;
int que[MAXN], headq, tailq;

void addedge(int x, int y) {
    to[tot] = y;
    next[tot] = head[x];
    head[x] = tot++;
}

void addedge2(int x, int y) {
    to2[tot2] = y;
    next2[tot2] = head2[x];
    head2[x] = tot2++;
}

void tarjan(int x) {
    dfn[x] = low[x] = ++index;
    st[++top] = x;
    for (int i = head[x]; i != -1; i = next[i]) {
        int u = to[i];
        if (!dfn[u]) {
            tarjan(u);
            low[x] = (low[x] < low[u]) ? low[x] : low[u];
        } else if (!sccno[u]) {
            low[x] = (low[x] < dfn[u]) ? low[x] : dfn[u];
        }
    }
    if (dfn[x] == low[x]) {
        int y;
        scc_cnt++;
        do {
            y = st[top--];
            sccno[y] = scc_cnt;
            belong[y] = scc_cnt;
            r[scc_cnt]++;
            size[scc_cnt] = (size[scc_cnt] < y) ? y : size[scc_cnt];
        } while (x != y);
    }
}

void bfs(int s) {
    headq = tailq = 0;
    que[tailq++] = s;
    while (headq < tailq) {
        int x = que[headq++];
        for (int i = head2[x]; i != -1; i = next2[i]) {
            int u = to2[i];
            belong[u] = s;
            r[s] += r[u];
            size[s] = (size[s] < size[u]) ? size[s] : size[u];
            if (!--r[u]) {
                que[tailq++] = u;
            }
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i <= n; i++) {
        head[i] = head2[i] = -1;
    }
    for (int i = 1; i <= m; i++) {
        int a, b, t;
        scanf("%d%d%d", &a, &b, &t);
        addedge(a, b);
        if (t == 2) {
            addedge(b, a);
        }
    }
    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) {
            tarjan(i);
        }
    }
    for (int i = 1; i <= scc_cnt; i++) {
        r[i]++;
    }
    for (int i = 1; i <= n; i++) {
        if (!belong[i]) {
            bfs(i);
        }
    }
    int max = 0, max_scc = 0;
    for (int i = 1; i <= scc_cnt; i++) {
        if (r[i] > max) {
            max = r[i];
            max_scc = i;
        }
    }
    printf("%d\n", max);
    for (int i = 1; i <= n; i++) {
        if (belong[i] == max_scc) {
            printf("%d ", i);
        }
    }
    printf("\n");
    return 0;
}