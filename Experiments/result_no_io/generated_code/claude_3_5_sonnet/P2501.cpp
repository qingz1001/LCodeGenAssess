#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_N 35001
#define MAX_A 100001

int n;
int a[MAX_N];
int dp[MAX_N][MAX_A];
int prev[MAX_N][MAX_A];

int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j < MAX_A; j++) {
            dp[i][j] = INT_MAX;
        }
    }

    dp[0][0] = 0;

    for (int i = 1; i <= n; i++) {
        int min_prev = INT_MAX;
        int min_prev_j = 0;

        for (int j = 1; j < MAX_A; j++) {
            if (dp[i-1][j-1] < min_prev) {
                min_prev = dp[i-1][j-1];
                min_prev_j = j-1;
            }

            if (j <= a[i]) {
                dp[i][j] = min_prev + 1;
                prev[i][j] = min_prev_j;
            } else {
                dp[i][j] = min(dp[i-1][j-1], min_prev + 1);
                prev[i][j] = (dp[i][j] == dp[i-1][j-1]) ? j-1 : min_prev_j;
            }
        }
    }

    int min_changes = INT_MAX;
    int min_j = 0;
    for (int j = 1; j < MAX_A; j++) {
        if (dp[n][j] < min_changes) {
            min_changes = dp[n][j];
            min_j = j;
        }
    }

    printf("%d\n", min_changes);

    long long total_diff = 0;
    for (int i = n; i >= 1; i--) {
        total_diff += abs(min_j - a[i]);
        min_j = prev[i][min_j];
    }

    printf("%lld\n", total_diff);

    return 0;
}