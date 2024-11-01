#include <stdio.h>
#include <string.h>

#define MAX_M 10001
#define MOD 255

int M, P, A, O, S, U;
int dp[MAX_M][MAX_M];

int f(int x) {
    return (O * x * x + S * x + U) % P;
}

int main() {
    scanf("%d %d", &M, &P);
    scanf("%d", &A);
    scanf("%d", &O);
    scanf("%d", &S);
    scanf("%d", &U);

    memset(dp, 0, sizeof(dp));
    dp[0][0] = 1;

    for (int i = 1; i <= A; i++) {
        for (int j = 0; j <= M; j++) {
            for (int k = 0; k <= j; k++) {
                dp[i][j] = (dp[i][j] + dp[i-1][j-k] * f(k)) % P;
            }
        }
    }

    int S = 0;
    for (int j = 0; j <= M; j++) {
        S = (S + dp[A][j]) % P;
    }

    printf("%d\n", S);
    return 0;
}