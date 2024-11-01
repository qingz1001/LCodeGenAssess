#include <stdio.h>
#include <stdlib.h>

#define MAXN 200
#define MAXM 200

typedef struct {
    int score;
    int bullet; // 1 if bullet is rewarded, 0 otherwise
} Brick;

Brick bricks[MAXN][MAXM];
int dp[MAXN][MAXM][MAXM]; // dp[i][j][k] means the max score with i bullets left, j rows processed, k columns processed

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &bricks[i][j].score);
            char c;
            scanf(" %c", &c);
            bricks[i][j].bullet = (c == 'Y') ? 1 : 0;
        }
    }

    for (int i = 0; i <= k; i++) {
        for (int j = 0; j <= n; j++) {
            for (int l = 0; l <= m; l++) {
                dp[i][j][l] = 0;
            }
        }
    }

    for (int i = 1; i <= k; i++) {
        for (int j = 0; j < n; j++) {
            for (int l = 0; l < m; l++) {
                int score = bricks[j][l].score;
                int bullet = bricks[j][l].bullet;

                // Option 1: Use the bullet on this brick
                if (i > 0) {
                    dp[i][j][l] = max(dp[i][j][l], dp[i - 1][j][l] + score);
                }

                // Option 2: Skip this brick and move to the next one
                if (l > 0) {
                    dp[i][j][l] = max(dp[i][j][l], dp[i][j][l - 1]);
                }

                // Option 3: Use the bullet on this brick and get a reward bullet
                if (i > 0 && bullet) {
                    dp[i][j][l] = max(dp[i][j][l], dp[i - 1][j][l] + score + dp[i - 1][j][l]);
                }
            }
        }
    }

    printf("%d\n", dp[k][n - 1][m - 1]);

    return 0;
}