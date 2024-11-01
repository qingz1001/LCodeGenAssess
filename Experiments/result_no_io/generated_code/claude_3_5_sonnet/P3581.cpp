#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_N 1000001
#define MOD 1000000007

int n, k, p;
bool dislike[MAX_N][4];
long long dp[MAX_N][4];

int main() {
    scanf("%d %d %d", &n, &k, &p);

    memset(dislike, 0, sizeof(dislike));
    for (int i = 0; i < k; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        a--; b--;
        dislike[a][b - a + 3 & 3] = true;
    }

    memset(dp, 0, sizeof(dp));
    dp[n-1][0] = 1;

    for (int i = n-2; i >= 0; i--) {
        for (int j = 0; j <= p; j++) {
            for (int k = 0; k <= p; k++) {
                if (dislike[i][(k-j+4)%4]) continue;
                dp[i][j] = (dp[i][j] + dp[i+1][k]) % MOD;
            }
        }
    }

    long long ans = 0;
    for (int j = 0; j <= p; j++) {
        ans = (ans + dp[0][j]) % MOD;
    }

    printf("%lld\n", ans);

    return 0;
}