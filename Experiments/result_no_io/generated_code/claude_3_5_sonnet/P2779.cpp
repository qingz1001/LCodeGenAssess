#include <stdio.h>
#include <string.h>

#define MOD 1000000009
#define MAXN 500005

char s[MAXN];
long long dp[MAXN][2];

int main() {
    scanf("%s", s);
    int n = strlen(s);
    
    dp[0][0] = dp[0][1] = 1;
    
    for (int i = 1; i <= n; i++) {
        if (s[i-1] == 'B' || s[i-1] == '?') {
            dp[i][0] = (dp[i-1][0] + dp[i-1][1]) % MOD;
        }
        if (s[i-1] == 'W' || s[i-1] == '?') {
            int j = i - 1;
            while (j >= 0 && (s[j] == 'W' || s[j] == '?')) j--;
            j++;
            if (j == 0) {
                dp[i][1] = dp[i-1][0];
            } else {
                dp[i][1] = dp[j-1][0];
            }
        }
    }
    
    printf("%lld\n", (dp[n][0] + dp[n][1]) % MOD);
    
    return 0;
}