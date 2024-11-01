#include <stdio.h>
#include <string.h>

#define MAX_N 505
#define INF 0x3f3f3f3f

int A, B;
int K[MAX_N][MAX_N];
int dp[1 << 20];

int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    scanf("%d %d", &A, &B);
    
    for(int i = 0; i < B; i++) {
        for(int j = 0; j < B; j++) {
            scanf("%d", &K[i][j]);
        }
    }
    
    memset(dp, 0x3f, sizeof(dp));
    dp[0] = 0;
    
    for(int s = 1; s < (1 << B); s++) {
        for(int i = 0; i < B; i++) {
            if(s & (1 << i)) {
                int prev = s ^ (1 << i);
                dp[s] = min(dp[s], dp[prev] + A);
                
                for(int j = 0; j < B; j++) {
                    if(prev & (1 << j)) {
                        dp[s] = min(dp[s], dp[prev] + K[i][j]);
                    }
                }
            }
        }
    }
    
    printf("%d\n", dp[(1 << B) - 1]);
    
    return 0;
}