#include <stdio.h>
#include <stdlib.h>

#define MAX_T 1000
#define MAX_M 100

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    int T, M;
    int time[MAX_M], value[MAX_M];
    int dp[MAX_T + 1] = {0};

    scanf("%d %d", &T, &M);
    for (int i = 0; i < M; i++) {
        scanf("%d %d", &time[i], &value[i]);
    }

    for (int i = 0; i < M; i++) {
        for (int j = T; j >= time[i]; j--) {
            dp[j] = max(dp[j], dp[j - time[i]] + value[i]);
        }
    }

    printf("%d\n", dp[T]);

    return 0;
}