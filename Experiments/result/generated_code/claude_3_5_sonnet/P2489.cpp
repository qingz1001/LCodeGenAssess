#include <stdio.h>
#include <string.h>
#include <math.h>

#define MAX_M 30
#define MAX_N 29
#define MAX_K 5
#define MAX_H 5
#define MAX_STATES (1 << MAX_K)

int m, n, k, H;
char maze[MAX_M][MAX_N+1];
long long p[MAX_STATES];
double dp[MAX_M][MAX_N][MAX_H+1][MAX_STATES];
int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};

double dfs(int x, int y, int h, int state) {
    if (h <= 0) return 0;
    if (maze[x][y] == '@') return 1;
    if (dp[x][y][h][state] >= 0) return dp[x][y][h][state];

    double res = 0;
    for (int d = 0; d < 4; d++) {
        int nx = x + dx[d], ny = y + dy[d];
        if (nx < 0 || nx >= m || ny < 0 || ny >= n || maze[nx][ny] == '#') continue;

        if (maze[nx][ny] >= 'A' && maze[nx][ny] <= 'Z') {
            int trap = maze[nx][ny] - 'A';
            int harmful = (state >> trap) & 1;
            res = fmax(res, dfs(nx, ny, h - harmful, state));
        } else {
            res = fmax(res, dfs(nx, ny, h, state));
        }
    }

    return dp[x][y][h][state] = res;
}

int main() {
    scanf("%d %d %d %d", &m, &n, &k, &H);
    
    for (int i = 0; i < m; i++) {
        scanf("%s", maze[i]);
    }

    long long sum = 0;
    for (int i = 0; i < (1 << k); i++) {
        scanf("%lld", &p[i]);
        sum += p[i];
    }

    memset(dp, -1, sizeof(dp));

    int sx = -1, sy = -1;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (maze[i][j] == '$') {
                sx = i;
                sy = j;
                break;
            }
        }
        if (sx != -1) break;
    }

    double ans = 0;
    for (int state = 0; state < (1 << k); state++) {
        ans += dfs(sx, sy, H, state) * p[state];
    }

    printf("%.3f\n", ans / sum);

    return 0;
}