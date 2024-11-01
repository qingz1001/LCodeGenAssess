#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 2000

int min(int a, int b) {
    return a < b ? a : b;
}

int distance(char *A, char *B, int K) {
    int lenA = strlen(A);
    int lenB = strlen(B);
    int dp[MAX_LEN + 1][MAX_LEN + 1];

    for (int i = 0; i <= lenA; i++) {
        for (int j = 0; j <= lenB; j++) {
            if (i == 0) {
                dp[i][j] = j * K;
            } else if (j == 0) {
                dp[i][j] = i * K;
            } else {
                int cost = abs(A[i - 1] - B[j - 1]);
                dp[i][j] = min(dp[i - 1][j - 1] + cost, min(dp[i - 1][j] + K, dp[i][j - 1] + K));
            }
        }
    }

    return dp[lenA][lenB];
}

int main() {
    char A[MAX_LEN + 1], B[MAX_LEN + 1];
    int K;

    scanf("%s", A);
    scanf("%s", B);
    scanf("%d", &K);

    int result = distance(A, B, K);
    printf("%d\n", result);

    return 0;
}