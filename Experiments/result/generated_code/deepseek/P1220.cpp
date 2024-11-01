#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 50

typedef struct {
    int position;
    int power;
} Lamp;

int min(int a, int b) {
    return a < b ? a : b;
}

int dp[MAXN][MAXN][2];

int main() {
    int n, c;
    scanf("%d %d", &n, &c);
    Lamp lamps[MAXN];
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &lamps[i].position, &lamps[i].power);
    }

    int total_power = 0;
    for (int i = 0; i < n; i++) {
        total_power += lamps[i].power;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dp[i][j][0] = dp[i][j][1] = INT_MAX;
        }
    }

    dp[c - 1][c - 1][0] = dp[c - 1][c - 1][1] = 0;

    for (int len = 1; len < n; len++) {
        for (int i = 0; i + len < n; i++) {
            int j = i + len;
            if (dp[i][j - 1][0] != INT_MAX) {
                dp[i][j][0] = min(dp[i][j][0], dp[i][j - 1][0] + (total_power - (lamps[j].power - lamps[i].power)) * (lamps[j].position - lamps[j - 1].position));
            }
            if (dp[i][j - 1][1] != INT_MAX) {
                dp[i][j][0] = min(dp[i][j][0], dp[i][j - 1][1] + (total_power - (lamps[j].power - lamps[i].power)) * (lamps[j].position - lamps[i].position));
            }
            if (dp[i + 1][j][0] != INT_MAX) {
                dp[i][j][1] = min(dp[i][j][1], dp[i + 1][j][0] + (total_power - (lamps[j].power - lamps[i].power)) * (lamps[i + 1].position - lamps[i].position));
            }
            if (dp[i + 1][j][1] != INT_MAX) {
                dp[i][j][1] = min(dp[i][j][1], dp[i + 1][j][1] + (total_power - (lamps[j].power - lamps[i].power)) * (lamps[j].position - lamps[i].position));
            }
        }
    }

    int result = min(dp[0][n - 1][0], dp[0][n - 1][1]);
    printf("%d\n", result);

    return 0;
}