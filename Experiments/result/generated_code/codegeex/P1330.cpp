#include <stdio.h>
#include <stdlib.h>

#define MAXN 10005
#define MAXM 100005

int n, m;
int adj[MAXN][MAXN];
int color[MAXN];
int count1, count2;

void dfs(int u, int c) {
    color[u] = c;
    if (c == 1) count1++;
    else count2++;
    for (int v = 1; v <= n; v++) {
        if (adj[u][v] && !color[v]) {
            dfs(v, 3 - c);
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        adj[u][v] = adj[v][u] = 1;
    }

    for (int i = 1; i <= n; i++) {
        if (!color[i]) {
            count1 = count2 = 0;
            dfs(i, 1);
            if (count1 > count2) {
                count1 += count2;
                count2 = 0;
            } else {
                count2 += count1;
                count1 = 0;
            }
        }
    }

    int result = count1 + count2;
    if (result == m) {
        printf("%d\n", result);
    } else {
        printf("Impossible\n");
    }

    return 0;
}