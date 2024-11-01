#include <stdio.h>
#include <string.h>

#define MAXN 50
#define MAXK 7

long long dp[MAXN][MAXK];

int main() {
    int N, K;
    char num[MAXN];
    
    scanf("%d %d", &N, &K);
    scanf("%s", num);
    
    for (int i = 0; i <= N; i++) {
        for (int j = 0; j <= K; j++) {
            dp[i][j] = -1;
        }
    }
    
    dp[0][0] = 1;
    
    for (int i = 1; i <= N; i++) {
        for (int j = 0; j <= K; j++) {
            if (dp[i-1][j] != -1) {
                for (int len = 1; i + len - 1 <= N; len++) {
                    int product = 1;
                    for (int k = i - 1; k < i + len - 1; k++) {
                        product *= num[k] - '0';
                    }
                    if (j + 1 <= K && dp[i+len-1][j+1] == -1 || dp[i+len-1][j+1] < dp[i-1][j] * product) {
                        dp[i+len-1][j+1] = dp[i-1][j] * product;
                    }
                }
            }
        }
    }
    
    printf("%lld\n", dp[N][K]);
    
    return 0;
}