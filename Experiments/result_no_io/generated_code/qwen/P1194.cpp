#include <stdio.h>
#include <stdlib.h>

#define MAX_B 50000
#define MAX_A 1000

int min(int a, int b) {
    return (a < b) ? a : b;
}

int main() {
    int A, B;
    scanf("%d %d", &A, &B);

    int K[MAX_B][MAX_B];
    for (int i = 0; i < B; i++) {
        for (int j = 0; j < B; j++) {
            scanf("%d", &K[i][j]);
        }
    }

    int dp[B];
    for (int i = 0; i < B; i++) {
        dp[i] = A + K[0][i];
    }

    for (int i = 1; i < B; i++) {
        for (int j = 0; j < i; j++) {
            dp[j] = min(dp[j], dp[i] - K[i][j] + A);
        }
    }

    printf("%d\n", dp[0]);

    return 0;
}