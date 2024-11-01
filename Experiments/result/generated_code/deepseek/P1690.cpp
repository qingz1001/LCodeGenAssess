#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 100
#define MAXP 10

int min(int a, int b) {
    return a < b ? a : b;
}

int tsp(int n, int dist[MAXN][MAXN], int P, int treasures[MAXP]) {
    int dp[1 << MAXP][MAXP];
    for (int i = 0; i < (1 << P); i++) {
        for (int j = 0; j < P; j++) {
            dp[i][j] = INT_MAX;
        }
    }

    for (int i = 0; i < P; i++) {
        dp[1 << i][i] = dist[0][treasures[i]];
    }

    for (int mask = 1; mask < (1 << P); mask++) {
        for (int i = 0; i < P; i++) {
            if (mask & (1 << i)) {
                for (int j = 0; j < P; j++) {
                    if (!(mask & (1 << j))) {
                        int new_mask = mask | (1 << j);
                        dp[new_mask][j] = min(dp[new_mask][j], dp[mask][i] + dist[treasures[i]][treasures[j]]);
                    }
                }
            }
        }
    }

    int final_mask = (1 << P) - 1;
    int result = INT_MAX;
    for (int i = 0; i < P; i++) {
        result = min(result, dp[final_mask][i] + dist[treasures[i]][n - 1]);
    }

    return result;
}

int main() {
    int n;
    scanf("%d", &n);

    int dist[MAXN][MAXN];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &dist[i][j]);
        }
    }

    int P;
    scanf("%d", &P);

    int treasures[MAXP];
    for (int i = 0; i < P; i++) {
        scanf("%d", &treasures[i]);
    }

    int result = tsp(n, dist, P, treasures);
    printf("%d\n", result);

    return 0;
}