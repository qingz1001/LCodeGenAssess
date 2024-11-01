#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MOD 19940417
#define MAXN 1000010

typedef long long ll;

int n, k;
int x[MAXN], y[MAXN];
int dp[MAXN][2];
int maxv[MAXN];

int max(int a, int b) {
    return a > b ? a : b;
}

int min(int a, int b) {
    return a < b ? a : b;
}

void solve() {
    int i, j, last = 0;
    ll ans = 1;
    
    dp[0][0] = dp[0][1] = 1;
    maxv[0] = 0;
    
    for (i = 1; i <= k; i++) {
        int len = x[i] - x[last];
        int dif = y[i] - y[last];
        
        if (abs(dif) > len || (len + dif) % 2 != 0) {
            printf("0 0\n");
            return;
        }
        
        int up = (len + dif) / 2;
        int down = (len - dif) / 2;
        
        for (j = 1; j < up; j++)
            ans = ans * 2 % MOD;
        
        dp[i][0] = dp[last][0];
        dp[i][1] = dp[last][1];
        
        if (y[i] > y[last]) {
            dp[i][1] = 0;
        } else if (y[i] < y[last]) {
            dp[i][0] = 0;
        }
        
        maxv[i] = max(maxv[last], y[i]);
        last = i;
    }
    
    int len = n - x[last];
    int up = (len + y[last]) / 2;
    
    for (i = 1; i < up; i++)
        ans = ans * 2 % MOD;
    
    ans = ans * (dp[k][0] + dp[k][1]) % MOD;
    
    printf("%lld %d\n", ans, maxv[k]);
}

int main() {
    scanf("%d%d", &n, &k);
    int i;
    for (i = 1; i <= k; i++) {
        scanf("%d%d", &x[i], &y[i]);
    }
    solve();
    return 0;
}