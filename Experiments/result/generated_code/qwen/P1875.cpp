#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_N 1000
#define INF INT_MAX

typedef struct {
    int a, b, c;
} Recipe;

int min(int a, int b) {
    return (a < b) ? a : b;
}

int main() {
    int N;
    scanf("%d", &N);
    int prices[MAX_N];
    for (int i = 0; i < N; i++) {
        scanf("%d", &prices[i]);
    }

    Recipe recipes[2 * MAX_N];
    int recipe_count = 0;
    while (scanf("%d %d %d", &recipes[recipe_count].a, &recipes[recipe_count].b, &recipes[recipe_count].c) != EOF && recipes[recipe_count].a != 0) {
        recipe_count++;
    }

    long long dp[N][N];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            dp[i][j] = INF;
        }
    }
    dp[0][0] = 0;

    for (int k = 0; k < recipe_count; k++) {
        int a = recipes[k].a, b = recipes[k].b, c = recipes[k].c;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (dp[a][i] != INF && dp[b][j] != INF) {
                    dp[c][(i + j) / 2] = min(dp[c][(i + j) / 2], dp[a][i] + dp[b][j] + (i + j) % 2 * prices[c]);
                }
            }
        }
    }

    long long min_cost = INF;
    long long count = 0;
    for (int i = 0; i < N; i++) {
        if (dp[0][i] != INF) {
            if (min_cost > dp[0][i]) {
                min_cost = dp[0][i];
                count = 1;
            } else if (min_cost == dp[0][i]) {
                count++;
            }
        }
    }

    printf("%lld %lld\n", min_cost, count);

    return 0;
}