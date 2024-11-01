#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 10000
#define MAX_PREREQUISITES 100

int n;
int times[MAX_N + 1];
int prerequisites[MAX_N + 1][MAX_PREREQUISITES + 1];
int dp[MAX_N + 1];

int max(int a, int b) {
    return a > b ? a : b;
}

int dfs(int task) {
    if (dp[task] != -1) {
        return dp[task];
    }

    int maxPrerequisiteTime = 0;
    for (int i = 0; prerequisites[task][i] != 0; i++) {
        maxPrerequisiteTime = max(maxPrerequisiteTime, dfs(prerequisites[task][i]));
    }

    dp[task] = maxPrerequisiteTime + times[task];
    return dp[task];
}

int main() {
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        int task, time;
        scanf("%d %d", &task, &time);
        times[task] = time;

        int prerequisite;
        int j = 0;
        while (scanf("%d", &prerequisite) == 1 && prerequisite != 0) {
            prerequisites[task][j++] = prerequisite;
        }
        prerequisites[task][j] = 0;
    }

    memset(dp, -1, sizeof(dp));

    int maxTime = 0;
    for (int i = 1; i <= n; i++) {
        maxTime = max(maxTime, dfs(i));
    }

    printf("%d\n", maxTime);

    return 0;
}