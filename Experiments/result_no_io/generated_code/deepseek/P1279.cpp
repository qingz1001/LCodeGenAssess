#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 2000

int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    char A[MAX_LEN + 1], B[MAX_LEN + 1];
    int K;
    scanf("%s", A);
    scanf("%s", B);
    scanf("%d", &K);

    int lenA = strlen(A);
    int lenB = strlen(B);

    int dp[lenA + 1][lenB + 1];

    // Initialize the dp array
    for (int i = 0; i <= lenA; i++) {
        for (int j = 0; j <= lenB; j++) {
            dp[i][j] = 0;
        }
    }

    // Fill the dp array
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

    printf("%d\n", dp[lenA][lenB]);

    return 0;
}