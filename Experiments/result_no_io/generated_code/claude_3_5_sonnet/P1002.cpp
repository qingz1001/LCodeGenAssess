#include <stdio.h>

#define MAX_N 21
#define MAX_M 21

long long dp[MAX_N][MAX_M];
int horse_x, horse_y;
int n, m;

int is_controlled(int x, int y) {
    int dx[] = {-2, -1, 1, 2, 2, 1, -1, -2};
    int dy[] = {1, 2, 2, 1, -1, -2, -2, -1};
    
    if (x == horse_x && y == horse_y) return 1;
    
    for (int i = 0; i < 8; i++) {
        int nx = horse_x + dx[i];
        int ny = horse_y + dy[i];
        if (nx == x && ny == y) return 1;
    }
    
    return 0;
}

int main() {
    scanf("%d %d %d %d", &n, &m, &horse_x, &horse_y);
    
    dp[0][0] = 1;
    
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            if (is_controlled(i, j)) {
                dp[i][j] = 0;
                continue;
            }
            
            if (i > 0) dp[i][j] += dp[i-1][j];
            if (j > 0) dp[i][j] += dp[i][j-1];
        }
    }
    
    printf("%lld\n", dp[n][m]);
    
    return 0;
}