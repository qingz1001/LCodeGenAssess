#include <stdio.h>
#include <string.h>

#define MOD 1000000007
#define MAXM 6
#define MAXS (1 << MAXM)

typedef long long ll;

ll n, m, k;
ll dp[MAXS][MAXM];
ll mat[MAXS][MAXS], res[MAXS][MAXS], tmp[MAXS][MAXS];
int S;

int count_ones(int x) {
    int cnt = 0;
    while (x) {
        cnt += x & 1;
        x >>= 1;
    }
    return cnt;
}

void matrix_mul(ll a[MAXS][MAXS], ll b[MAXS][MAXS], ll c[MAXS][MAXS]) {
    memset(tmp, 0, sizeof(tmp));
    for (int i = 0; i < S; i++)
        for (int j = 0; j < S; j++)
            for (int k = 0; k < S; k++)
                tmp[i][j] = (tmp[i][j] + a[i][k] * b[k][j]) % MOD;
    memcpy(c, tmp, sizeof(tmp));
}

void matrix_pow(ll a[MAXS][MAXS], ll n) {
    memset(res, 0, sizeof(res));
    for (int i = 0; i < S; i++)
        res[i][i] = 1;
    while (n) {
        if (n & 1)
            matrix_mul(res, a, res);
        matrix_mul(a, a, a);
        n >>= 1;
    }
}

int main() {
    scanf("%lld%lld%lld", &n, &m, &k);
    S = 1 << m;

    for (int s = 0; s < S; s++) {
        if (count_ones(s) <= k) {
            dp[s][m-1] = 1;
            for (int i = m-2; i >= 0; i--)
                dp[s][i] = dp[s][i+1] * (2 - ((s >> i) & 1));
        }
    }

    for (int s = 0; s < S; s++)
        for (int t = 0; t < S; t++)
            if ((s & ((1 << (m-1)) - 1)) == (t >> 1))
                mat[s][t] = dp[t][0];

    matrix_pow(mat, n);

    ll ans = 0;
    for (int s = 0; s < S; s++)
        if (count_ones(s) <= k)
            ans = (ans + res[0][s]) % MOD;

    printf("%lld\n", ans);
    return 0;
}