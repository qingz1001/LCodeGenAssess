#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 500005

int N, M;
int worship[MAX_N];
int dp[MAX_N];

int min(int a, int b) {
    return a < b ? a : b;
}

int abs(int x) {
    return x < 0 ? -x : x;
}

int main() {
    scanf("%d %d", &N, &M);
    
    for (int i = 1; i <= N; i++) {
        scanf("%d", &worship[i]);
    }
    
    memset(dp, 0x3f, sizeof(dp));
    dp[0] = 0;
    
    for (int i = 1; i <= N; i++) {
        int yyy = 0, c01 = 0;
        for (int j = i; j >= 1; j--) {
            if (worship[j] == 1) yyy++;
            else c01++;
            
            if (yyy == c01 || abs(yyy - c01) <= M) {
                dp[i] = min(dp[i], dp[j-1] + 1);
            }
        }
    }
    
    printf("%d\n", dp[N]);
    
    return 0;
}