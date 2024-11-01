#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 100005;
const int MAXM = 400005;

vector<int> adj[MAXN];
int low[MAXN], dfn[MAXN], visited[MAXN], stack[MAXN], inStack[MAXN], component[MAXN];
int index, componentCount;

void tarjan(int u) {
    low[u] = dfn[u] = ++index;
    stack[++stack[0]] = u;
    inStack[u] = 1;

    for (int v : adj[u]) {
        if (!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (inStack[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }

    if (low[u] == dfn[u]) {
        componentCount++;
        int v;
        do {
            v = stack[stack[0]--];
            inStack[v] = 0;
            component[v] = componentCount;
        } while (v != u);
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) {
            tarjan(i);
        }
    }

    int ans = 0;
    for (int u = 1; u <= n; u++) {
        for (int v : adj[u]) {
            if (component[u] != component[v]) {
                ans++;
            }
        }
    }

    printf("%d\n", ans);

    return 0;
}