#include <stdio.h>
#include <string.h>

#define MAX_N 100
#define MAX_M 10000

int N, M;
int prices[MAX_N];
int dp[MAX_M + 1];

int main() {
    scanf("%d %d", &N, &M);
    
    for (int i = 0; i < N; i++) {
        scanf("%d", &prices[i]);
    }
    
    memset(dp, 0, sizeof(dp));
    dp[0] = 1;
    
    for (int i = 0; i < N; i++) {
        for (int j = M; j >= prices[i]; j--) {
            dp[j] += dp[j - prices[i]];
        }
    }
    
    printf("%d\n", dp[M]);
    
    return 0;
}