#include <stdio.h>
#include <string.h>

int n, m, c1, c2;
int map[105][105], visited[105], min = 999;

void dfs(int v, int cnt) {
    if (v == c2) {
        if (cnt < min) min = cnt;
        return;
    }
    for (int i = 1; i <= n; i++) {
        if (map[v][i] && !visited[i]) {
            visited[i] = 1;
            dfs(i, cnt + 1);
            visited[i] = 0;
        }
    }
}

int main() {
    scanf("%d%d%d%d", &n, &m, &c1, &c2);
    for (int i = 0; i < m; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        map[x][y] = map[y][x] = 1;
    }
    visited[c1] = 1;
    dfs(c1, 0);
    printf("%d\n", min);
    return 0;
}