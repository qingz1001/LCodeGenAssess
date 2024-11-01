#include <stdio.h>
#include <string.h>

#define MOD 998244353

int n, m, c, op;
char grid[10][10];
int dp[10][10][4][4][2][2];
int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};

int dfs(int x, int y, int dir, int last_dir, int start, int visited) {
    if (x < 0 || x >= n || y < 0 || y >= m || grid[x][y] == '#') {
        return 0;
    }
    if (dp[x][y][dir][last_dir][start][visited] != -1) {
        return dp[x][y][dir][last_dir][start][visited];
    }
    
    int ret = 0;
    if (visited) {
        ret = c; // 可以选择任意颜色
    } else {
        ret = 1; // 必须结束本次画线
    }
    
    for (int i = 0; i < 4; i++) {
        if (i == dir || i == last_dir) {
            continue; // 不能画与当前方向或上一次方向相同的线
        }
        int nx = x + dx[i];
        int ny = y + dy[i];
        ret = (ret + dfs(nx, ny, i, dir, 0, visited)) % MOD;
    }
    
    dp[x][y][dir][last_dir][start][visited] = ret;
    return ret;
}

int main() {
    scanf("%d%d%d%d", &n, &m, &c, &op);
    for (int i = 0; i < n; i++) {
        scanf("%s", grid[i]);
    }
    
    memset(dp, -1, sizeof(dp));
    int ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == '.') {
                ans = (ans + dfs(i, j, -1, -1, 1, 1)) % MOD;
            }
        }
    }
    
    printf("%d\n", ans);
    return 0;
}