#include <stdio.h>
#include <stdlib.h>

#define MAX_N 200
#define MAX_M 20

typedef struct {
    int A;
    int B;
} Topic;

int min(int a, int b) {
    return (a < b) ? a : b;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    Topic topics[MAX_M];
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &topics[i].A, &topics[i].B);
    }

    long long dp[MAX_N + 1];
    for (int i = 0; i <= n; i++) {
        dp[i] = (long long)i * i; // 初始化为最大可能值
    }
    dp[0] = 0;

    for (int i = 0; i < m; i++) {
        for (int j = n; j >= 0; j--) {
            for (int k = 0; k <= j; k++) {
                dp[j] = min(dp[j], dp[j - k] + (long long)topics[i].A * pow(k, topics[i].B));
            }
        }
    }

    printf("%lld\n", dp[n]);

    return 0;
}