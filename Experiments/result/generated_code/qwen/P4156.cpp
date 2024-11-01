#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 1000
#define MAX_W 1000

int dp[MAX_W + 1];

void dfs(const char *s, int n, int w, int len) {
    if (len > w) return;
    dp[len]++;
    for (int i = 1; i <= n; i++) {
        dfs(s, n - i, w, len + i);
    }
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int n, w;
        scanf("%d %d", &n, &w);
        char s[MAX_N + 1];
        scanf("%s", s);
        memset(dp, 0, sizeof(dp));
        dfs(s, n, w, 0);
        int count = 0;
        for (int i = 0; i <= w; i++) {
            if (dp[i]) count++;
        }
        printf("%d\n", count);
    }
    return 0;
}