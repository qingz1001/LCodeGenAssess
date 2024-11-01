#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 20
#define MAX_MASK 1024
#define INF 0x3f3f3f3f

int n;
int t[MAX_N], a[MAX_N], b[MAX_N];
int dp[MAX_MASK][MAX_MASK];

int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int solve() {
    memset(dp, 0x3f, sizeof(dp));
    dp[0][0] = 0;

    for (int mask = 0; mask < (1 << n); mask++) {
        for (int submask = mask; submask; submask = (submask - 1) & mask) {
            int time_a = 0, time_b = 0;
            for (int i = 0; i < n; i++) {
                if (mask & (1 << i)) {
                    if (submask & (1 << i)) {
                        time_a += a[i];
                    } else {
                        time_b += b[i];
                    }
                }
            }

            for (int i = 0; i < n; i++) {
                if (!(mask & (1 << i))) {
                    int new_mask = mask | (1 << i);
                    if (t[i] == 1 || t[i] == 3) {
                        dp[new_mask][submask | (1 << i)] = min(dp[new_mask][submask | (1 << i)], 
                                                               max(dp[mask][submask] + a[i], time_b + b[i]));
                    }
                    if (t[i] == 2 || t[i] == 3) {
                        dp[new_mask][submask] = min(dp[new_mask][submask], 
                                                    max(dp[mask][submask] + b[i], time_a + a[i]));
                    }
                }
            }
        }
    }

    return dp[(1 << n) - 1][(1 << n) - 1];
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d", &t[i], &a[i], &b[i]);
    }

    int result = solve();
    printf("%d\n", result);

    return 0;
}