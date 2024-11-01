#include <stdio.h>
#include <string.h>

#define MOD 100000000
#define MAXN 12
#define MAXM (1<<12)

int M, N;
int field[MAXN];
int dp[2][MAXM];

int main() {
    scanf("%d %d", &M, &N);
    
    for (int i = 0; i < M; i++) {
        int row = 0;
        for (int j = 0; j < N; j++) {
            int x;
            scanf("%d", &x);
            if (x) row |= (1 << j);
        }
        field[i] = row;
    }
    
    int cur = 0, prev = 1;
    dp[cur][0] = 1;
    
    for (int i = 0; i < M; i++) {
        cur ^= 1; prev ^= 1;
        memset(dp[cur], 0, sizeof(dp[cur]));
        
        for (int mask = 0; mask < (1 << N); mask++) {
            if ((mask & field[i]) != mask) continue;
            if (mask & (mask << 1)) continue;
            
            for (int prev_mask = 0; prev_mask < (1 << N); prev_mask++) {
                if (mask & prev_mask) continue;
                dp[cur][mask] = (dp[cur][mask] + dp[prev][prev_mask]) % MOD;
            }
        }
    }
    
    int result = 0;
    for (int mask = 0; mask < (1 << N); mask++) {
        result = (result + dp[cur][mask]) % MOD;
    }
    
    printf("%d\n", result);
    return 0;
}