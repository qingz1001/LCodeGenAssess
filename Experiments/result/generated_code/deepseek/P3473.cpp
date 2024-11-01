#include <stdio.h>
#include <string.h>

#define MAXN 105
#define MOD 1000000000

int n, m, k, x, y;
char grid[MAXN][MAXN];
int dp[MAXN][MAXN][4]; // dp[i][j][dir] represents the number of ways to reach (i, j) with direction dir

// Directions: 0 = North, 1 = East, 2 = South, 3 = West
int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};

int mod(int a, int b) {
    return (a % b + b) % b;
}

int main() {
    scanf("%d %d %d", &n, &m, &k);
    scanf("%d %d", &x, &y);
    for (int i = 1; i <= n; i++) {
        scanf("%s", grid[i] + 1);
    }

    // Initialize the starting point (n, 1) with direction North
    dp[n][1][0] = 1;

    for (int i = n; i >= 1; i--) {
        for (int j = 1; j <= m; j++) {
            if (grid[i][j] == '*') continue; // Skip police intersections
            for (int dir = 0; dir < 4; dir++) {
                if (dp[i][j][dir] > 0) {
                    // Move straight
                    int nx = i + dx[dir];
                    int ny = j + dy[dir];
                    if (nx >= 1 && nx <= n && ny >= 1 && ny <= m && grid[nx][ny] != '*') {
                        dp[nx][ny][dir] = mod(dp[nx][ny][dir] + dp[i][j][dir], k);
                    }
                    // Turn right
                    int ndir = (dir + 1) % 4;
                    nx = i + dx[ndir];
                    ny = j + dy[ndir];
                    if (nx >= 1 && nx <= n && ny >= 1 && ny <= m && grid[nx][ny] != '*') {
                        dp[nx][ny][ndir] = mod(dp[nx][ny][ndir] + dp[i][j][dir], k);
                    }
                }
            }
        }
    }

    // The result is the sum of all directions at the hideout (x, y)
    int result = 0;
    for (int dir = 0; dir < 4; dir++) {
        result = mod(result + dp[x][y][dir], k);
    }

    printf("%d\n", result);
    return 0;
}