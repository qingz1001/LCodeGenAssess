#include <stdio.h>
#include <stdlib.h>
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
    int nA = 0, nB = 0;
    for (int i = 0; i < (1 << N); i++) {
        if (mask & (1 << i)) {
            nB++;
        } else {
            nA++;
        }
    }
    for (int i = 0; i < (1 << N); i++) {
        for (int j = i + 1; j < (1 << N); j++) {
            if ((mask & (1 << i)) != (mask & (1 << j))) {
                cost += flow[i][j] * k;
            } else {
                cost += flow[i][j] * (1 - k);
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
            flow[j][i] = flow[i][j];
        }
    }

    int total_cost = INT_MAX;
    for (int mask = 0; mask < (1 << (1 << N)); mask++) {
        int change_cost_sum = 0;
        for (int i = 0; i < (1 << N); i++) {
            if ((mask & (1 << i)) != (initial_payment[i] << i)) {
                change_cost_sum += change_cost[i];
            }
        }
        int payment_cost = calculate_cost(mask, 1);
        total_cost = min(total_cost, change_cost_sum + payment_cost);
    }

    printf("%d\n", total_cost);
    return 0;
}