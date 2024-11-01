#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_N 30005
#define INF 0x3f3f3f3f

char s[MAX_N];
int n, q;
int next[MAX_N][26];
int dp[MAX_N][MAX_N];

void preprocess() {
    for (int i = 0; i < 26; i++) {
        next[n][i] = n + 1;
    }
    for (int i = n - 1; i >= 0; i--) {
        for (int j = 0; j < 26; j++) {
            if (s[i] - 'a' == j) {
                next[i][j] = i;
            } else {
                next[i][j] = next[i + 1][j];
            }
        }
    }
}

int min(int a, int b) {
    return a < b ? a : b;
}

int solve(int i, int p, int k) {
    memset(dp, 0x3f, sizeof(dp));
    int j = i;
    while (j < n && s[j] == s[p + j - i]) {
        j++;
    }
    dp[i][j] = n - j;

    for (int x = i; x <= k; x++) {
        for (int y = x; y <= n; y++) {
            if (dp[x][y] == INF) continue;
            
            if (x > 0) dp[x - 1][y] = min(dp[x - 1][y], dp[x][y] + 1);
            if (y < n) dp[x][y + 1] = min(dp[x][y + 1], dp[x][y] + 1);
            
            for (int c = 0; c < 26; c++) {
                int nx = next[x][c];
                int ny = next[y][c];
                if (nx <= k && ny <= n) {
                    dp[nx][ny] = min(dp[nx][ny], dp[x][y] + 1);
                }
            }
        }
    }

    int ans = INF;
    for (int y = k; y <= n; y++) {
        ans = min(ans, dp[k][y]);
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
        i--; p--; k--;
        printf("%d\n", solve(i, p, k));
    }

    return 0;
}