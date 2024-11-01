#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 200005

double p[MAXN], q[MAXN];
int known[MAXN];
double dp[MAXN][2];

void update_dp(int n) {
    dp[1][0] = 1 - p[1];
    dp[1][1] = p[1];

    for (int i = 2; i <= n; i++) {
        if (known[i - 1] == -1) {
            dp[i][0] = dp[i - 1][0] * (1 - q[i]) + dp[i - 1][1] * (1 - p[i]);
            dp[i][1] = dp[i - 1][0] * q[i] + dp[i - 1][1] * p[i];
        } else if (known[i - 1] == 0) {
            dp[i][0] = dp[i - 1][0] * (1 - q[i]);
            dp[i][1] = dp[i - 1][0] * q[i];
        } else {
            dp[i][0] = dp[i - 1][1] * (1 - p[i]);
            dp[i][1] = dp[i - 1][1] * p[i];
        }
    }
}

int main() {
    int n, m;
    char type[10];
    scanf("%d %d %s", &n, &m, type);

    for (int i = 1; i <= n; i++) {
        if (i == 1) {
            scanf("%lf", &p[1]);
        } else {
            scanf("%lf %lf", &p[i], &q[i]);
        }
        known[i] = -1;
    }

    update_dp(n);

    for (int i = 0; i < m; i++) {
        char op[5];
        int idx;
        scanf("%s %d", op, &idx);

        if (strcmp(op, "add") == 0) {
            int result;
            scanf("%d", &result);
            known[idx] = result;
        } else if (strcmp(op, "del") == 0) {
            known[idx] = -1;
        }

        update_dp(n);

        double expected_wins = 0.0;
        for (int j = 1; j <= n; j++) {
            if (known[j] == -1) {
                expected_wins += dp[j][1];
            } else if (known[j] == 1) {
                expected_wins += 1.0;
            }
        }

        printf("%.6f\n", expected_wins);
    }

    return 0;
}