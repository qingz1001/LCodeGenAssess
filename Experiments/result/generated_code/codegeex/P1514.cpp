#include <stdio.h>
#include <stdlib.h>

#define MAXN 501
#define MAXM 501
#define MAX 1000000

int n, m;
int height[MAXN][MAXM];
int factory[MAXN][MAXM];
int water[MAXN][MAXM];
int min_factories = MAX;

int min(int a, int b) {
    return a < b ? a : b;
}

void dfs(int x, int y, int count) {
    if (x < 1 || x > n || y < 1 || y > m || factory[x][y] || water[x][y]) return;
    factory[x][y] = 1;
    if (x > 1 && height[x-1][y] < height[x][y]) dfs(x-1, y, count);
    if (x < n && height[x+1][y] < height[x][y]) dfs(x+1, y, count);
    if (y > 1 && height[x][y-1] < height[x][y]) dfs(x, y-1, count);
    if (y < m && height[x][y+1] < height[x][y]) dfs(x, y+1, count);
    if (count < min_factories) min_factories = count;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            scanf("%d", &height[i][j]);
        }
    }

    for (int i = 1; i <= m; i++) {
        if (height[1][i] == MAX) continue;
        dfs(1, i, 1);
    }

    int total_factories = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (factory[i][j]) total_factories++;
        }
    }

    if (total_factories < n * m) {
        printf("0\n%d\n", n * m - total_factories);
    } else {
        printf("1\n%d\n", min_factories);
    }

    return 0;
}