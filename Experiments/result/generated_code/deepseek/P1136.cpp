#include <stdio.h>
#include <string.h>

#define MAXN 500
#define MAXK 100

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    int N, K;
    char sequence[MAXN + 1];
    int dp[MAXN + 1][MAXK + 1][2];

    scanf("%d %d", &N, &K);
    scanf("%s", sequence);

    memset(dp, 0, sizeof(dp));

    for (int i = 1; i <= N; i++) {
        for (int k = 0; k <= K; k++) {
            for (int state = 0; state < 2; state++) {
                dp[i][k][state] = dp[i - 1][k][state];
                if (sequence[i - 1] == 'j' && state == 1) {
                    dp[i][k][state] = max(dp[i][k][state], dp[i - 1][k][0] + 1);
                }
                if (sequence[i - 1] == 'z' && state == 0) {
                    dp[i][k][state] = max(dp[i][k][state], dp[i - 1][k][1] + 1);
                }
                if (k > 0) {
                    dp[i][k][state] = max(dp[i][k][state], dp[i - 1][k - 1][state]);
                }
            }
        }
    }

    int result = 0;
    for (int k = 0; k <= K; k++) {
        result = max(result, dp[N][k][1]);
    }

    printf("%d\n", result);

    return 0;
}