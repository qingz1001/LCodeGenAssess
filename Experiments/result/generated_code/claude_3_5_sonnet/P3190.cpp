#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAX_N 100
#define MAX_M 6
#define MAX_STATE (1 << MAX_M)

int n, m;
int a[MAX_N][MAX_M];
int dp[MAX_N][MAX_M][MAX_STATE];

int max(int a, int b) {
    return a > b ? a : b;
}

int dfs(int x, int y, int state, int sx, int sy) {
    if (dp[x][y][state] != INT_MIN) {
        return dp[x][y][state];
    }
    
    int res = INT_MIN;
    
    // Check if we can return to the starting point
    if ((x == sx && y == sy) && (state != (1 << y)) && (__builtin_popcount(state) >= 4)) {
        res = 0;
    }
    
    // Try moving to adjacent cells
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};
    
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        
        if (nx >= 0 && nx < n && ny >= 0 && ny < m && !(state & (1 << ny))) {
            int new_state = state | (1 << ny);
            int sub_res = dfs(nx, ny, new_state, sx, sy);
            
            if (sub_res != INT_MIN) {
                res = max(res, sub_res + a[x][y]);
            }
        }
    }
    
    dp[x][y][state] = res;
    return res;
}

int main() {
    scanf("%d %d", &n, &m);
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &a[i][j]);
        }
    }
    
    int ans = INT_MIN;
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            memset(dp, 0xc0, sizeof(dp));  // Initialize dp with INT_MIN
            int res = dfs(i, j, 1 << j, i, j);
            ans = max(ans, res);
        }
    }
    
    printf("%d\n", ans);
    
    return 0;
}