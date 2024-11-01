#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005
#define MAXV 1000

int n;
char s[MAXN];
int v[MAXN];
int dp[MAXN][MAXV + 1];

int main() {
    scanf("%s", s);
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &v[i]);
    }

    memset(dp, 0, sizeof(dp));
    int ans = 0;

    for (int i = 0; i < n; i++) {
        dp[i][v[i]]++;
        for (int j = 0; j <= MAXV; j++) {
            if (dp[i - 1][j] > 0) {
                dp[i][j + v[i]] += dp[i - 1][j];
            }
        }
        if (dp[i][i + 1] > 0) {
            ans += dp[i][i + 1];
        }
    }

    printf("%d\n", ans);

    return 0;
}