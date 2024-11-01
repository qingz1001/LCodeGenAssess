#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_M 101
#define MAX_L 1000000001
#define INF 0x3f3f3f3f

int L, S, T, M;
int stones[MAX_M];
int dp[MAX_L];

int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    scanf("%d", &L);
    scanf("%d %d %d", &S, &T, &M);
    
    for (int i = 1; i <= M; i++) {
        scanf("%d", &stones[i]);
    }
    stones[0] = 0;
    stones[M+1] = L;
    
    // 压缩坐标
    for (int i = M; i >= 1; i--) {
        int diff = stones[i+1] - stones[i];
        if (diff > T) {
            L -= (diff - T);
            for (int j = i + 1; j <= M + 1; j++) {
                stones[j] -= (diff - T);
            }
        }
    }
    
    memset(dp, 0x3f, sizeof(dp));
    dp[0] = 0;
    
    for (int i = 1; i <= L; i++) {
        for (int j = S; j <= T && i >= j; j++) {
            dp[i] = min(dp[i], dp[i-j]);
        }
        for (int j = 1; j <= M; j++) {
            if (i == stones[j]) {
                dp[i]++;
                break;
            }
        }
    }
    
    int result = INF;
    for (int i = L; i >= L-T+1 && i >= 0; i--) {
        result = min(result, dp[i]);
    }
    
    printf("%d\n", result);
    
    return 0;
}