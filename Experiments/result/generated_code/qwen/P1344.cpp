#include <stdio.h>
#include <stdlib.h>

#define INF 0x3f3f3f3f

typedef struct {
    int from, to, cost;
} Edge;

int n, m;
Edge edges[1005];
int dp[33][1 << 32];

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &edges[i].from, &edges[i].to, &edges[i].cost);
    }

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j < 1 << n; j++) {
            dp[i][j] = INF;
        }
    }
    dp[1][0] = 0;

    for (int k = 0; k < m; k++) {
        for (int i = n; i >= 1; i--) {
            for (int j = 0; j < 1 << n; j++) {
                if ((j & (1 << (i - 1))) == 0) {
                    dp[i][j] = dp[i][j | (1 << (i - 1))];
                }
                dp[i][j] = dp[i][j] < dp[i][j ^ (1 << (i - 1))] + edges[k].cost ? dp[i][j] : dp[i][j ^ (1 << (i - 1))] + edges[k].cost;
            }
        }
    }

    int min_cost = INF, min_trucks = INF;
    for (int j = 0; j < 1 << n; j++) {
        if (dp[n][j] < min_cost || (dp[n][j] == min_cost && __builtin_popcount(j) < min_trucks)) {
            min_cost = dp[n][j];
            min_trucks = __builtin_popcount(j);
        }
    }

    printf("%d %d\n", min_cost, min_trucks);

    return 0;
}