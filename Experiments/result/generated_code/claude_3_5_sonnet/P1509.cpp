#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 101
#define MAX_M 101
#define MAX_R 101
#define INF 0x3f3f3f3f

int n, m, r;
int rmb[MAX_N], rp[MAX_N], time[MAX_N];
int dp[MAX_M][MAX_R];

int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    scanf("%d", &n);
    
    for (int i = 1; i <= n; i++) {
        scanf("%d %d %d", &rmb[i], &rp[i], &time[i]);
    }
    
    scanf("%d %d", &m, &r);
    
    memset(dp, 0x3f, sizeof(dp));
    dp[0][0] = 0;
    
    for (int i = 1; i <= n; i++) {
        for (int j = m; j >= rmb[i]; j--) {
            for (int k = r; k >= rp[i]; k--) {
                dp[j][k] = min(dp[j][k], dp[j-rmb[i]][k-rp[i]] + time[i]);
            }
        }
    }
    
    int min_time = INF;
    for (int j = 0; j <= m; j++) {
        for (int k = 0; k <= r; k++) {
            min_time = min(min_time, dp[j][k]);
        }
    }
    
    printf("%d\n", min_time == INF ? 0 : min_time);
    
    return 0;
}