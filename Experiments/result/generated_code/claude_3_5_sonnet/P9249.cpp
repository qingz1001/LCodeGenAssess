#include <stdio.h>
#include <string.h>

#define MOD 998244353
#define MAXN 64
#define MAXM 20000

long long A[MAXN][MAXN];
long long dp[2][MAXN][MAXN];
long long tmp[MAXN][MAXN];
int n, m;

void matrix_multiply(long long a[MAXN][MAXN], long long b[MAXN][MAXN], long long c[MAXN][MAXN]) {
    memset(tmp, 0, sizeof(tmp));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            for (int k = 0; k < n; k++)
                tmp[i][j] = (tmp[i][j] + a[i][k] * b[k][j]) % MOD;
    memcpy(c, tmp, sizeof(tmp));
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%lld", &A[i][j]);

    long long ans = 0;
    int cur = 0, nxt = 1;
    
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            dp[cur][i][j] = A[i][j];

    for (int step = 1; step <= m; step++) {
        memset(dp[nxt], 0, sizeof(dp[nxt]));
        matrix_multiply(dp[cur], A, dp[nxt]);
        
        for (int y = 0; y < n; y++) {
            long long sum = 0;
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    if ((i & j) == y)
                        sum = (sum + dp[nxt][i][j]) % MOD;
            ans ^= sum;
        }
        
        cur ^= 1;
        nxt ^= 1;
    }

    printf("%lld\n", ans);
    return 0;
}