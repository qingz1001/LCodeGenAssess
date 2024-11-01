#include <stdio.h>
#include <stdlib.h>

#define MAX_N 350
#define MAX_M 120

int n, m;
int board[MAX_N];
int cards[MAX_M];

int dp[MAX_N][MAX_M + 1][5];

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%d", &board[i]);
    }
    for (int i = 0; i < m; i++) {
        scanf("%d", &cards[i]);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= m; j++) {
            for (int k = 0; k < 5; k++) {
                dp[i][j][k] = -1;
            }
        }
    }

    dp[0][0][0] = board[0];

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j <= m; j++) {
            for (int k = 0; k < 5; k++) {
                if (dp[i][j][k] != -1) {
                    for (int l = 0; l < m; l++) {
                        if (j & (1 << l)) continue;
                        int next_pos = i + cards[l];
                        if (next_pos >= n) break;
                        dp[next_pos][j | (1 << l)][l + 1] = max(dp[next_pos][j | (1 << l)][l + 1], dp[i][j][k] + board[next_pos]);
                    }
                }
            }
        }
    }

    int result = -1;
    for (int j = 0; j <= m; j++) {
        for (int k = 0; k < 5; k++) {
            result = max(result, dp[n - 1][j][k]);
        }
    }

    printf("%d\n", result);

    return 0;
}