#include <stdio.h>
#include <string.h>

int n, m, x, y, i, j, k, sum;
int a[1001][1001];
char ch[1001][1001];
int vis[1001][1001];
int dir[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

void dfs(int x, int y) {
    int nx, ny;
    for (k = 0; k < 4; k++) {
        nx = x + dir[k][0];
        ny = y + dir[k][1];
        if (nx >= 1 && nx <= n && ny >= 1 && ny <= n && !vis[nx][ny] && ((ch[x][y] == '0' && ch[nx][ny] == '1') || (ch[x][y] == '1' && ch[nx][ny] == '0'))) {
            vis[nx][ny] = 1;
            sum++;
            dfs(nx, ny);
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; i++) {
        scanf("%s", ch[i] + 1);
        for (j = 1; j <= n; j++) {
            a[i][j] = ch[i][j] - '0';
        }
    }
    for (i = 0; i < m; i++) {
        scanf("%d%d", &x, &y);
        if (!vis[x][y]) {
            vis[x][y] = 1;
            sum = 1;
            dfs(x, y);
        }
        printf("%d\n", sum);
    }
    return 0;
}