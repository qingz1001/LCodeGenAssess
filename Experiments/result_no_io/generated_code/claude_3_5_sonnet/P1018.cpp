#include <stdio.h>
#include <string.h>

#define MAX_N 41
#define MAX_K 7

long long dp[MAX_N][MAX_K];
int num[MAX_N];

long long max(long long a, long long b) {
    return a > b ? a : b;
}

int main() {
    int N, K;
    char str[MAX_N];
    
    scanf("%d %d", &N, &K);
    scanf("%s", str);
    
    for (int i = 0; i < N; i++) {
        num[i] = str[i] - '0';
    }
    
    for (int i = 0; i < N; i++) {
        dp[i][0] = 0;
        for (int j = i; j >= 0; j--) {
            dp[i][0] = dp[i][0] * 10 + num[j];
        }
    }
    
    for (int k = 1; k <= K; k++) {
        for (int i = k; i < N; i++) {
            long long temp = 0;
            for (int j = i; j >= k; j--) {
                temp = temp * 10 + num[j];
                dp[i][k] = max(dp[i][k], temp * dp[j-1][k-1]);
            }
        }
    }
    
    printf("%lld\n", dp[N-1][K]);
    
    return 0;
}