#include <stdio.h>
#include <stdlib.h>

#define MAXN 150

int main() {
    int N;
    scanf("%d", &N);
    int V[MAXN], A[MAXN];
    for (int i = 0; i < N; i++) {
        scanf("%d", &V[i]);
    }
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }

    int dp[MAXN][MAXN];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            dp[i][j] = 0;
        }
    }

    for (int len = 1; len <= N; len++) {
        for (int i = 0; i + len - 1 < N; i++) {
            int j = i + len - 1;
            if (len == 1) {
                dp[i][j] = V[j];
            } else {
                for (int k = i; k < j; k++) {
                    if ((k == i && A[k] == A[k + 1] - 1) || (k == j - 1 && A[k] == A[k - 1] + 1)) {
                        dp[i][j] = fmax(dp[i][j], dp[i][k] + dp[k + 1][j]);
                    }
                }
            }
        }
    }

    printf("%d\n", dp[0][N - 1]);

    return 0;
}