#include <stdio.h>
#include <string.h>

#define MAXN 305

int n, m, M;
int a[MAXN], used[MAXN];
long long dp[MAXN][MAXN];

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d%d", &n, &m, &M);
        memset(a, 0, sizeof(a));
        memset(used, 0, sizeof(used));
        
        for (int i = 0; i < m; i++) {
            int p, q;
            scanf("%d%d", &p, &q);
            a[p] = q;
            used[q]++;
        }
        
        int flag = 1;
        for (int i = 1; i <= n; i++) {
            if (a[i] && used[a[i]] > 1) {
                flag = 0;
                break;
            }
        }
        
        if (!flag) {
            printf("NO\n");
            continue;
        }
        
        memset(dp, 0, sizeof(dp));
        dp[0][0] = 1;
        
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j <= n; j++) {
                if (a[i]) {
                    if (j >= a[i]) dp[i][j] = dp[i-1][j-1];
                } else {
                    for (int k = 1; k <= j; k++) {
                        if (!used[k]) {
                            dp[i][j] = (dp[i][j] + dp[i-1][j-1]) % M;
                        }
                    }
                }
            }
        }
        
        long long ans = 0;
        for (int i = 0; i <= n; i++) {
            ans = (ans + dp[n][i]) % M;
        }
        
        printf("YES %lld\n", ans);
    }
    return 0;
}