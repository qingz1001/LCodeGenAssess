#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005
#define MAXK 10005

struct Edge {
    int to, c, m;
};

Edge edges[MAXN];
int head[MAXN], cnt;
int n, k;
long long cows[MAXN], limit[MAXN], t[MAXK];

void addEdge(int u, int v, int c, int m) {
    edges[cnt] = (Edge){v, c, m};
    head[u] = cnt++;
}

void dfs(int u, int p) {
    if (u != 1) {
        cows[u] = cows[p] + limit[p];
        limit[u] = limit[p] - cows[p];
    }
    for (int i = head[u]; i != -1; i = edges[i].to) {
        dfs(edges[i].c, u);
    }
}

int main() {
    memset(head, -1, sizeof(head));
    scanf("%d %d", &n, &k);
    for (int i = 1; i <= n; i++) {
        int p, c, m;
        scanf("%d %d %d", &p, &c, &m);
        addEdge(p, i, c, m);
    }
    for (int i = 1; i <= k; i++) {
        scanf("%lld", &t[i]);
    }
    dfs(1, 0);
    for (int i = 1; i <= k; i++) {
        long long maxCows = 0;
        for (int j = 1; j <= n; j++) {
            maxCows += (t[i] - cows[j] - 1) / limit[j];
        }
        printf("%lld\n", maxCows);
    }
    return 0;
}