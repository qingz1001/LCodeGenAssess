#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 200005;
vector<int> G[MAXN], RG[MAXN], NG[MAXN];
int n, m, ID[MAXN], IDcnt, dfn[MAXN], rnk[MAXN], fa[MAXN], semi[MAXN], dom[MAXN];
int insemi[MAXN], outsemi[MAXN], in[MAXN], out[MAXN];

void dfs(int u) {
    insemi[u] = in[u] = ++IDcnt;
    dfn[IDcnt] = u;
    for (int i = 0; i < G[u].size(); i++) {
        int v = G[u][i];
        if (!dfn[v]) {
            fa[v] = u;
            dfs(v);
        }
    }
    outsemi[u] = out[u] = IDcnt;
}

void dfs(int u, int father) {
    semi[u] = u;
    for (int i = 0; i < NG[u].size(); i++) {
        int v = NG[u][i];
        dfs(v, u);
        if (outsemi[v] < outsemi[u]) {
            outsemi[u] = outsemi[v];
            semi[u] = semi[v];
        }
    }
}

void dfs(int u, int father) {
    rnk[ID[insemi[u]]] = u;
    if (father) {
        while (insemi[u] < insemi[father]) {
            dom[u] = semi[u];
            u = fa[dfn[insemi[u]]];
        }
        if (u != father) {
            dom[u] = dom[father];
        }
    }
    for (int i = 0; i < RG[u].size(); i++) {
        int v = RG[u][i];
        dfs(v, u);
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        G[u].push_back(v);
    }
    dfs(1);
    for (int i = 1; i <= n; i++) {
        if (!semi[i]) {
            dfs(i, 0);
        }
    }
    for (int u = 1; u <= n; u++) {
        for (int i = 0; i < G[u].size(); i++) {
            int v = G[u][i];
            if (dfn[u] < dfn[v]) {
                NG[u].push_back(v);
                RG[v].push_back(u);
            }
        }
    }
    dfs(1, 0);
    for (int i = 1; i <= n; i++) {
        int cnt = 0;
        for (int j = 1; j <= n; j++) {
            if (rnk[j] <= rnk[dom[i]] && rnk[dom[i]] <= rnk[j]) {
                cnt++;
            }
        }
        printf("%d ", cnt);
    }
    return 0;
}