#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_N 30005
#define INF 0x3f3f3f3f

char s[MAX_N];
int n, q;
int nxt[MAX_N][26], dp[MAX_N];

void preprocess() {
    for (int i = 0; i < 26; i++) {
        nxt[n][i] = n + 1;
    }
    for (int i = n - 1; i >= 0; i--) {
        for (int j = 0; j < 26; j++) {
            nxt[i][j] = nxt[i + 1][j];
        }
        nxt[i][s[i] - 'a'] = i + 1;
    }
}

int solve(int i, int p, int k) {
    memset(dp, 0x3f, sizeof(dp));
    int j = i;
    while (j <= n && s[j - 1] == s[p - 1]) {
        j++;
        p++;
    }
    dp[j] = n - j;

    for (int x = j; x <= n; x++) {
        if (dp[x] == INF) continue;
        for (int y = x; y <= n; y++) {
            int z = nxt[i - 1][s[y - 1] - 'a'];
            if (z > n) break;
            dp[y + 1] = (dp[y + 1] < dp[x] + y - x + 1) ? dp[y + 1] : dp[x] + y - x + 1;
        }
    }

    int ans = dp[k];
    for (int x = k; x <= n; x++) {
        ans = (ans < dp[x] + x - k) ? ans : dp[x] + x - k;
    }
    return ans;
}

int main() {
    scanf("%d %d", &n, &q);
    scanf("%s", s);
    preprocess();

    while (q--) {
        int i, p, k;
        scanf("%d %d %d", &i, &p, &k);
        printf("%d\n", solve(i, p, k));
    }

    return 0;
}