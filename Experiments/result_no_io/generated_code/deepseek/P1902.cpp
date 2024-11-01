#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 1000
#define MAXM 1000

int n, m;
int p[MAXN][MAXM];
int visited[MAXN][MAXM];

int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int dfs(int x, int y, int max_damage) {
    if (x == n - 1) {
        return max_damage;
    }

    visited[x][y] = 1;
    int min_damage = INT_MAX;

    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];

        if (nx >= 0 && nx < n && ny >= 0 && ny < m && !visited[nx][ny]) {
            int new_damage = max(max_damage, p[nx][ny]);
            min_damage = min(min_damage, dfs(nx, ny, new_damage));
        }
    }

    visited[x][y] = 0;
    return min_damage;
}

int main() {
    scanf("%d %d", &n, &m);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &p[i][j]);
        }
    }

    int result = INT_MAX;

    for (int j = 0; j < m; j++) {
        result = min(result, dfs(0, j, 0));
    }

    printf("%d\n", result);

    return 0;
}