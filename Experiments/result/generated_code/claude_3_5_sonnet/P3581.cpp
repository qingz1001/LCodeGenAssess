#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_N 1000001
#define MOD 1000000007

int n, k, p;
bool dislike[MAX_N][4];
int dp[MAX_N][4];

int main() {
    scanf("%d %d %d", &n, &k, &p);
    
    memset(dislike, 0, sizeof(dislike));
    
    for (int i = 0; i < k; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        if (b <= a + p && b > a) {
            dislike[a][b - a - 1] = true;
        }
    }
    
    memset(dp, 0, sizeof(dp));
    
    for (int i = 1; i <= p; i++) {
        dp[n-1][i-1] = 1;
    }
    
    for (int i = n-2; i >= 1; i--) {
        for (int j = 0; j < p; j++) {
            if (dislike[i][j]) continue;
            for (int k = 0; k < p; k++) {
                dp[i][j] = (dp[i][j] + dp[i+1][k]) % MOD;
            }
        }
    }
    
    int result = 0;
    for (int i = 0; i < p; i++) {
        result = (result + dp[1][i]) % MOD;
    }
    
    printf("%d\n", result);
    
    return 0;
}