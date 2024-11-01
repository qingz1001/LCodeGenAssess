#include <stdio.h>
#include <string.h>

#define MAXN 1005
#define EPS 1e-9

double dp[MAXN][MAXN];

double solve(int n, int m) {
    memset(dp, 0, sizeof(dp));
    
    for (int i = 1; i <= n; i++) {
        dp[1][i] = (i == 1) ? 1.0 : 0.0;
    }
    
    for (int i = 2; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            dp[i][j] += dp[i-1][j] * 0.5;  // 2,4,6
            if (j > 1) {
                dp[i][j] += dp[i-1][j-1] * (1.0/6.0);  // 1
            }
            if (j < i) {
                dp[i][j] += dp[i-1][j+1] * (1.0/3.0);  // 3,5
            }
        }
    }
    
    double result = 0.0;
    for (int i = 1; i <= n; i++) {
        result += dp[i][m];
    }
    
    return result;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    
    double ans = solve(n, m);
    printf("%.9f\n", ans);
    
    return 0;
}