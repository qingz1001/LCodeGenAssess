#include <stdio.h>
#include <string.h>

int n, m, ans;
char a[35][35];
int l[35][35][35][35], cnt, f[35][35][35][35][35][35];

void dfs(int x, int y, int p) {
    if (x == n && y == m + 1) {
        ans++;
        return;
    }
    if (y == m + 1) x++, y = 1;
    if (a[x][y] == '#') {
        dfs(x, y + 1, p);
        return;
    }
    if (f[x][y][l[x][y][0]][l[x][y][1]][l[x][y][2]][l[x][y][3]] == cnt) return;
    f[x][y][l[x][y][0]][l[x][y][1]][l[x][y][2]][l[x][y][3]] = cnt;
    int i, j, k;
    for (i = 0; i < 4; i++) {
        int dx = x + p[i][0], dy = y + p[i][1];
        if (dx < 0 || dx >= n || dy < 0 || dy >= m || a[dx][dy] == '#') continue;
        for (j = 0; j < 4; j++) {
            int tx = dx + p[j][0], ty = dy + p[j][1];
            if (tx < 0 || tx >= n || ty < 0 || ty >= m || a[tx][ty] == '#') continue;
            for (k = 0; k < 4; k++) {
                int ex = tx + p[k][0], ey = ty + p[k][1];
                if (ex < 0 || ex >= n || ey < 0 || ey >= m || a[ex][ey] == '#') continue;
                if (l[dx][dy][j] != -1 || l[tx][ty][k] != -1 || l[ex][ey][i] != -1) continue;
                l[dx][dy][j] = i;
                l[tx][ty][k] = j;
                l[ex][ey][i] = k;
                dfs(x, y + 1, p);
                l[dx][dy][j] = -1;
                l[tx][ty][k] = -1;
                l[ex][ey][i] = -1;
            }
        }
    }
}

int main() {
    int i, j;
    scanf("%d%d", &n, &m);
    for (i = 0; i < n; i++) scanf("%s", a[i]);
    int p[4][2] = {{0, 1}, {1, 0}, {1, -1}, {-1, 1}};
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            if (a[i][j] == '.') {
                l[i][j][0] = l[i][j][1] = l[i][j][2] = l[i][j][3] = -1;
                dfs(i, j + 1, p);
            }
    printf("%d\n", ans);
    return 0;
}