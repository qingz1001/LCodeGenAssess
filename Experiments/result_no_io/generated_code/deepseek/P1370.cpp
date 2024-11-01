#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MOD 998244353
#define MAXN 100005

typedef long long ll;

ll dp[MAXN][26];
ll sum[MAXN];

ll mod(ll x) {
    return (x % MOD + MOD) % MOD;
}

int main() {
    int n;
    scanf("%d", &n);
    int *a = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    memset(dp, 0, sizeof(dp));
    memset(sum, 0, sizeof(sum));

    for (int i = 0; i < n; i++) {
        int c = a[i];
        for (int j = i; j >= 0; j--) {
            if (j == 0) {
                dp[j][c] = 1;
            } else {
                dp[j][c] = mod(sum[j - 1] - dp[j - 1][c]);
            }
            sum[j] = mod(sum[j] + dp[j][c]);
        }
    }

    ll result = 0;
    for (int i = 0; i < n; i++) {
        result = mod(result + sum[i]);
    }

    printf("%lld\n", result);

    free(a);
    return 0;
}