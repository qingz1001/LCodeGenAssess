#include <stdio.h>
#include <string.h>

#define MAX_N 45
#define MAX_W 1000

int n, w;
char s[MAX_N + 1];
int dp[MAX_W + 1];

int solve() {
    memset(dp, 0, sizeof(dp));
    dp[0] = 1;
    
    for (int i = n; i <= w; i++) {
        for (int j = 0; j < n && j < i; j++) {
            int k;
            for (k = 0; k < n && j + k < i; k++) {
                if (s[k] != s[i - j - n + k]) {
                    break;
                }
            }
            if (k == n || j + k == i) {
                dp[i] |= dp[i - n + j];
            }
        }
    }
    
    int ans = 0;
    for (int i = n; i <= w; i++) {
        if (dp[i]) {
            ans++;
        }
    }
    return ans;
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        scanf("%d %d", &n, &w);
        scanf("%s", s);
        printf("%d\n", solve());
    }
    return 0;
}