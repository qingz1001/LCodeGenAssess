#include <stdio.h>
#include <string.h>

#define MAX_N 500005
#define MAX_W 500005

char s[MAX_N];
int n, w;
long long dp[MAX_W];
int cnt[MAX_W];

void solve() {
    scanf("%d %d", &n, &w);
    scanf("%s", s);
    
    memset(dp, 0, sizeof(dp));
    memset(cnt, 0, sizeof(cnt));
    
    dp[0] = 1;
    for (int i = 1; i <= w; i++) {
        for (int j = 0; j < n && i - j > 0; j++) {
            if (s[j] == s[(i - j - 1) % n]) {
                dp[i] += dp[i - j - 1];
            } else {
                break;
            }
        }
    }
    
    for (int i = n; i <= w; i++) {
        if (dp[i] > 0) {
            cnt[i] = 1;
        }
    }
    
    int answer = 0;
    for (int i = n; i <= w; i++) {
        answer += cnt[i];
    }
    
    printf("%d\n", answer);
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        solve();
    }
    return 0;
}