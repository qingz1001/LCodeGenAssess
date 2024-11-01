#include <stdio.h>
#include <stdlib.h>

#define MAXN 9

int grid[MAXN][MAXN];
int dp[MAXN][MAXN][MAXN][MAXN];

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    int N;
    scanf("%d", &N);

    int x, y, num;
    while (1) {
        scanf("%d %d %d", &x, &y, &num);
        if (x == 0 && y == 0 && num == 0) break;
        grid[x-1][y-1] = num;
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                for (int l = 0; l < N; l++) {
                    int val = grid[i][j] + (i != k || j != l ? grid[k][l] : 0);
                    dp[i][j][k][l] = max(dp[i][j][k][l], (i > 0 && k > 0 ? dp[i-1][j][k-1][l] : 0) + val);
                    dp[i][j][k][l] = max(dp[i][j][k][l], (i > 0 && l > 0 ? dp[i-1][j][k][l-1] : 0) + val);
                    dp[i][j][k][l] = max(dp[i][j][k][l], (j > 0 && k > 0 ? dp[i][j-1][k-1][l] : 0) + val);
                    dp[i][j][k][l] = max(dp[i][j][k][l], (j > 0 && l > 0 ? dp[i][j-1][k][l-1] : 0) + val);
                }
            }
        }
    }

    printf("%d\n", dp[N-1][N-1][N-1][N-1]);

    return 0;
}