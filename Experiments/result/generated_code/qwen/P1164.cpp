#include <stdio.h>

int main() {
    int N, M;
    scanf("%d %d", &N, &M);
    
    int prices[100];
    for (int i = 0; i < N; i++) {
        scanf("%d", &prices[i]);
    }
    
    int dp[10001] = {0};
    dp[0] = 1;
    
    for (int i = 0; i < N; i++) {
        for (int j = M; j >= prices[i]; j--) {
            dp[j] += dp[j - prices[i]];
        }
    }
    
    printf("%d\n", dp[M]);
    
    return 0;
}