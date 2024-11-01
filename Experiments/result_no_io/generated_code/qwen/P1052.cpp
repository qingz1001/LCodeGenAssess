#include <stdio.h>
#include <stdlib.h>

#define MAXN 100010

int stones[MAXN];
int dp[MAXN];

int min(int a, int b) {
    return (a < b) ? a : b;
}

int main() {
    int L, S, T, M;
    scanf("%d %d %d %d", &L, &S, &T, &M);
    
    for (int i = 0; i < M; i++) {
        scanf("%d", &stones[i]);
    }
    
    for (int i = 0; i <= L; i++) {
        dp[i] = INT_MAX / 2;
    }
    dp[0] = 0;
    
    for (int i = 0; i <= L; i++) {
        if (dp[i] == INT_MAX / 2) continue;
        for (int j = 0; j < M; j++) {
            if (stones[j] > i && stones[j] - i >= S && stones[j] - i <= T) {
                dp[stones[j]] = min(dp[stones[j]], dp[i] + 1);
            } else if (stones[j] <= i) {
                break;
            }
        }
    }
    
    printf("%d\n", dp[L]);
    
    return 0;
}