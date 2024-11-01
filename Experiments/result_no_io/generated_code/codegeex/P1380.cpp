#include <stdio.h>
#include <string.h>

int n, m, ans;
char s[10][10];

void dfs(int x, int y, int cnt) {
    if (x >= n || y >= m) {
        ans = cnt > ans ? cnt : ans;
        return;
    }
    if (s[x][y] == '1') return;
    int temp[5][5];
    memset(temp, 0, sizeof(temp));
    int dx[] = {-1, 0, 1, 0};
    int dy[] = {0, 1, 0, -1};
    for (int i = 0; i < 4; i++) {
        int xx = x + dx[i];
        int yy = y + dy[i];
        if (xx < 0 || xx >= n || yy < 0 || yy >= m || s[xx][yy] == '1') return;
        temp[xx][yy] = 1;
    }
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            s[i][j] += temp[i][j];
    dfs(x, y + 1, cnt + 1);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            s[i][j] -= temp[i][j];
    dfs(x + 1, y, cnt);
}

int main() {
    scanf("%d%d", &n, &m);
    dfs(0, 0, 0);
    printf("%d\n", ans);
    return 0;
}