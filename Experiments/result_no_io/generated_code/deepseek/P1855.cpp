#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100
#define MAX_M 200
#define MAX_T 200

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    int n, M, T;
    int m[MAX_N], t[MAX_N];
    int dp[MAX_M + 1][MAX_T + 1];

    scanf("%d %d %d", &n, &M, &T);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &m[i], &t[i]);
    }

    for (int i = 0; i <= M; i++) {
        for (int j = 0; j <= T; j++) {
            dp[i][j] = 0;
        }
    }

    for (int k = 0; k < n; k++) {
        for (int i = M; i >= m[k]; i--) {
            for (int j = T; j >= t[k]; j--) {
                dp[i][j] = max(dp[i][j], dp[i - m[k]][j - t[k]] + 1);
            }
        }
    }

    printf("%d\n", dp[M][T]);

    return 0;
}