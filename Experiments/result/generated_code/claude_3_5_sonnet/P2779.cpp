#include <stdio.h>
#include <string.h>

#define MOD 1000000009
#define MAXN 500005

char s[MAXN];
int n, dp[MAXN][2][2];

int main() {
    scanf("%s", s);
    n = strlen(s);

    dp[0][0][0] = 1;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                if (s[i] == 'W' && j == 1) continue;
                if (s[i] == 'B' && j == 0) continue;

                if (j == 0) {
                    dp[i+1][0][0] = (dp[i+1][0][0] + dp[i][j][k]) % MOD;
                    dp[i+1][1][1] = (dp[i+1][1][1] + dp[i][j][k]) % MOD;
                } else {
                    if (k == 0) {
                        dp[i+1][0][0] = (dp[i+1][0][0] + dp[i][j][k]) % MOD;
                    }
                    dp[i+1][1][0] = (dp[i+1][1][0] + dp[i][j][k]) % MOD;
                }
            }
        }
    }

    int result = 0;
    for (int j = 0; j < 2; j++) {
        for (int k = 0; k < 2; k++) {
            result = (result + dp[n][j][k]) % MOD;
        }
    }

    printf("%d\n", result);

    return 0;
}