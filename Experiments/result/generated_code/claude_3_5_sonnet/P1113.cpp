#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 10000
#define MAX_PREP 100

int n;
int time[MAX_N + 1];
int prep[MAX_N + 1][MAX_PREP + 1];
int dp[MAX_N + 1];

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        int task, len;
        scanf("%d %d", &task, &len);
        time[task] = len;

        int j = 0;
        while (1) {
            int p;
            scanf("%d", &p);
            if (p == 0) break;
            prep[task][j++] = p;
        }
        prep[task][j] = 0;
    }

    memset(dp, 0, sizeof(dp));

    for (int i = 1; i <= n; i++) {
        dp[i] = time[i];
        for (int j = 0; prep[i][j] != 0; j++) {
            dp[i] = max(dp[i], dp[prep[i][j]] + time[i]);
        }
    }

    int result = 0;
    for (int i = 1; i <= n; i++) {
        result = max(result, dp[i]);
    }

    printf("%d\n", result);

    return 0;
}