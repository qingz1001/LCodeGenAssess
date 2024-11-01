#include <stdio.h>
#include <stdlib.h>

#define MAX_N 30000
#define MAX_M 25

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    int v[MAX_M], w[MAX_M];
    for (int i = 1; i <= m; i++) {
        scanf("%d %d", &v[i], &w[i]);
    }

    int dp[MAX_N] = {0};

    for (int i = 1; i <= m; i++) {
        for (int j = n; j >= v[i]; j--) {
            dp[j] = max(dp[j], dp[j - v[i]] + v[i] * w[i]);
        }
    }

    printf("%d\n", dp[n]);

    return 0;
}