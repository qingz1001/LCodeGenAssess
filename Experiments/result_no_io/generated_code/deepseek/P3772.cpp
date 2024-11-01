#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 200005

typedef struct {
    double p, q;
} Game;

Game games[MAXN];
int known[MAXN];
double dp[MAXN][2];

double calculate_expectation(int n, int m, char type[]) {
    // Initialize dp array
    memset(dp, 0, sizeof(dp));
    dp[1][0] = 1 - games[1].p;
    dp[1][1] = games[1].p;

    for (int i = 2; i <= n; i++) {
        dp[i][0] = dp[i-1][0] * (1 - games[i].q) + dp[i-1][1] * (1 - games[i].p);
        dp[i][1] = dp[i-1][0] * games[i].q + dp[i-1][1] * games[i].p;
    }

    double expectation = 0;
    for (int i = 1; i <= n; i++) {
        if (known[i] == 1) {
            expectation += dp[i][1];
        } else if (known[i] == 0) {
            expectation += dp[i][0];
        } else {
            expectation += dp[i][1];
        }
    }

    return expectation;
}

int main() {
    int n, m;
    char type[10];
    scanf("%d %d %s", &n, &m, type);

    for (int i = 1; i <= n; i++) {
        if (i == 1) {
            scanf("%lf", &games[i].p);
        } else {
            scanf("%lf %lf", &games[i].p, &games[i].q);
        }
    }

    memset(known, -1, sizeof(known));

    for (int i = 0; i < m; i++) {
        char op[5];
        int idx, result;
        scanf("%s", op);

        if (strcmp(op, "add") == 0) {
            scanf("%d %d", &idx, &result);
            known[idx] = result;
        } else if (strcmp(op, "del") == 0) {
            scanf("%d", &idx);
            known[idx] = -1;
        }

        double expectation = calculate_expectation(n, m, type);
        printf("%.4lf\n", expectation);
    }

    return 0;
}