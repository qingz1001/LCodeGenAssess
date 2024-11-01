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
        long long temp = 0;
        for (int j = i; j < N; j++) {
            temp = temp * 10 + num[j];
            dp[j][0] = temp;
        }
    }
    
    for (int k = 1; k <= K; k++) {
        for (int i = k; i < N; i++) {
            for (int j = k - 1; j < i; j++) {
                dp[i][k] = max(dp[i][k], dp[j][k-1] * dp[i][0]);
            }
        }
    }
    
    printf("%lld\n", dp[N-1][K]);
    
    return 0;
}