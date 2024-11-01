#include <stdio.h>
#include <string.h>

#define MOD 1000000007
#define MAX_N 1000001

long long dp[MAX_N];

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    memset(dp, 0, sizeof(dp));
    dp[0] = 1;

    for (int i = 0; i < M; i++) {
        int C;
        scanf("%d", &C);

        for (int j = N; j >= C + 1; j--) {
            dp[j] = (dp[j] + dp[j - C - 1]) % MOD;
        }
    }

    printf("%lld\n", dp[N]);

    return 0;
}