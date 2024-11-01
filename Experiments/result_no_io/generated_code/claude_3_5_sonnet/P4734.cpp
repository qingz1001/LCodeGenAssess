#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXN 2005
#define max(a,b) ((a)>(b)?(a):(b))

int n;
int v[MAXN];
int dp[MAXN][MAXN];

int solve(int l, int r) {
    if (l == r) return v[l];
    if (dp[l][r] != -1) return dp[l][r];
    
    int res = 0;
    for (int i = l; i <= r; i++) {
        int left = (i == l) ? r : i-1;
        int right = (i == r) ? l : i+1;
        res = max(res, v[i] + min(solve(left, i-1), solve(i+1, right)));
    }
    
    return dp[l][r] = res;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &v[i]);
    }
    
    memset(dp, -1, sizeof(dp));
    
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        ans = max(ans, v[i] + min(solve(1, i-1), solve(i+1, n)));
    }
    
    printf("%d\n", ans);
    
    return 0;
}