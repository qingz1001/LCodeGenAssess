#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

const int N = 500005;
int n, m, q;
vector<int> G[N];
int low[N], dfn[N], cnt, scc[N], scc_cnt, stk[N], top, in[N];
bool instack[N];

void tarjan(int u) {
    dfn[u] = low[u] = ++cnt;
    stk[++top] = u;
    instack[u] = true;
    for (int v : G[u]) {
        if (!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (instack[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if (low[u] == dfn[u]) {
        int v;
        scc_cnt++;
        do {
            v = stk[top--];
            instack[v] = false;
            scc[v] = scc_cnt;
        } while (u != v);
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) tarjan(i);
    }
    scanf("%d", &q);
    while (q--) {
        int u, v;
        scanf("%d%d", &u, &v);
        if (scc[u] == scc[v]) {
            printf("%d\n", 2);
        } else {
            printf("%d\n", 3);
        }
    }
    return 0;
}