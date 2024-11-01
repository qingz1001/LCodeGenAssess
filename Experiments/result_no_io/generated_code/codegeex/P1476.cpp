#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

#define MAXN 100
#define MAXM 120

int main() {
    int n, m;
    scanf("%d%d", &n, &m);

    int time[MAXM + 1][MAXM + 1];
    memset(time, 0, sizeof(time));

    for (int i = 0; i < m; i++) {
        int i, j, k;
        scanf("%d%d%d", &i, &j, &k);
        time[i][j] = k;
    }

    int dp[MAXN + 1][MAXM + 1];
    bool visited[MAXN + 1][MAXM + 1];

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            dp[i][j] = INT_MAX;
            visited[i][j] = false;
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (time[i][j] > 0) {
                dp[i][j] = time[i][j];
                visited[i][j] = true;
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            for (int k = 1; k <= m; k++) {
                if (time[j][k] > 0 && dp[i][j] != INT_MAX && dp[i][j] + time[j][k] < dp[i][k]) {
                    dp[i][k] = dp[i][j] + time[j][k];
                    visited[i][k] = true;
                }
            }
        }
    }

    int minTime = INT_MAX;
    for (int i = 1; i <= m; i++) {
        if (visited[n][i] && dp[n][i] < minTime) {
            minTime = dp[n][i];
        }
    }

    printf("%d\n", minTime);

    bool found = false;
    for (int i = 1; i <= m; i++) {
        if (visited[n][i] && dp[n][i] == minTime) {
            printf("%d ", i);
            found = true;
        }
    }

    if (!found) {
        printf("No valid path found.");
    }

    return 0;
}