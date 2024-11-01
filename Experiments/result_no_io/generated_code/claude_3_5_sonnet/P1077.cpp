#include <stdio.h>

#define MOD 1000007
#define MAXN 101
#define MAXM 101

int n, m;
int a[MAXN];
int dp[MAXN][MAXM];

int main() {
    scanf("%d %d", &n, &m);
    
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    
    dp[0][0] = 1;
    
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            for (int k = 0; k <= a[i] && k <= j; k++) {
                dp[i][j] = (dp[i][j] + dp[i-1][j-k]) % MOD;
            }
        }
    }
    
    printf("%d\n", dp[n][m]);
    
    return 0;
}