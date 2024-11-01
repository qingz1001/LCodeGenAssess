#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005
#define MAXK 105

typedef long long ll;

int n, k, r, L;
int p[MAXN];
ll dp[MAXN][MAXK];
int ans[MAXN];

void solve() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= k; j++) {
            dp[i][j] = -1;
        }
    }
    dp[1][1] = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= k; j++) {
            for (int t = 1; t < i; t++) {
                int len = p[i] - p[t];
                if (len <= 2 * r) continue;
                ll sum = (ll)r * r * (p[i] - p[t] - 2 * r);
                for (int m = 1; m < j; m++) {
                    sum += dp[t][m];
                }
                if (dp[i][j] < sum) {
                    dp[i][j] = sum;
                    ans[i] = j;
                }
            }
        }
    }
    int now = n;
    for (int i = k; i > 0; i--) {
        printf("%d ", now);
        now = ans[now];
    }
    printf("\n");
}

int main() {
    scanf("%d %d %d %d", &n, &k, &r, &L);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &p[i]);
    }
    solve();
    return 0;
}