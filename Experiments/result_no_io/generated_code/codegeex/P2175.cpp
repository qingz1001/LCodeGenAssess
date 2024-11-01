#include <stdio.h>
#include <stdlib.h>

#define MAXN 2001

int n;
int G[MAXN][MAXN];
int color[MAXN];

int dfs(int u, int c) {
    color[u] = c;
    for (int v = 1; v <= n; v++) {
        if (G[u][v] && color[v] == c) return 0;
        if (G[u][v] && color[v] == -1 && !dfs(v, !c)) return 0;
    }
    return 1;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        int x;
        while (scanf("%d", &x) && x) {
            G[i][x] = 1;
            G[x][i] = 1;
        }
    }

    for (int i = 1; i <= n; i++) {
        color[i] = -1;
    }

    for (int i = 1; i <= n; i++) {
        if (color[i] == -1 && !dfs(i, 0)) {
            printf("No solution\n");
            return 0;
        }
    }

    int cnt0 = 0, cnt1 = 0;
    for (int i = 1; i <= n; i++) {
        if (color[i]) cnt1++;
        else cnt0++;
    }

    if (cnt0 > cnt1) printf("%d %d\n", cnt1, cnt0);
    else printf("%d %d\n", cnt0, cnt1);

    return 0;
}