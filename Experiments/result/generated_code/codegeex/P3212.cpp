#include <stdio.h>
#include <string.h>

#define MAX_TASKS 20
#define MAX_TIME 10000

int tasks[MAX_TASKS][4];
int n;

int dp[1 << MAX_TASKS][2][MAX_TIME];

int solve() {
    memset(dp, 0x3f, sizeof(dp));
    dp[0][0][0] = 0;

    for (int mask = 1; mask < (1 << n); mask++) {
        for (int i = 0; i < n; i++) {
            if (!(mask & (1 << i))) continue;

            int type = tasks[i][0];
            int a_time = tasks[i][1];
            int b_time = tasks[i][2];

            for (int j = 0; j < 2; j++) {
                for (int k = 0; k < MAX_TIME; k++) {
                    if (dp[mask ^ (1 << i)][j][k] == 0x3f3f3f3f) continue;

                    int new_a_time = j == 0 ? k + a_time : k;
                    int new_b_time = j == 1 ? k + b_time : k;

                    if (type == 1) {
                        if (new_a_time < new_b_time) {
                            dp[mask][1][new_b_time] = (dp[mask ^ (1 << i)][j][k] < dp[mask][1][new_b_time]) ? dp[mask ^ (1 << i)][j][k] : dp[mask][1][new_b_time];
                        }
                    } else if (type == 2) {
                        if (new_a_time > new_b_time) {
                            dp[mask][0][new_a_time] = (dp[mask ^ (1 << i)][j][k] < dp[mask][0][new_a_time]) ? dp[mask ^ (1 << i)][j][k] : dp[mask][0][new_a_time];
                        }
                    } else {
                        dp[mask][0][new_a_time] = (dp[mask ^ (1 << i)][j][k] < dp[mask][0][new_a_time]) ? dp[mask ^ (1 << i)][j][k] : dp[mask][0][new_a_time];
                        dp[mask][1][new_b_time] = (dp[mask ^ (1 << i)][j][k] < dp[mask][1][new_b_time]) ? dp[mask ^ (1 << i)][j][k] : dp[mask][1][new_b_time];
                    }
                }
            }
        }
    }

    int min_time = MAX_TIME;
    for (int i = 0; i < MAX_TIME; i++) {
        min_time = (dp[(1 << n) - 1][0][i] < min_time) ? dp[(1 << n) - 1][0][i] : min_time;
        min_time = (dp[(1 << n) - 1][1][i] < min_time) ? dp[(1 << n) - 1][1][i] : min_time;
    }

    return min_time;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d%d%d", &tasks[i][0], &tasks[i][1], &tasks[i][2]);
    }

    int result = solve();
    printf("%d\n", result);

    return 0;
}