#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 50005
#define MAXW 1000005

int n, w;
char s[MAXN];
int dp[MAXW];

void solve() {
    scanf("%d %d", &n, &w);
    scanf("%s", s);

    if (w < n) {
        printf("0\n");
        return;
    }

    memset(dp, 0, sizeof(dp));
    dp[n] = 1;

    for (int i = n; i <= w; i++) {
        if (dp[i]) {
            for (int j = 1; j <= n; j++) {
                if (i + j <= w) {
                    dp[i + j] = 1;
                }
            }
        }
    }

    int count = 0;
    for (int i = n; i <= w; i++) {
        if (dp[i]) {
            count++;
        }
    }

    printf("%d\n", count);
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        solve();
    }
    return 0;
}