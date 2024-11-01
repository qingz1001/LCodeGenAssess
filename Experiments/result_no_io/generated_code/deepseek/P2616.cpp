#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 100
#define MAXK 100
#define MAXE 350

typedef struct {
    int x, f, c;
} Store;

Store stores[MAXN];
int dp[MAXE + 1][MAXK + 1];

int compare(const void *a, const void *b) {
    return ((Store *)a)->x - ((Store *)b)->x;
}

int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    int K, E, N;
    scanf("%d %d %d", &K, &E, &N);

    for (int i = 0; i < N; i++) {
        scanf("%d %d %d", &stores[i].x, &stores[i].f, &stores[i].c);
    }

    qsort(stores, N, sizeof(Store), compare);

    for (int i = 0; i <= E; i++) {
        for (int j = 0; j <= K; j++) {
            dp[i][j] = INT_MAX;
        }
    }

    dp[0][0] = 0;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j <= K; j++) {
            if (dp[stores[i].x][j] == INT_MAX) continue;
            for (int k = 0; k <= stores[i].f && j + k <= K; k++) {
                int cost = dp[stores[i].x][j] + k * stores[i].c;
                int new_pos = stores[i].x + (K - (j + k));
                if (new_pos <= E) {
                    dp[new_pos][j + k] = min(dp[new_pos][j + k], cost);
                }
            }
        }
    }

    int min_cost = INT_MAX;
    for (int i = 0; i <= E; i++) {
        if (dp[i][K] != INT_MAX) {
            min_cost = min(min_cost, dp[i][K] + (E - i) * K);
        }
    }

    printf("%d\n", min_cost);

    return 0;
}