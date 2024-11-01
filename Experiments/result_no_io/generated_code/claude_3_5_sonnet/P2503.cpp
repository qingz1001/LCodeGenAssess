#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

#define MAX_N 20
#define MAX_M 6

int n, m;
int a[MAX_N];
int sum[1 << MAX_N];
double dp[MAX_M + 1][1 << MAX_N];

int count_bits(int x) {
    int count = 0;
    while (x) {
        count += x & 1;
        x >>= 1;
    }
    return count;
}

double calc_variance(double mean, int group_sum) {
    return (group_sum - mean) * (group_sum - mean) / m;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    int total = 0;
    for (int mask = 0; mask < (1 << n); mask++) {
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                sum[mask] += a[i];
            }
        }
        if (mask == (1 << n) - 1) {
            total = sum[mask];
        }
    }

    double mean = (double)total / m;

    for (int i = 0; i <= m; i++) {
        for (int j = 0; j < (1 << n); j++) {
            dp[i][j] = DBL_MAX;
        }
    }

    dp[0][0] = 0;

    for (int i = 1; i <= m; i++) {
        for (int mask = 0; mask < (1 << n); mask++) {
            if (count_bits(mask) < i) continue;
            for (int submask = mask; submask > 0; submask = (submask - 1) & mask) {
                double variance = calc_variance(mean, sum[submask]);
                if (dp[i - 1][mask ^ submask] + variance < dp[i][mask]) {
                    dp[i][mask] = dp[i - 1][mask ^ submask] + variance;
                }
            }
        }
    }

    double result = sqrt(dp[m][(1 << n) - 1]);
    printf("%.2f\n", result);

    return 0;
}