#include <stdio.h>
#include <stdlib.h>

#define MAXN 1000
#define MAXM 100000

int n, m;
char maze[MAXN][MAXN];
int visited[MAXN][MAXN];

int dx[] = {0, 0, -1, 1};
int dy[] = {-1, 1, 0, 0};

void dfs(int x, int y) {
    if (x < 0 || x >= n || y < 0 || y >= n || visited[x][y] || maze[x][y] == '0') return;
    visited[x][y] = 1;
    for (int i = 0; i < 4; i++) {
        dfs(x + dx[i], y + dy[i]);
    }
}

int countReachableCells(int x, int y) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            visited[i][j] = 0;
        }
    }
    dfs(x - 1, y - 1);
    int count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (visited[i][j]) count++;
        }
    }
    return count;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%s", maze[i]);
    }
    for (int i = 0; i < m; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        printf("%d\n", countReachableCells(x, y));
    }
    return 0;
}