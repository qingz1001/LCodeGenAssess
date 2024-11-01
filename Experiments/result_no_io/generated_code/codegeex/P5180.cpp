#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 200005;
const int MAXM = 300005;

vector<int> adj[MAXM];
int semi[MAXN];
int idom[MAXN];
int dom[MAXN];
int ancestor[MAXN];
int bucket[MAXN];
int n, m;

void dfs(int u) {
    int num = 0;
    for (int v : adj[u]) {
        if (semi[v] == -1) {
            dfs(v);
        }
        if (semi[v] != 0) {
            bucket[semi[v]]++;
            num++;
        }
    }
    for (int i = 1; i <= num; i++) {
        bucket[i] = 0;
    }
    for (int v : adj[u]) {
        if (semi[v] != 0) {
            semi[u] = min(semi[u], semi[v] - (bucket[semi[v]] == 1));
        }
    }
    semi[u] = min(semi[u], semi[u] - (bucket[semi[u]] == 1));
}

void find_idom() {
    for (int i = 1; i <= n; i++) {
        semi[i] = dom[i] = i;
    }
    semi[1] = 0;
    for (int i = n; i >= 2; i--) {
        dfs(i);
        int u = i;
        while (semi[u] != 0) {
            for (int v : adj[semi[u]]) {
                if (semi[v] != 0) {
                    u = ancestor[v];
                }
            }
            ancestor[i] = u;
            u = ancestor[u];
            semi[i] = min(semi[i], semi[u]);
        }
        dom[i] = semi[i];
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        adj[u].push_back(v);
    }
    find_idom();
    for (int i = 1; i <= n; i++) {
        printf("%d ", dom[i]);
    }
    return 0;
}