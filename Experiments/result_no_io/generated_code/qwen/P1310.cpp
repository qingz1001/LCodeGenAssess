#include <stdio.h>
#include <stdlib.h>

#define MOD 10007

int dp[100001][2];

int main() {
    int L;
    scanf("%d", &L);
    char expression[L + 1];
    scanf("%s", expression);

    // Initialize the DP table
    for (int i = 0; i <= L; i++) {
        dp[i][0] = 0;
        dp[i][1] = 0;
    }

    // Base case: if there's only one operator and no parentheses
    if (L == 0) {
        dp[0][0] = 1;
        dp[0][1] = 1;
    } else {
        dp[0][0] = 1;
        dp[0][1] = 1;
        for (int i = 1; i <= L; i++) {
            if (expression[i - 1] == '*') {
                dp[i][0] = (dp[i - 1][0] * dp[i - 1][0]) % MOD;
                dp[i][1] = ((dp[i - 1][0] * dp[i - 1][1]) % MOD + (dp[i - 1][1] * dp[i - 1][0]) % MOD + (dp[i - 1][1] * dp[i - 1][1]) % MOD) % MOD;
            } else {
                dp[i][0] = ((dp[i - 1][0] * dp[i - 1][0]) % MOD + (dp[i - 1][0] * dp[i - 1][1]) % MOD + (dp[i - 1][1] * dp[i - 1][0]) % MOD) % MOD;
                dp[i][1] = (dp[i - 1][1] * dp[i - 1][1]) % MOD;
            }
        }
    }

    printf("%d\n", dp[L][0]);
    return 0;
}