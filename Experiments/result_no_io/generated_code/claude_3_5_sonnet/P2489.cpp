#include <stdio.h>
#include <string.h>
#include <math.h>

#define MAX_M 31
#define MAX_N 30
#define MAX_K 5
#define MAX_H 6
#define MAX_STATE (1 << MAX_K)

char map[MAX_M][MAX_N];
int m, n, k, H;
long long p[MAX_STATE];
double dp[MAX_M][MAX_N][MAX_H][MAX_STATE];
int vis[MAX_M][MAX_N][MAX_H][MAX_STATE];
int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};

double dfs(int x, int y, int h, int state) {
    if (h <= 0) return 0;
    if (map[x][y] == '@') return 1;
    if (vis[x][y][h][state]) return dp[x][y][h][state];
    
    vis[x][y][h][state] = 1;
    double &res = dp[x][y][h][state];
    res = 0;

    if (map[x][y] >= 'A' && map[x][y] <= 'Z') {
        int trap = map[x][y] - 'A';
        int mask = 1 << trap;
        long long sum_safe = 0, sum_danger = 0;
        
        for (int s = 0; s < (1 << k); s++) {
            if (s & mask) sum_danger += p[s];
            else sum_safe += p[s];
        }
        
        if (sum_safe > 0) res += (double)sum_safe / (sum_safe + sum_danger) * dfs(x, y, h, state & ~mask);
        if (sum_danger > 0) res += (double)sum_danger / (sum_safe + sum_danger) * dfs(x, y, h - 1, state | mask);
    } else {
        for (int d = 0; d < 4; d++) {
            int nx = x + dx[d], ny = y + dy[d];
            if (nx >= 0 && nx < m && ny >= 0 && ny < n && map[nx][ny] != '#') {
                res = fmax(res, dfs(nx, ny, h, state));
            }
        }
    }
    
    return res;
}

int main() {
    scanf("%d%d%d%d", &m, &n, &k, &H);
    for (int i = 0; i < m; i++) {
        scanf("%s", map[i]);
    }
    
    int start_x, start_y;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (map[i][j] == '$') {
                start_x = i;
                start_y = j;
            }
        }
    }
    
    for (int i = 0; i < (1 << k); i++) {
        scanf("%lld", &p[i]);
    }
    
    double ans = dfs(start_x, start_y, H, 0);
    printf("%.3f\n", ans);
    
    return 0;
}