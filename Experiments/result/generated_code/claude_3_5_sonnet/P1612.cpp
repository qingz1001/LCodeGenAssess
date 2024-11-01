#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005
#define MAXM 20

int n;
int parent[MAXN];
long long w[MAXN], c[MAXN];
int depth[MAXN];
int ancestor[MAXN][MAXM];
long long prefixSum[MAXN];

void dfs(int u, int p, int d) {
    depth[u] = d;
    ancestor[u][0] = p;
    prefixSum[u] = prefixSum[p] + w[u];

    for (int i = 1; i < MAXM; i++) {
        ancestor[u][i] = ancestor[ancestor[u][i-1]][i-1];
    }

    for (int v = 1; v <= n; v++) {
        if (parent[v] == u) {
            dfs(v, u, d + 1);
        }
    }
}

int getLongestChain(int u) {
    int length = 0;
    long long sum = 0;
    int v = u;

    while (v != 0 && sum + w[v] <= c[u]) {
        sum += w[v];
        length++;
        v = parent[v];
    }

    return length;
}

int main() {
    scanf("%d", &n);

    for (int i = 2; i <= n; i++) {
        scanf("%d", &parent[i]);
    }

    for (int i = 1; i <= n; i++) {
        scanf("%lld", &w[i]);
    }

    for (int i = 1; i <= n; i++) {
        scanf("%lld", &c[i]);
    }

    dfs(1, 0, 0);

    for (int i = 1; i <= n; i++) {
        printf("%d ", getLongestChain(i));
    }

    return 0;
}