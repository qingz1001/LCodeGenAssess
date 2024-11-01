#include <stdio.h>

int main() {
    int T, M;
    scanf("%d %d", &T, &M);

    int time[100], value[100];
    for (int i = 0; i < M; i++) {
        scanf("%d %d", &time[i], &value[i]);
    }

    int dp[1001] = {0}; // dp[i]表示时间不超过i时采药的最大价值

    for (int i = 0; i < M; i++) {
        for (int j = T; j >= time[i]; j--) {
            dp[j] = (dp[j - time[i]] + value[i] > dp[j]) ? dp[j - time[i]] + value[i] : dp[j];
        }
    }

    printf("%d\n", dp[T]);
    return 0;
}