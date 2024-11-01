#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_N 2000
#define INF 0x3f3f3f3f

int n;
int v[MAX_N + 1];
int dp[MAX_N + 1][MAX_N + 1];

int max(int a, int b) {
    return a > b ? a : b;
}

int min(int a, int b) {
    return a < b ? a : b;
}

int solve(int l, int r) {
    if (dp[l][r] != -1) return dp[l][r];
    if (l == r) return dp[l][r] = v[l];
    if ((r + 1) % n == l) return dp[l][r] = 0;

    int res = 0;
    for (int i = l; i != (r + 1) % n; i = (i + 1) % n) {
        int next_l = (i + 1) % n;
        int next_r = (r + 1) % n;
        res = max(res, v[i] + min(solve(next_l, r), solve(next_l, next_r)));
    }

    return dp[l][r] = res;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &v[i]);
    }

    memset(dp, -1, sizeof(dp));
    
    int ans = 0;
    for (int i = 0; i < n; i++) {
        ans = max(ans, solve(i, (i - 1 + n) % n));
    }

    printf("%d\n", ans);

    return 0;
}