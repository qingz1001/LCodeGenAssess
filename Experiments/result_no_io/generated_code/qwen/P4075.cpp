#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005
#define MAXM 100005

int n, m;
char nodes[MAXN];
char S[MAXM];
int tree[MAXN][2];
int path[MAXN * 2];

int dfs(int u, int p, int pos) {
    if (pos == m) return 1;
    if (nodes[u - 1] != S[pos]) return 0;
    for (int i = 0; i < 2; i++) {
        if (tree[u][i] && tree[u][i] != p) {
            if (dfs(tree[u][i], u, pos + 1)) return 1;
        }
    }
    return 0;
}

int main() {
    int C;
    scanf("%d", &C);
    while (C--) {
        scanf("%d %d", &n, &m);
        scanf("%s", nodes);
        for (int i = 1; i <= n; i++) {
            tree[i][0] = tree[i][1] = 0;
        }
        for (int i = 1; i < n; i++) {
            int u, v;
            scanf("%d %d", &u, &v);
            tree[u][v > u] = v;
            tree[v][u > v] = u;
        }
        scanf("%s", S);
        long long count = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (i != j) {
                    memset(path, 0, sizeof(path));
                    int len = 0;
                    int u = i, v = j;
                    while (v) {
                        path[len++] = v;
                        v = tree[v][u > v];
                    }
                    int ok = 1;
                    for (int k = len - 1; k >= 0; k -= m) {
                        if (!dfs(path[k], 0, 0)) {
                            ok = 0;
                            break;
                        }
                    }
                    if (ok) count++;
                }
            }
        }
        printf("%lld\n", count);
    }
    return 0;
}