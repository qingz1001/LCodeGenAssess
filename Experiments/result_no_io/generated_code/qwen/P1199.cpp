#include <stdio.h>
#include <stdlib.h>

#define MAX_N 500
#define INF 1000000000

int n;
int adj[MAX_N][MAX_N];
int dp[MAX_N][1 << MAX_N];

int max(int a, int b) {
    return (a > b) ? a : b;
}

int min(int a, int b) {
    return (a < b) ? a : b;
}

void preprocess() {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < (1 << n); ++j) {
            dp[i][j] = -INF;
        }
    }
    for (int mask = 0; mask < (1 << n); ++mask) {
        if (__builtin_popcount(mask) == n / 2) {
            dp[0][mask] = 0;
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int mask = 0; mask < (1 << n); ++mask) {
            if (dp[i][mask] != -INF) {
                for (int j = 0; j < n; ++j) {
                    if (!(mask & (1 << j))) {
                        dp[i + 1][mask | (1 << j)] = max(dp[i + 1][mask | (1 << j)], dp[i][mask] + adj[i][j]);
                    }
                }
            }
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n - i; ++j) {
            scanf("%d", &adj[i][j]);
        }
    }

    preprocess();

    int max_val = 0;
    int found = 0;

    for (int mask = 0; mask < (1 << n); ++mask) {
        if (__builtin_popcount(mask) == n / 2) {
            int other_mask = (1 << n) - 1 - mask;
            if (dp[n / 2][mask] > dp[n / 2][other_mask]) {
                found = 1;
                max_val = dp[n / 2][mask];
            }
        }
    }

    if (found) {
        printf("1\n%d\n", max_val);
    } else {
        printf("0\n");
    }

    return 0;
}