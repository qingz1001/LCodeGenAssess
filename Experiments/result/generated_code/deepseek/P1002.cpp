#include <stdio.h>
#include <stdbool.h>

#define MAX 21

int dp[MAX][MAX];
bool is_controlled[MAX][MAX];

void mark_controlled_points(int x, int y) {
    int dx[] = {0, -2, -1, 1, 2, 2, 1, -1, -2};
    int dy[] = {0, 1, 2, 2, 1, -1, -2, -2, -1};
    for (int i = 0; i < 9; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx >= 0 && nx < MAX && ny >= 0 && ny < MAX) {
            is_controlled[nx][ny] = true;
        }
    }
}

int main() {
    int n, m, hx, hy;
    scanf("%d %d %d %d", &n, &m, &hx, &hy);

    mark_controlled_points(hx, hy);

    dp[0][0] = 1;
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            if (is_controlled[i][j]) continue;
            if (i > 0) dp[i][j] += dp[i-1][j];
            if (j > 0) dp[i][j] += dp[i][j-1];
        }
    }

    printf("%d\n", dp[n][m]);
    return 0;
}