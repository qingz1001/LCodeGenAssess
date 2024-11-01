#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 1001
#define MAX_M 1001

int n;
int m[MAX_N];
int pre[MAX_N][MAX_M];
int dp[MAX_N];

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    scanf("%d", &n);
    
    for (int i = 1; i <= n; i++) {
        scanf("%d", &m[i]);
        for (int j = 1; j <= m[i]; j++) {
            int x, y;
            scanf("%d %d", &x, &y);
            pre[i][x] = y;
        }
        scanf("%d %d", &pre[i][0], &pre[i][i]);
    }
    
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        dp[i] = 1;
        for (int j = 0; j < i; j++) {
            if (pre[i][j] > 0) {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
        ans = max(ans, dp[i]);
    }
    
    printf("%d\n", ans);
    
    return 0;
}