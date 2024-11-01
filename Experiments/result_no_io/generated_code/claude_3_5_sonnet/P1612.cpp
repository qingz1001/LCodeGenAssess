#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 100005
#define MAX_M 20

int n;
int parent[MAX_N];
long long w[MAX_N], c[MAX_N];
int depth[MAX_N];
int anc[MAX_N][MAX_M];
long long sum[MAX_N][MAX_M];

void dfs(int u, int p) {
    depth[u] = depth[p] + 1;
    anc[u][0] = p;
    sum[u][0] = w[p];
    for (int i = 1; i < MAX_M; i++) {
        anc[u][i] = anc[anc[u][i-1]][i-1];
        sum[u][i] = sum[u][i-1] + sum[anc[u][i-1]][i-1];
    }
}

int query(int u) {
    int res = 1;
    long long total = w[u];
    for (int i = MAX_M - 1; i >= 0; i--) {
        if (anc[u][i] && total + sum[u][i] <= c[u]) {
            res += (1 << i);
            total += sum[u][i];
            u = anc[u][i];
        }
    }
    return res;
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

    for (int i = 2; i <= n; i++) {
        dfs(i, parent[i]);
    }

    for (int i = 1; i <= n; i++) {
        printf("%d ", query(i));
    }
    printf("\n");

    return 0;
}