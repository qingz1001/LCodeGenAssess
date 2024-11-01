#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 200
#define MAXM 200

typedef struct {
    int score;
    char hasBullet;
} Brick;

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);

    Brick bricks[MAXN][MAXM];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d %c", &bricks[i][j].score, &bricks[i][j].hasBullet);
        }
    }

    int dp[MAXN+1][MAXM+1][MAXM+1];
    memset(dp, 0, sizeof(dp));

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            for (int bullets = 0; bullets <= k; bullets++) {
                dp[i][j][bullets] = dp[i-1][m][bullets];
                if (j > 0) {
                    dp[i][j][bullets] = max(dp[i][j][bullets], dp[i][j-1][bullets]);
                }
                if (bullets > 0) {
                    int newBullets = bullets;
                    if (bricks[i-1][j-1].hasBullet == 'Y') {
                        newBullets++;
                    }
                    dp[i][j][bullets] = max(dp[i][j][bullets], dp[i-1][m][bullets-1] + bricks[i-1][j-1].score);
                    if (j > 0) {
                        dp[i][j][bullets] = max(dp[i][j][bullets], dp[i][j-1][bullets-1] + bricks[i-1][j-1].score);
                    }
                }
            }
        }
    }

    printf("%d\n", dp[n][m][k]);
    return 0;
}