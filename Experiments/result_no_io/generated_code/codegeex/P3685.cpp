#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

const int MAXN = 15;
const int MAXM = 1005;
const int INF = 0x3f3f3f3f;

int n, m, len;
int a[MAXN][MAXN], b[MAXN][MAXN];
int vis[MAXN][MAXN], dp[MAXM][MAXN];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        int x;
        while (1) {
            scanf("%d", &x);
            if (x == 0) break;
            a[i][++len] = x;
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= len; j++) {
            int l = 0, r = 0;
            memset(vis, 0, sizeof(vis));
            for (int k = j; k <= len; k++) {
                if (!vis[a[i][k]]) {
                    vis[a[i][k]] = 1;
                    b[i][++r] = a[i][k];
                }
            }
            memset(vis, 0, sizeof(vis));
            for (int k = j; k >= 1; k--) {
                if (!vis[a[i][k]]) {
                    vis[a[i][k]] = 1;
                    b[i][++l] = a[i][k];
                }
            }
            for (int k = 1; k <= l; k++) a[i][k] = b[i][l - k + 1];
            a[i][l + 1] = 0;
            for (int k = 1; k <= r; k++) a[i][k + l + 1] = b[i][k];
            a[i][l + r + 2] = 0;
        }
    }

    memset(dp, 0x3f, sizeof(dp));
    dp[0][0] = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= len; j++) {
            for (int k = 0; k <= len; k++) {
                if (dp[j][i - 1] != INF && a[i][k] == a[i - 1][j]) {
                    dp[k][i] = min(dp[k][i], dp[j][i - 1] + (k - j) * (k - j));
                }
            }
        }
    }

    int ans = INF;
    for (int i = 1; i <= len; i++) {
        ans = min(ans, dp[i][n]);
    }
    if (ans == INF) ans = -1;
    printf("%d\n", ans);
    return 0;
}