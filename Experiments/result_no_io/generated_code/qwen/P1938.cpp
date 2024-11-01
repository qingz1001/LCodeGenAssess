#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_CITIES 220
#define MAX_PATHS 150
#define MAX_JET_ROUTES 350
#define INF INT_MAX

typedef struct {
    int dest;
    int cost;
} JetRoute;

int min(int a, int b) {
    return (a < b) ? a : b;
}

int main() {
    int D, P, C, F, S;
    scanf("%d %d %d %d %d", &D, &P, &C, &F, &S);

    // Adjacency list for paths
    int *paths[C + 1];
    for (int i = 1; i <= C; ++i) {
        paths[i] = (int *)malloc(sizeof(int));
        *(paths[i]) = 0;
    }

    // Read paths
    for (int i = 0; i < P; ++i) {
        int A, B;
        scanf("%d %d", &A, &B);
        int *new_path = (int *)realloc(paths[A], sizeof(int) * (*(paths[A]) + 2));
        new_path[*(paths[A])] = B;
        new_path[*(paths[A]) + 1] = 0;
        paths[A] = new_path;
        *(paths[A] + 1)++;
    }

    // Array to store jet routes
    JetRoute jetRoutes[F];

    // Read jet routes
    for (int i = 0; i < F; ++i) {
        scanf("%d %d %d", &jetRoutes[i].dest, &jetRoutes[i].cost);
    }

    // Initialize DP array
    int dp[C + 1][D + 1];
    for (int i = 1; i <= C; ++i) {
        for (int j = 0; j <= D; ++j) {
            dp[i][j] = -INF;
        }
    }
    dp[S][0] = 0;

    // Fill DP table
    for (int d = 0; d <= D; ++d) {
        for (int c = 1; c <= C; ++c) {
            if (dp[c][d] == -INF) continue;
            for (int k = 0; k < *(paths[c]); ++k) {
                int nextCity = paths[c][k];
                dp[nextCity][0] = max(dp[nextCity][0], dp[c][d] + D);
            }
            for (int j = 0; j < F; ++j) {
                int nextCity = jetRoutes[j].dest;
                dp[nextCity][0] = max(dp[nextCity][0], dp[c][d] + jetRoutes[j].cost);
            }
        }
    }

    // Find the maximum profit
    int maxProfit = -1;
    for (int c = 1; c <= C; ++c) {
        maxProfit = max(maxProfit, dp[c][0]);
    }

    printf("%d\n", maxProfit);

    // Free allocated memory
    for (int i = 1; i <= C; ++i) {
        free(paths[i]);
    }

    return 0;
}