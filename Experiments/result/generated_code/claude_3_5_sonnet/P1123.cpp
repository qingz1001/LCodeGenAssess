#include <stdio.h>
#include <string.h>

#define MAX_N 6
#define MAX_M 6

int N, M;
int matrix[MAX_N][MAX_M];
int dp[MAX_N][MAX_M][1 << MAX_M];

int max(int a, int b) {
    return a > b ? a : b;
}

int solve() {
    memset(dp, 0, sizeof(dp));

    for (int i = 0; i < N; i++) {
        for (int state = 0; state < (1 << M); state++) {
            if (i == 0) {
                for (int j = 0; j < M; j++) {
                    if ((state & (1 << j)) && !(state & (1 << (j-1))) && !(state & (1 << (j+1)))) {
                        dp[i][j][state] = matrix[i][j];
                    }
                }
            } else {
                for (int j = 0; j < M; j++) {
                    if (state & (1 << j)) {
                        if (j > 0 && (state & (1 << (j-1)))) continue;
                        if (j < M-1 && (state & (1 << (j+1)))) continue;

                        for (int prev_state = 0; prev_state < (1 << M); prev_state++) {
                            if ((prev_state & (1 << j)) || 
                                (j > 0 && (prev_state & (1 << (j-1)))) || 
                                (j < M-1 && (prev_state & (1 << (j+1))))) {
                                continue;
                            }

                            int max_prev = 0;
                            for (int k = 0; k < M; k++) {
                                max_prev = max(max_prev, dp[i-1][k][prev_state]);
                            }

                            dp[i][j][state] = max(dp[i][j][state], max_prev + matrix[i][j]);
                        }
                    }
                }
            }
        }
    }

    int result = 0;
    for (int j = 0; j < M; j++) {
        for (int state = 0; state < (1 << M); state++) {
            result = max(result, dp[N-1][j][state]);
        }
    }

    return result;
}

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        scanf("%d %d", &N, &M);

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                scanf("%d", &matrix[i][j]);
            }
        }

        printf("%d\n", solve());
    }

    return 0;
}