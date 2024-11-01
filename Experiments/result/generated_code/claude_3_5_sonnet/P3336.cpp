#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MOD 19940417
#define MAXN 2000010

typedef long long ll;

int n, k;
int f[MAXN], g[MAXN];
int dp[MAXN][2];

void init() {
    memset(f, -1, sizeof(f));
    memset(g, 0, sizeof(g));
    f[0] = f[n] = 0;
    g[0] = g[n] = 1;
}

void input() {
    scanf("%d %d", &n, &k);
    init();
    for (int i = 0; i < k; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        f[x] = y;
        g[x] = 1;
    }
}

int max(int a, int b) {
    return a > b ? a : b;
}

void solve() {
    ll ans1 = 1, ans2 = 0;
    int last = 0;
    dp[0][0] = dp[0][1] = 1;

    for (int i = 1; i <= n; i++) {
        if (g[i]) {
            if (f[i] == -1) {
                dp[i][0] = (dp[i-1][0] + dp[i-1][1]) % MOD;
                dp[i][1] = dp[i][0];
            } else {
                int d = f[i] - f[last];
                if (abs(d) > i - last || (d + i - last) % 2 != 0) {
                    ans1 = 0;
                    break;
                }
                int up = (d + i - last) / 2;
                int down = (i - last - d) / 2;
                dp[i][0] = dp[last][0];
                dp[i][1] = dp[last][1];
                if (up > 0) dp[i][1] = (ll)dp[i][1] * dp[up][0] % MOD;
                if (down > 0) dp[i][0] = (ll)dp[i][0] * dp[down][1] % MOD;
            }
            ans2 = max(ans2, f[i]);
            last = i;
        } else {
            dp[i][0] = (dp[i-1][0] + dp[i-1][1]) % MOD;
            dp[i][1] = dp[i][0];
        }
    }

    if (ans1) ans1 = dp[n][0];
    printf("%lld %lld\n", ans1, ans2);
}

int main() {
    input();
    solve();
    return 0;
}