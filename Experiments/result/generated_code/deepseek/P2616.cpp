#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 100
#define MAXK 100
#define MAXE 350

typedef struct {
    int x, f, c;
} Store;

int compare(const void *a, const void *b) {
    return ((Store *)a)->x - ((Store *)b)->x;
}

int main() {
    int K, E, N;
    Store stores[MAXN];
    int dp[MAXK + 1];

    scanf("%d %d %d", &K, &E, &N);
    for (int i = 0; i < N; i++) {
        scanf("%d %d %d", &stores[i].x, &stores[i].f, &stores[i].c);
    }

    qsort(stores, N, sizeof(Store), compare);

    for (int i = 0; i <= K; i++) {
        dp[i] = INT_MAX;
    }
    dp[0] = 0;

    for (int i = 0; i < N; i++) {
        for (int j = K; j >= stores[i].f; j--) {
            if (dp[j - stores[i].f] != INT_MAX) {
                int cost = dp[j - stores[i].f] + stores[i].f * stores[i].c;
                if (i > 0) {
                    cost += (stores[i].x - stores[i - 1].x) * (j - stores[i].f);
                } else {
                    cost += stores[i].x * (j - stores[i].f);
                }
                if (cost < dp[j]) {
                    dp[j] = cost;
                }
            }
        }
    }

    int min_cost = INT_MAX;
    for (int i = K; i <= K; i++) {
        if (dp[i] != INT_MAX) {
            int final_cost = dp[i] + (E - stores[N - 1].x) * i;
            if (final_cost < min_cost) {
                min_cost = final_cost;
            }
        }
    }

    printf("%d\n", min_cost);

    return 0;
}