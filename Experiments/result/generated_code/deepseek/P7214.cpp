#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_M 100000

typedef struct {
    int T, L, R, C;
} Plan;

int compare_plans(const void *a, const void *b) {
    return ((Plan *)a)->T - ((Plan *)b)->T;
}

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    Plan plans[MAX_M];
    for (int i = 0; i < M; i++) {
        scanf("%d %d %d %d", &plans[i].T, &plans[i].L, &plans[i].R, &plans[i].C);
    }

    // Sort plans by time T
    qsort(plans, M, sizeof(Plan), compare_plans);

    long long dp[MAX_M];
    for (int i = 0; i < M; i++) {
        dp[i] = LLONG_MAX;
    }

    for (int i = 0; i < M; i++) {
        if (plans[i].L == 1) {
            dp[i] = plans[i].C;
        }
    }

    for (int i = 0; i < M; i++) {
        for (int j = i + 1; j < M; j++) {
            if (plans[j].T > plans[i].T && plans[j].L <= plans[i].R + 1 && plans[j].R >= plans[i].R + 1) {
                if (dp[i] != LLONG_MAX) {
                    dp[j] = (dp[j] < dp[i] + plans[j].C) ? dp[j] : (dp[i] + plans[j].C);
                }
            }
        }
    }

    long long min_cost = LLONG_MAX;
    for (int i = 0; i < M; i++) {
        if (plans[i].R == N && dp[i] != LLONG_MAX) {
            min_cost = (min_cost < dp[i]) ? min_cost : dp[i];
        }
    }

    if (min_cost == LLONG_MAX) {
        printf("-1\n");
    } else {
        printf("%lld\n", min_cost);
    }

    return 0;
}