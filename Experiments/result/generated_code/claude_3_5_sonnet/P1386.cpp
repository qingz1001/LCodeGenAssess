#include <stdio.h>
#include <string.h>

#define MAXN 305

int n, m, M;
int seat[MAXN], num[MAXN];
long long dp[MAXN][MAXN];

int check(int pos, int val) {
    int cur = val;
    while (pos <= n) {
        if (seat[cur] == 0) return cur;
        cur++;
        if (cur > n) cur = 1;
        pos++;
    }
    return 0;
}

long long solve() {
    memset(dp, 0, sizeof(dp));
    dp[0][0] = 1;
    
    for (int i = 1; i <= n; i++) {
        if (num[i]) {
            int valid = check(i, num[i]);
            if (!valid) return 0;
            seat[valid] = 1;
            for (int j = 0; j < n; j++) {
                dp[i][j] = dp[i-1][j];
            }
        } else {
            for (int j = 1; j <= n; j++) {
                int valid = check(i, j);
                if (valid) {
                    for (int k = 0; k < n; k++) {
                        dp[i][(k+1)%n] = (dp[i][(k+1)%n] + dp[i-1][k]) % M;
                    }
                    break;
                }
            }
        }
    }
    
    long long res = 0;
    for (int i = 0; i < n; i++) {
        res = (res + dp[n][i]) % M;
    }
    return res;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d%d", &n, &m, &M);
        memset(seat, 0, sizeof(seat));
        memset(num, 0, sizeof(num));
        
        for (int i = 0; i < m; i++) {
            int p, q;
            scanf("%d%d", &p, &q);
            num[p] = q;
        }
        
        long long ans = solve();
        if (ans) {
            printf("YES %lld\n", ans);
        } else {
            printf("NO\n");
        }
    }
    return 0;
}