#include <stdio.h>
#include <stdlib.h>

#define MAX_N 2000
#define MAX_H 10000

int main() {
    int N, H, Delta;
    scanf("%d %d %d", &N, &H, &Delta);

    int trees[MAX_N][MAX_H + 1];
    for (int i = 0; i < N; ++i) {
        int N_i;
        scanf("%d", &N_i);
        for (int j = 0; j <= H; ++j) {
            trees[i][j] = 0;
        }
        for (int j = 0; j < N_i; ++j) {
            int T_ij;
            scanf("%d", &T_ij);
            trees[i][T_ij]++;
        }
    }

    int dp[MAX_N][H + 1];
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j <= H; ++j) {
            dp[i][j] = 0;
        }
    }

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j <= H; ++j) {
            if (trees[i][j] > 0) {
                dp[i][j] += trees[i][j];
                if (i > 0) {
                    for (int k = 0; k <= H - Delta; ++k) {
                        dp[i][j] = fmax(dp[i][j], dp[i - 1][k]);
                    }
                }
                for (int k = 1; k <= H - Delta; ++k) {
                    dp[i][j] = fmax(dp[i][j], dp[i][j - k]);
                }
            }
        }
    }

    int max_sen = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j <= H; ++j) {
            max_sen = fmax(max_sen, dp[i][j]);
        }
    }

    printf("%d\n", max_sen);

    return 0;
}