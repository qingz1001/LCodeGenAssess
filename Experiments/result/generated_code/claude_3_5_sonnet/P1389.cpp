#include <stdio.h>
#include <string.h>

#define MAX_N 150
#define MAX_VAL 1000000000
#define INF 0x3f3f3f3f

int N, V[MAX_N], A[MAX_N];
int dp[MAX_N][MAX_N][15][15];

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &V[i]);
    }
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }

    memset(dp, -INF, sizeof(dp));

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < 15; j++) {
            dp[i][i][j][j] = 0;
        }
    }

    for (int len = 2; len <= N; len++) {
        for (int i = 0; i + len - 1 < N; i++) {
            int j = i + len - 1;
            for (int l = 0; l < 15; l++) {
                for (int r = 0; r < 15; r++) {
                    for (int k = i; k < j; k++) {
                        for (int m = 0; m < 15; m++) {
                            if (dp[i][k][l][m] > -INF && dp[k+1][j][m][r] > -INF) {
                                dp[i][j][l][r] = max(dp[i][j][l][r], dp[i][k][l][m] + dp[k+1][j][m][r]);
                            }
                        }
                    }
                    if (A[i] == A[j] || abs(A[i] - A[j]) == 1) {
                        int score = V[j - i + 1];
                        if (l == r && (l == 0 || l == 14 || A[i-1] - A[i] != A[j] - A[i])) {
                            dp[i][j][l][r] = max(dp[i][j][l][r], score);
                        }
                    }
                }
            }
        }
    }

    int result = 0;
    for (int l = 0; l < 15; l++) {
        for (int r = 0; r < 15; r++) {
            result = max(result, dp[0][N-1][l][r]);
        }
    }

    printf("%d\n", result);

    return 0;
}