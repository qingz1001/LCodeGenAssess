#include <stdio.h>
#include <stdlib.h>

#define MAX_N 200

int min(int a, int b) {
    return (a < b) ? a : b;
}

int main() {
    int N, A, B;
    scanf("%d %d %d", &N, &A, &B);
    int K[MAX_N];
    for (int i = 0; i < N; i++) {
        scanf("%d", &K[i]);
    }

    int dp[MAX_N][2]; // dp[i][0] 表示从第 i 层向上到达的最小按键次数，dp[i][1] 表示从第 i 层向下到达的最小按键次数
    for (int i = 0; i < N; i++) {
        dp[i][0] = dp[i][1] = -1;
    }
    dp[A-1][0] = dp[B-1][1] = 0;

    for (int i = 0; i < N; i++) {
        if (dp[i][0] != -1) {
            if (i + K[i] < N && dp[i + K[i]][0] == -1) {
                dp[i + K[i]][0] = dp[i][0] + 1;
            }
            if (i - K[i] >= 0 && dp[i - K[i]][1] == -1) {
                dp[i - K[i]][1] = dp[i][0] + 1;
            }
        }
        if (dp[i][1] != -1) {
            if (i + K[i] < N && dp[i + K[i]][0] == -1) {
                dp[i + K[i]][0] = dp[i][1] + 1;
            }
            if (i - K[i] >= 0 && dp[i - K[i]][1] == -1) {
                dp[i - K[i]][1] = dp[i][1] + 1;
            }
        }
    }

    int result = -1;
    if (dp[B-1][0] != -1 && dp[B-1][1] != -1) {
        result = min(dp[B-1][0], dp[B-1][1]);
    } else if (dp[B-1][0] != -1) {
        result = dp[B-1][0];
    } else if (dp[B-1][1] != -1) {
        result = dp[B-1][1];
    }

    printf("%d\n", result);

    return 0;
}