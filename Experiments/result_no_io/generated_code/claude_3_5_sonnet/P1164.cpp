#include <stdio.h>

#define MAXN 101
#define MAXM 10001

int N, M;
int prices[MAXN];
int dp[MAXM];

int main() {
    scanf("%d %d", &N, &M);
    
    for (int i = 0; i < N; i++) {
        scanf("%d", &prices[i]);
    }

    dp[0] = 1;
    
    for (int i = 0; i < N; i++) {
        for (int j = prices[i]; j <= M; j++) {
            dp[j] += dp[j - prices[i]];
        }
    }

    printf("%d\n", dp[M]);

    return 0;
}