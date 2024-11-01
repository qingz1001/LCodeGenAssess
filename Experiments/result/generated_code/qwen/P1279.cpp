#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 2005

int min(int a, int b) {
    return (a < b) ? a : b;
}

int distance(char *A, char *B, int K) {
    int lenA = strlen(A);
    int lenB = strlen(B);
    int dp[MAX_LEN][MAX_LEN];

    for (int i = 0; i <= lenA; i++) {
        for (int j = 0; j <= lenB; j++) {
            if (i == 0 && j == 0) {
                dp[i][j] = 0;
            } else if (i == 0) {
                dp[i][j] = dp[i][j - 1] + K;
            } else if (j == 0) {
                dp[i][j] = dp[i - 1][j] + K;
            } else {
                if (A[i - 1] == B[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                } else {
                    dp[i][j] = dp[i - 1][j - 1] + abs((int)(A[i - 1] - B[j - 1]));
                }
            }
        }
    }

    return dp[lenA][lenB];
}

int main() {
    char A[MAX_LEN], B[MAX_LEN];
    int K;

    scanf("%s", A);
    scanf("%s", B);
    scanf("%d", &K);

    printf("%d\n", distance(A, B, K));

    return 0;
}