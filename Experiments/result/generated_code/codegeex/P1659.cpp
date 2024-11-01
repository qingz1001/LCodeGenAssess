#include <stdio.h>
#include <string.h>
#define MOD 19930726

typedef long long ll;

int n, k;
char s[1000005];
ll ans = 1;
int pows[1000005];
int cnt[1000005];
int dp[1000005][27];

int main() {
    scanf("%d%d%s", &n, &k, s);
    pows[0] = 1;
    for (int i = 1; i <= n; i++) {
        pows[i] = (pows[i-1] * 26) % MOD;
    }
    int len = 0;
    dp[0][13] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < 26; j++) {
            dp[i][j] = dp[i-1][j];
        }
        dp[i][s[i-1]-'a']++;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < 26; j++) {
            if (dp[i][j] % 2 == 1) {
                cnt[i-j]++;
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < i; j++) {
            if (cnt[i-j] > 0) {
                ans = (ans * pows[cnt[i-j]]) % MOD;
                cnt[i-j]--;
                k--;
                if (k == 0) {
                    break;
                }
            }
        }
        if (k == 0) {
            break;
        }
    }
    if (k > 0) {
        printf("-1\n");
    } else {
        printf("%lld\n", ans);
    }
    return 0;
}