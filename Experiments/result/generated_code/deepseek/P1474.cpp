#include <stdio.h>
#include <stdlib.h>

#define MAX_N 10000
#define MAX_V 25

long long dp[MAX_N + 1];

int main() {
    int V, N;
    int coins[MAX_V];

    scanf("%d %d", &V, &N);
    for (int i = 0; i < V; i++) {
        scanf("%d", &coins[i]);
    }

    dp[0] = 1;
    for (int i = 0; i < V; i++) {
        for (int j = coins[i]; j <= N; j++) {
            dp[j] += dp[j - coins[i]];
        }
    }

    printf("%lld\n", dp[N]);

    return 0;
}