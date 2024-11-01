#include <stdio.h>
#include <stdbool.h>

#define MAX 21

int n, m, cx, cy;
long long dp[MAX][MAX];
bool control[MAX][MAX];

void markControlPoints(int x, int y) {
    int dx[] = {0, 0, 1, -1, 1, -1, 2, -2};
    int dy[] = {1, -1, 0, 0, 2, -2, 1, -1};
    control[x][y] = true;
    for (int i = 0; i < 8; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx >= 0 && nx <= n && ny >= 0 && ny <= m) {
            control[nx][ny] = true;
        }
    }
}

int main() {
    scanf("%d %d %d %d", &n, &m, &cx, &cy);
    
    markControlPoints(cx, cy);
    
    dp[0][0] = 1;
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            if (control[i][j]) {
                dp[i][j] = 0;
            } else {
                if (i > 0) dp[i][j] += dp[i-1][j];
                if (j > 0) dp[i][j] += dp[i][j-1];
            }
        }
    }
    
    printf("%lld\n", dp[n][m]);
    return 0;
}