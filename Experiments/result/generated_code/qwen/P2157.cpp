#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000
#define MAX_C 5

int min(int a, int b) {
    return (a < b) ? a : b;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int main() {
    int C, N;
    scanf("%d", &C);
    while (C--) {
        scanf("%d", &N);
        int T[MAX_N], B[MAX_N];
        for (int i = 0; i < N; i++) {
            scanf("%d %d", &T[i], &B[i]);
        }

        int dp[N][MAX_B + 1];
        for (int i = 0; i < N; i++) {
            for (int j = 0; j <= MAX_B; j++) {
                dp[i][j] = 0;
            }
        }

        dp[0][0] = 0;
        for (int i = 1; i < N; i++) {
            for (int j = 0; j <= MAX_B; j++) {
                dp[i][j] = dp[i - 1][j] + (T[i] | T[i - 1]) - (T[i] & T[i - 1]);
                if (j >= 1) {
                    dp[i][j] = min(dp[i][j], dp[i - 1][j - 1] + (T[i] | T[i - 1]) - (T[i] & T[i - 1]));
                }
            }
        }

        printf("%d\n", dp[N - 1][B[N - 1]]);
    }
    return 0;
}