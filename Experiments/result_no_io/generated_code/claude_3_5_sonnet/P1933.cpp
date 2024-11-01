#include <stdio.h>
#include <string.h>

#define MOD 11192869
#define MAXN 3
#define MAXM 50
#define MAXS (1 << 3)

int n, m;
int T[MAXN][MAXM];
int L[MAXN * MAXM];
int dp[MAXM][MAXN][MAXS][MAXS];

int main() {
    scanf("%d %d", &n, &m);
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &T[i][j]);
        }
    }
    
    for (int i = 0; i < n * m; i++) {
        scanf("%d", &L[i]);
    }
    
    memset(dp, 0, sizeof(dp));
    
    for (int j = 0; j < m; j++) {
        for (int i = 0; i < n; i++) {
            if (T[i][j] == L[0]) {
                if (j == 0 || j == m - 1 || i == 0 || i == n - 1) {
                    dp[0][i][1 << i][1 << i] = 1;
                }
            }
        }
    }
    
    for (int k = 1; k < n * m; k++) {
        for (int j = 0; j < m; j++) {
            for (int i = 0; i < n; i++) {
                if (T[i][j] != L[k]) continue;
                for (int mask1 = 0; mask1 < (1 << n); mask1++) {
                    for (int mask2 = 0; mask2 < (1 << n); mask2++) {
                        if (!(mask2 & (1 << i))) continue;
                        int prev_mask2 = mask2 ^ (1 << i);
                        if (i > 0 && (mask2 & (1 << (i - 1)))) {
                            dp[j][i][mask1][mask2] = (dp[j][i][mask1][mask2] + dp[j][i - 1][mask1][prev_mask2]) % MOD;
                        }
                        if (i < n - 1 && (mask2 & (1 << (i + 1)))) {
                            dp[j][i][mask1][mask2] = (dp[j][i][mask1][mask2] + dp[j][i + 1][mask1][prev_mask2]) % MOD;
                        }
                        if (j > 0) {
                            dp[j][i][mask1][mask2] = (dp[j][i][mask1][mask2] + dp[j - 1][i][prev_mask2][mask1]) % MOD;
                        }
                    }
                }
            }
        }
    }
    
    int result = 0;
    for (int i = 0; i < n; i++) {
        for (int mask1 = 0; mask1 < (1 << n); mask1++) {
            for (int mask2 = 0; mask2 < (1 << n); mask2++) {
                result = (result + dp[m - 1][i][mask1][mask2]) % MOD;
            }
        }
    }
    
    printf("%d\n", result);
    
    return 0;
}