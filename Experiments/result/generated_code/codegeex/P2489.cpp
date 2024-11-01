#include <stdio.h>
#include <string.h>

#define MAXN 35
#define MAXK 6
#define MAXH 6
#define MAXS (1 << MAXK)

int m, n, k, H;
char maze[MAXN][MAXN];
int p[MAXS];
double dp[MAXN][MAXN][MAXS][MAXH];

double dfs(int x, int y, int state, int health) {
    if (health <= 0) return 0.0;
    if (maze[x][y] == '@') return 1.0;
    if (dp[x][y][state][health] >= 0.0) return dp[x][y][state][health];

    double result = 0.0;
    if (maze[x][y] == '.' || maze[x][y] == '$' || maze[x][y] == '@') {
        if (x > 0) result += dfs(x - 1, y, state, health);
        if (x < m - 1) result += dfs(x + 1, y, state, health);
        if (y > 0) result += dfs(x, y - 1, state, health);
        if (y < n - 1) result += dfs(x, y + 1, state, health);
    } else {
        int trap_index = maze[x][y] - 'A';
        for (int i = 0; i < (1 << k); ++i) {
            if (i & (1 << trap_index)) {
                result += dfs(x, y, state | i, health - 1) * p[i] / p[state];
            } else {
                result += dfs(x, y, state | i, health) * p[i] / p[state];
            }
        }
    }
    dp[x][y][state][health] = result;
    return result;
}

int main() {
    scanf("%d%d%d%d", &m, &n, &k, &H);
    for (int i = 0; i < m; ++i) {
        scanf("%s", maze[i]);
    }
    for (int i = 0; i < (1 << k); ++i) {
        scanf("%d", &p[i]);
    }

    memset(dp, -1, sizeof(dp));
    double result = dfs(0, 0, 0, H);
    printf("%.3f\n", result);
    return 0;
}