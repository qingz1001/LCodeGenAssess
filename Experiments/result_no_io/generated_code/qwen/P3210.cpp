#include <stdio.h>
#include <stdlib.h>

#define MAXN 1000005

int dp[MAXN][2];

int main() {
    int N;
    scanf("%d", &N);
    int stones[N];
    for (int i = 0; i < N; ++i) {
        scanf("%d", &stones[i]);
    }

    // Initialize the DP table
    dp[0][0] = 0;
    dp[0][1] = stones[0];
    for (int i = 1; i < N; ++i) {
        if (stones[i] == 0) {
            dp[i][0] = dp[i-1][0];
            dp[i][1] = dp[i-1][1];
        } else {
            dp[i][0] = dp[i-1][1];
            dp[i][1] = dp[i-1][0] + stones[i];
        }
    }

    printf("%d %d\n", dp[N-1][0], dp[N-1][1]);
    return 0;
}