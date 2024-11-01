#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAXN 10
#define MAXM (1 << MAXN)

int N;
int initial_payment[MAXM];
int change_cost[MAXM];
int flow[MAXM][MAXM];
int dp[MAXM][MAXM];

int min(int a, int b) {
    return a < b ? a : b;
}

int calculate_cost(int mask, int k) {
    int cost = 0;
    for (int i = 0; i < (1 << N); i++) {
        if ((mask & (1 << i)) != 0) {
            cost += change_cost[i];
        }
    }
    for (int i = 0; i < (1 << N); i++) {
        for (int j = i + 1; j < (1 << N); j++) {
            if (((mask & (1 << i)) != 0) != ((mask & (1 << j)) != 0)) {
                cost += flow[i][j];
            }
        }
    }
    return cost;
}

int main() {
    scanf("%d", &N);
    for (int i = 0; i < (1 << N); i++) {
        scanf("%d", &initial_payment[i]);
    }
    for (int i = 0; i < (1 << N); i++) {
        scanf("%d", &change_cost[i]);
    }
    for (int i = 0; i < (1 << N); i++) {
        for (int j = i + 1; j < (1 << N); j++) {
            scanf("%d", &flow[i][j]);
        }
    }

    int total_users = 1 << N;
    int min_cost = INT_MAX;

    for (int mask = 0; mask < (1 << total_users); mask++) {
        int cost = calculate_cost(mask, N);
        min_cost = min(min_cost, cost);
    }

    printf("%d\n", min_cost);
    return 0;
}