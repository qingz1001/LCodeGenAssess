#include <stdio.h>
#include <stdlib.h>

#define MAX_M 10000
#define MOD 255

int dp[MAX_M + 1][MAX_M + 1];

int f(int x, int O, int S, int U) {
    return (O * x * x + S * x + U) % MOD;
}

int main() {
    int M, P, A, O, S, U;
    scanf("%d %d", &M, &P);
    scanf("%d", &A);
    scanf("%d", &O);
    scanf("%d", &S);
    scanf("%d", &U);

    for (int i = 0; i <= M; i++) {
        for (int j = 0; j <= M; j++) {
            dp[i][j] = 0;
        }
    }

    dp[0][0] = 1;

    for (int i = 1; i <= M; i++) {
        for (int j = 0; j <= M; j++) {
            for (int k = 0; k <= j; k++) {
                dp[i][j] = (dp[i][j] + dp[i - 1][j - k] * f(k, O, S, U)) % P;
            }
        }
    }

    int S = 0;
    for (int i = 0; i <= M; i++) {
        S = (S + dp[A][i]) % P;
    }

    printf("%d\n", S);

    return 0;
}