#include <stdio.h>

#define MAXN 40
#define MAXM 65

int S_r, S_b, S_g, m, P;
int perm[MAXM][MAXN];
int fact[MAXN];
int inv[MAXN];
int dp[MAXN][MAXN][MAXN];
int ans;

int mod(int x) {
    return x >= P ? x - P : x;
}

int modinv(int a, int p) {
    int res = 1, b = p - 2;
    while (b) {
        if (b & 1) res = (long long)res * a % p;
        a = (long long)a * a % p;
        b >>= 1;
    }
    return res;
}

void init() {
    fact[0] = inv[0] = 1;
    for (int i = 1; i < MAXN; i++) {
        fact[i] = (long long)fact[i - 1] * i % P;
        inv[i] = modinv(fact[i], P);
    }
}

int main() {
    scanf("%d%d%d%d%d", &S_r, &S_b, &S_g, &m, &P);
    init();

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < S_r + S_b + S_g; j++) {
            scanf("%d", &perm[i][j]);
            perm[i][j]--;
        }
    }

    dp[0][0][0] = 1;
    for (int i = 0; i <= S_r; i++) {
        for (int j = 0; j <= S_b; j++) {
            for (int k = 0; k <= S_g; k++) {
                if (dp[i][j][k]) {
                    for (int t = 0; t < m; t++) {
                        int ni = mod(i + perm[t][S_r]);
                        int nj = mod(j + perm[t][S_r + S_b]);
                        int nk = mod(k + perm[t][S_r + S_b + S_g]);
                        dp[ni][nj][nk] = mod(dp[ni][nj][nk] + dp[i][j][k]);
                    }
                }
            }
        }
    }

    for (int i = S_r; i <= S_r; i++) {
        for (int j = S_b; j <= S_b; j++) {
            for (int k = S_g; k <= S_g; k++) {
                ans = mod(ans + dp[i][j][k] * fact[i] % P * fact[j] % P * fact[k] % P);
            }
        }
    }

    printf("%d\n", ans);
    return 0;
}