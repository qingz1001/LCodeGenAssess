#include <stdio.h>
#include <limits.h>

int main() {
    int N;
    scanf("%d", &N);

    int prices[N];
    for (int i = 0; i < N; i++) {
        scanf("%d", &prices[i]);
    }

    int combinations[N][N];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            combinations[i][j] = -1;
        }
    }

    int A, B, C;
    while (scanf("%d%d%d", &A, &B, &C) == 3) {
        combinations[A][B] = C;
    }

    int min_cost[N];
    int min_cost_count[N];
    for (int i = 0; i < N; i++) {
        min_cost[i] = INT_MAX;
        min_cost_count[i] = 0;
    }
    min_cost[0] = prices[0];
    min_cost_count[0] = 1;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (combinations[i][j] != -1) {
                int mix_cost = min_cost[i] + min_cost[j];
                if (mix_cost < min_cost[combinations[i][j]]) {
                    min_cost[combinations[i][j]] = mix_cost;
                    min_cost_count[combinations[i][j]] = min_cost_count[i] * min_cost_count[j];
                } else if (mix_cost == min_cost[combinations[i][j]]) {
                    min_cost_count[combinations[i][j]] += min_cost_count[i] * min_cost_count[j];
                }
            }
        }
    }

    printf("%d %d\n", min_cost[0], min_cost_count[0]);

    return 0;
}