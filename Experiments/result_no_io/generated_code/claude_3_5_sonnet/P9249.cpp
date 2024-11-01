#include <stdio.h>
#include <string.h>

#define MOD 998244353
#define MAXN 64
#define MAXM 20000

typedef long long ll;

int n, m;
ll A[MAXN][MAXN];
ll dp[MAXM+1][MAXN][MAXN];
ll sum[MAXM+1][MAXN];

void matrix_mul(ll a[MAXN][MAXN], ll b[MAXN][MAXN], ll c[MAXN][MAXN]) {
    ll temp[MAXN][MAXN] = {0};
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                temp[i][j] = (temp[i][j] + a[i][k] * b[k][j]) % MOD;
            }
        }
    }
    memcpy(c, temp, sizeof(temp));
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%lld", &A[i][j]);
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dp[1][i][j] = A[i][j];
            sum[1][i & j] = (sum[1][i & j] + A[i][j]) % MOD;
        }
    }

    for (int k = 2; k <= m; k++) {
        matrix_mul(dp[k-1], A, dp[k]);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                sum[k][i & j] = (sum[k][i & j] + dp[k][i][j]) % MOD;
            }
        }
    }

    ll result = 0;
    for (int x = 1; x <= m; x++) {
        for (int y = 0; y < n; y++) {
            result ^= sum[x][y];
        }
    }

    printf("%lld\n", result);

    return 0;
}