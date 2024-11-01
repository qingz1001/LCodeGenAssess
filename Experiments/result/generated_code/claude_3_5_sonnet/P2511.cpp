#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 50001
#define MAXM 1001
#define MOD 10007

int n, m;
long long L[MAXN];
long long sum[MAXN];
long long dp[MAXN][MAXM];

int check(long long mid) {
    int cuts = 0, last = 0;
    for (int i = 1; i <= n; i++) {
        if (sum[i] - sum[last] > mid) {
            cuts++;
            last = i - 1;
        }
    }
    return cuts <= m;
}

long long binary_search() {
    long long left = 0, right = sum[n], mid;
    while (left < right) {
        mid = (left + right) / 2;
        if (check(mid)) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    return left;
}

int count_ways(long long max_len) {
    memset(dp, 0, sizeof(dp));
    dp[0][0] = 1;
    
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= m && j < i; j++) {
            long long segment = 0;
            for (int k = i; k >= 1 && segment <= max_len; k--) {
                segment += L[k];
                if (j > 0 && segment <= max_len) {
                    dp[i][j] = (dp[i][j] + dp[k-1][j-1]) % MOD;
                }
            }
            if (segment <= max_len) {
                dp[i][j] = (dp[i][j] + dp[i-1][j]) % MOD;
            }
        }
    }
    
    return dp[n][m];
}

int main() {
    scanf("%d %d", &n, &m);
    
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &L[i]);
        sum[i] = sum[i-1] + L[i];
    }
    
    long long max_len = binary_search();
    int ways = count_ways(max_len);
    
    printf("%lld %d\n", max_len, ways);
    
    return 0;
}