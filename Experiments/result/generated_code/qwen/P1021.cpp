#include <stdio.h>
#include <stdlib.h>

#define MAX_N 15
#define MAX_K 15

int dp[MAX_N + 1][MAX_K + 1];
int coins[MAX_N];

void dfs(int n, int k, int sum) {
    if (n == 0 || k == 0) {
        dp[n][k] = sum;
        return;
    }
    for (int i = 1; i <= n; i++) {
        dfs(n - i, k - 1, sum + i);
    }
}

int main() {
    int N, K;
    scanf("%d %d", &N, &K);

    dfs(N, K, 0);

    int max_value = 0;
    for (int i = 1; i <= N * K; i++) {
        if (dp[N][K] >= i) {
            max_value = i;
        } else {
            break;
        }
    }

    printf("1 ");
    for (int i = 2; i <= max_value; i++) {
        if (dp[N][K] >= i && dp[N][K] < i + 1) {
            printf("%d ", i);
        }
    }
    printf("\n");
    printf("MAX=%d\n", max_value);

    return 0;
}